/* Copyright (c) 2017 Tallence AG and the authors, see the included COPYING file */

#include <string>

#include <rados/librados.hpp>

extern "C" {

#include "lib.h"
#include "fs-api.h"
#include "master-service.h"
#include "mail-index-modseq.h"
#include "mail-search-build.h"
#include "mailbox-list-private.h"
#include "index-pop3-uidl.h"
#include "typeof-def.h"
#include "dbox-mail.h"
#include "dbox-save.h"
#include "rbox-file.h"
#include "rbox-sync.h"
#include "rbox-storage.h"
#include "debug-helper.h"
}

#include "rbox-storage-struct.h"
#include "rados-cluster.h"
#include "rados-storage.h"

using namespace librados;  // NOLINT

using std::string;

extern struct mail_storage dbox_storage, rbox_storage;
extern struct mailbox rbox_mailbox;
extern struct mailbox_vfuncs rbox_mailbox_vfuncs;
extern struct dbox_storage_vfuncs rbox_dbox_storage_vfuncs;

static void rbox_storage_get_list_settings(const struct mail_namespace *ns ATTR_UNUSED,
                                           struct mailbox_list_settings *set) {
  FUNC_START();
  if (set->layout == NULL)
    set->layout = MAILBOX_LIST_NAME_FS;
  if (set->subscription_fname == NULL)
    set->subscription_fname = DBOX_SUBSCRIPTION_FILE_NAME;
  if (*set->maildir_name == '\0')
    set->maildir_name = DBOX_MAILDIR_NAME;
  if (*set->mailbox_dir_name == '\0')
    set->mailbox_dir_name = DBOX_MAILBOX_DIR_NAME;
  rbox_dbg_print_mailbox_list_settings(set, "rbox_storage_get_list_settings", NULL);
  FUNC_END();
}

static struct mail_storage *rbox_storage_alloc(void) {
  FUNC_START();
  struct rbox_storage *storage;
  pool_t pool;

  pool = pool_alloconly_create("rbox storage", 512 + 256);
  storage = p_new(pool, struct rbox_storage, 1);
  storage->storage.v = rbox_dbox_storage_vfuncs;
  storage->storage.storage = rbox_storage;
  storage->storage.storage.pool = pool;
  rbox_dbg_print_mail_storage(&storage->storage.storage, "rbox_storage_alloc", NULL);
  FUNC_END();
  return &storage->storage.storage;
}

static int rbox_storage_create(struct mail_storage *_storage, struct mail_namespace *ns, const char **error_r) {
  FUNC_START();
  struct rbox_storage *storage = (struct rbox_storage *)_storage;
  enum fs_properties props;

  if (dbox_storage_create(_storage, ns, error_r) < 0) {
    FUNC_END_RET("ret == -1; dbox_storage_create failed");
    return -1;
  }

  if (storage->storage.attachment_fs != NULL) {
    props = fs_get_properties(storage->storage.attachment_fs);
    i_debug("rbox_storage_create: props = 0x%04x", props);
    if ((props & FS_PROPERTY_RENAME) == 0) {
      *error_r =
          "mail_attachment_fs: "
          "Backend doesn't support renaming";
      FUNC_END_RET("ret == -1; Backend doesn't support renaming");
      return -1;
    }
  }

  string error_msg;
  int ret = storage->cluster.init(&error_msg);

  if (ret < 0) {
    // TODO free rbox_storage?
    *error_r = t_strdup_printf("%s", error_msg.c_str());
    return -1;
  }

  string username = "unknown";
  if (storage->storage.storage.user != NULL) {
    username = storage->storage.storage.user->username;
  }

  string poolname = "mail_storage";
  ret = storage->cluster.storage_create(poolname, username, "my_oid", &storage->s);

  if (ret < 0) {
    *error_r = t_strdup_printf("Error creating RadosStorage()! %s", strerror(-ret));
    storage->cluster.deinit();
    return -1;
  }

  rbox_dbg_print_mail_storage(_storage, "rbox_storage_create", NULL);
  FUNC_END();
  return 0;
}

static void rbox_storage_destroy(struct mail_storage *_storage) {
  FUNC_START();
  struct rbox_storage *storage = (struct rbox_storage *)_storage;

  rbox_dbg_print_mail_storage(_storage, "rbox_storage_destroy", NULL);

  storage->cluster.deinit();
  delete storage->s;
  storage->s = nullptr;

  if (storage->storage.attachment_fs != NULL)
    fs_deinit(&storage->storage.attachment_fs);
  index_storage_destroy(_storage);
  FUNC_END();
}

static const char *rbox_storage_find_root_dir(const struct mail_namespace *ns) {
  FUNC_START();
  bool debug = ns->mail_set->mail_debug;
  const char *home, *path;

  rbox_dbg_print_mail_user(ns->owner, "rbox_storage_find_root_dir", NULL);

  if (ns->owner != NULL && mail_user_get_home(ns->owner, &home) > 0) {
    path = t_strconcat(home, "/rbox", NULL);
    if (access(path, R_OK | W_OK | X_OK) == 0) {
      if (debug)
        i_debug("rbox: root exists (%s)", path);
      FUNC_END();
      return path;
    }
    if (debug)
      i_debug("rbox: access(%s, rwx): failed: %m", path);
  }
  FUNC_END_RET("ret == NULL; no root dir found");
  return NULL;
}

static bool rbox_storage_autodetect(const struct mail_namespace *ns, struct mailbox_list_settings *set) {
  FUNC_START();
  bool debug = ns->mail_set->mail_debug;
  struct stat st;
  const char *path, *root_dir;

  rbox_dbg_print_mail_user(ns->owner, "rbox_storage_autodetect", NULL);
  rbox_dbg_print_mailbox_list_settings(set, "rbox_storage_autodetect", NULL);

  if (set->root_dir != NULL)
    root_dir = set->root_dir;
  else {
    root_dir = rbox_storage_find_root_dir(ns);
    if (root_dir == NULL) {
      if (debug)
        i_debug("rbox: couldn't find root dir");
      FUNC_END_RET("ret == FALSE");
      return FALSE;
    }
  }

  /* NOTE: this check works for mdbox as well. we'll rely on the
   autodetect ordering to catch mdbox before we get here. */
  path = t_strconcat(root_dir, "/" DBOX_MAILBOX_DIR_NAME, NULL);
  if (stat(path, &st) < 0) {
    if (debug)
      i_debug("rbox autodetect: stat(%s) failed: %m", path);
    FUNC_END_RET("ret == FALSE");
    return FALSE;
  }

  if (!S_ISDIR(st.st_mode)) {
    if (debug)
      i_debug("rbox autodetect: %s not a directory", path);
    FUNC_END_RET("ret == FALSE");
    return FALSE;
  }

  set->root_dir = root_dir;
  dbox_storage_get_list_settings(ns, set);
  FUNC_END();
  return TRUE;
}

static struct mailbox *rbox_mailbox_alloc(struct mail_storage *storage, struct mailbox_list *list, const char *vname,
                                          enum mailbox_flags flags) {
  FUNC_START();
  struct rbox_mailbox *mbox;
  struct index_mailbox_context *ibox;
  pool_t pool;

  /* dbox can't work without index files */
  int flags_ = flags & ~MAILBOX_FLAG_NO_INDEX_FILES;

  pool = pool_alloconly_create("rbox mailbox", 1024 * 3);
  mbox = p_new(pool, struct rbox_mailbox, 1);
  rbox_mailbox.v = rbox_mailbox_vfuncs;
  mbox->box = rbox_mailbox;
  mbox->box.pool = pool;
  mbox->box.storage = storage;
  mbox->box.list = list;
  mbox->box.mail_vfuncs = &rbox_mail_vfuncs;

  index_storage_mailbox_alloc(&mbox->box, vname, static_cast<mailbox_flags>(flags_), MAIL_INDEX_PREFIX);

  ibox = static_cast<index_mailbox_context *>(INDEX_STORAGE_CONTEXT(&mbox->box));
  flags_ = ibox->index_flags | MAIL_INDEX_OPEN_FLAG_KEEP_BACKUPS | MAIL_INDEX_OPEN_FLAG_NEVER_IN_MEMORY;
  ibox->index_flags = static_cast<mail_index_open_flags>(flags_);

  mbox->storage = (struct rbox_storage *)storage;

  i_debug("rbox_mailbox_alloc: vname = %s", vname);
  rbox_dbg_print_rbox_mailbox(mbox, "rbox_mailbox_alloc", NULL);
  FUNC_END();
  return &mbox->box;
}

int rbox_read_header(struct rbox_mailbox *mbox, struct rbox_index_header *hdr, bool log_error, bool *need_resize_r) {
  FUNC_START();
  struct mail_index_view *view;
  const void *data;
  size_t data_size;
  int ret = 0;

  i_assert(mbox->box.opened);

  view = mail_index_view_open(mbox->box.index);
  mail_index_get_header_ext(view, mbox->hdr_ext_id, &data, &data_size);
  if (data_size < RBOX_INDEX_HEADER_MIN_SIZE && (!mbox->box.creating || data_size != 0)) {
    if (log_error) {
      mail_storage_set_critical(&mbox->storage->storage.storage, "rbox %s: Invalid dbox header size",
                                mailbox_get_path(&mbox->box));
    }
    ret = -1;
  } else {
    i_zero(hdr);
    memcpy(hdr, data, I_MIN(data_size, sizeof(*hdr)));
    if (guid_128_is_empty(hdr->mailbox_guid))
      ret = -1;
    else {
      /* data is valid. remember it in case mailbox
       is being reset */
      mail_index_set_ext_init_data(mbox->box.index, mbox->hdr_ext_id, hdr, sizeof(*hdr));
    }
  }
  mail_index_view_close(&view);
  *need_resize_r = data_size < sizeof(*hdr);

  rbox_dbg_print_rbox_mailbox(mbox, "rbox_read_header", NULL);
  rbox_dbg_print_rbox_index_header(hdr, "rbox_read_header", NULL);
  FUNC_END();
  return ret;
}

static void rbox_update_header(struct rbox_mailbox *mbox, struct mail_index_transaction *trans,
                               const struct mailbox_update *update) {
  FUNC_START();
  struct rbox_index_header hdr, new_hdr;
  bool need_resize;

  if (rbox_read_header(mbox, &hdr, TRUE, &need_resize) < 0) {
    i_zero(&hdr);
    need_resize = TRUE;
  }

  new_hdr = hdr;

  if (update != NULL && !guid_128_is_empty(update->mailbox_guid)) {
    memcpy(new_hdr.mailbox_guid, update->mailbox_guid, sizeof(new_hdr.mailbox_guid));
  } else if (guid_128_is_empty(new_hdr.mailbox_guid)) {
    guid_128_generate(new_hdr.mailbox_guid);
  }

  if (need_resize) {
    mail_index_ext_resize_hdr(trans, mbox->hdr_ext_id, sizeof(new_hdr));
  }
  if (memcmp(&hdr, &new_hdr, sizeof(hdr)) != 0) {
    mail_index_update_header_ext(trans, mbox->hdr_ext_id, 0, &new_hdr, sizeof(new_hdr));
  }
  memcpy(mbox->mailbox_guid, new_hdr.mailbox_guid, sizeof(mbox->mailbox_guid));
  rbox_dbg_print_rbox_mailbox(mbox, "rbox_update_header", NULL);
  FUNC_END();
}

int rbox_mailbox_create_indexes(struct mailbox *box, const struct mailbox_update *update,
                                struct mail_index_transaction *trans) {
  FUNC_START();
  struct rbox_mailbox *mbox = (struct rbox_mailbox *)box;
  struct mail_index_transaction *new_trans = NULL;
  const struct mail_index_header *hdr;
  uint32_t uid_validity, uid_next;

  if (trans == NULL) {
    new_trans = mail_index_transaction_begin(box->view, static_cast<mail_index_transaction_flags>(0));
    trans = new_trans;
  }

  hdr = mail_index_get_header(box->view);
  if (update != NULL && update->uid_validity != 0)
    uid_validity = update->uid_validity;
  else if (hdr->uid_validity != 0)
    uid_validity = hdr->uid_validity;
  else {
    /* set uidvalidity */
    uid_validity = dbox_get_uidvalidity_next(box->list);
  }

  if (hdr->uid_validity != uid_validity) {
    mail_index_update_header(trans, offsetof(struct mail_index_header, uid_validity), &uid_validity,
                             sizeof(uid_validity), TRUE);
  }
  if (update != NULL && hdr->next_uid < update->min_next_uid) {
    uid_next = update->min_next_uid;
    mail_index_update_header(trans, offsetof(struct mail_index_header, next_uid), &uid_next, sizeof(uid_next), TRUE);
  }
  if (update != NULL && update->min_first_recent_uid != 0 && hdr->first_recent_uid < update->min_first_recent_uid) {
    uint32_t first_recent_uid = update->min_first_recent_uid;

    mail_index_update_header(trans, offsetof(struct mail_index_header, first_recent_uid), &first_recent_uid,
                             sizeof(first_recent_uid), FALSE);
  }
  if (update != NULL && update->min_highest_modseq != 0 &&
      mail_index_modseq_get_highest(box->view) < update->min_highest_modseq) {
    mail_index_modseq_enable(box->index);
    mail_index_update_highest_modseq(trans, update->min_highest_modseq);
  }

  if (box->inbox_user && box->creating) {
    /* initialize pop3-uidl header when creating mailbox
     (not on mailbox_update()) */
    index_pop3_uidl_set_max_uid(box, trans, 0);
  }

  rbox_update_header(mbox, trans, update);

  rbox_dbg_print_rbox_mailbox(mbox, "rbox_mailbox_create_indexes", NULL);

  if (new_trans != NULL) {
    if (mail_index_transaction_commit(&new_trans) < 0) {
      mailbox_set_index_error(box);
      FUNC_END_RET("ret == -1; mail_index_transaction_commit failed ");
      return -1;
    }
  }
  FUNC_END();
  return 0;
}

static const char *rbox_get_attachment_path_suffix(struct dbox_file *_file) {
  FUNC_START();
  struct rbox_file *file = (struct rbox_file *)_file;

  const char *ret = t_strdup_printf("-%s-%u", guid_128_to_string(file->mbox->mailbox_guid), file->uid);
  i_debug("rbox_get_attachment_path_suffix: path suffix = %s", ret);
  rbox_dbg_print_rbox_file(file, "rbox_get_attachment_path_suffix", NULL);
  FUNC_END();
  return ret;
}

void rbox_set_mailbox_corrupted(struct mailbox *box) {
  FUNC_START();
  struct rbox_mailbox *mbox = (struct rbox_mailbox *)box;
  struct rbox_index_header hdr;
  bool need_resize;

  if (rbox_read_header(mbox, &hdr, TRUE, &need_resize) < 0 || hdr.rebuild_count == 0)
    mbox->corrupted_rebuild_count = 1;
  else
    mbox->corrupted_rebuild_count = hdr.rebuild_count;
  rbox_dbg_print_rbox_mailbox(mbox, "rbox_set_mailbox_corrupted", NULL);
  FUNC_END();
}

static void rbox_set_file_corrupted(struct dbox_file *_file) {
  FUNC_START();
  struct rbox_file *file = (struct rbox_file *)_file;

  rbox_set_mailbox_corrupted(&file->mbox->box);
  rbox_dbg_print_rbox_file(file, "rbox_set_file_corrupted", NULL);
  FUNC_END();
}

static int rbox_mailbox_alloc_index(struct rbox_mailbox *mbox) {
  FUNC_START();
  struct rbox_index_header hdr;

  if (index_storage_mailbox_alloc_index(&mbox->box) < 0) {
    rbox_dbg_print_rbox_mailbox(mbox, "rbox_mailbox_alloc_index", NULL);
    FUNC_END_RET("ret == -1; index_storage_mailbox_alloc_index failed");
    return -1;
  }

  mbox->ext_id = mail_index_ext_register(mbox->box.index, "obox", 0, sizeof(struct obox_mail_index_record), 1);

  mbox->hdr_ext_id = mail_index_ext_register(mbox->box.index, "dbox-hdr", sizeof(struct rbox_index_header), 0, 0);

  /* set the initialization data in case the mailbox is created */
  i_zero(&hdr);
  guid_128_generate(hdr.mailbox_guid);
  mail_index_set_ext_init_data(mbox->box.index, mbox->hdr_ext_id, &hdr, sizeof(hdr));
  rbox_dbg_print_rbox_mailbox(mbox, "rbox_mailbox_alloc_index", NULL);
  FUNC_END();
  return 0;
}

static int rbox_mailbox_open(struct mailbox *box) {
  FUNC_START();
  struct rbox_mailbox *mbox = (struct rbox_mailbox *)box;
  struct rbox_index_header hdr;
  bool need_resize;

  if (rbox_mailbox_alloc_index(mbox) < 0) {
    FUNC_END_RET("ret == -1; rbox_mailbox_alloc_index failed");
    return -1;
  }

  if (dbox_mailbox_open(box) < 0) {
    FUNC_END_RET("ret == -1; dbox_mailbox_open failed");
    return -1;
  }

  if (box->creating) {
    /* wait for mailbox creation to initialize the index */
    FUNC_END_RET("ret == -1; wait for mailbox creation");
    return 0;
  }

  /* get/generate mailbox guid */
  if (rbox_read_header(mbox, &hdr, FALSE, &need_resize) < 0) {
    /* looks like the mailbox is corrupted */
    (void)rbox_sync(mbox, RBOX_SYNC_FLAG_FORCE);
    if (rbox_read_header(mbox, &hdr, TRUE, &need_resize) < 0)
      i_zero(&hdr);
  }

  if (guid_128_is_empty(hdr.mailbox_guid)) {
    /* regenerate it */
    if (rbox_mailbox_create_indexes(box, NULL, NULL) < 0 || rbox_read_header(mbox, &hdr, TRUE, &need_resize) < 0) {
      FUNC_END_RET("ret == -1; rbox_mailbox_create_indexes failed");
      return -1;
    }
  }
  memcpy(mbox->mailbox_guid, hdr.mailbox_guid, sizeof(mbox->mailbox_guid));
  rbox_dbg_print_rbox_mailbox(mbox, "rbox_mailbox_open", NULL);
  FUNC_END();
  return 0;
}

static void rbox_mailbox_close(struct mailbox *box) {
  FUNC_START();
  struct rbox_mailbox *mbox = (struct rbox_mailbox *)box;
  rbox_dbg_print_rbox_mailbox(mbox, "rbox_mailbox_close", NULL);

  if (mbox->corrupted_rebuild_count != 0)
    (void)rbox_sync(mbox, static_cast<rbox_sync_flags>(0));
  index_storage_mailbox_close(box);
  FUNC_END();
}

static int rbox_mailbox_create(struct mailbox *box, const struct mailbox_update *update, bool directory) {
  FUNC_START();
  struct rbox_mailbox *mbox = (struct rbox_mailbox *)box;
  struct rbox_index_header hdr;
  bool need_resize;

  if (dbox_mailbox_create(box, update, directory) < 0) {
    FUNC_END_RET("ret == -1; dbox_mailbox_create failed");
    return -1;
  }
  if (directory || !guid_128_is_empty(mbox->mailbox_guid)) {
    FUNC_END_RET("ret == 0; directory || mbox->mailbox_guid not empty");
    return 0;
  }

  /* another process just created the mailbox. read the mailbox_guid. */
  if (rbox_read_header(mbox, &hdr, FALSE, &need_resize) < 0) {
    mail_storage_set_critical(box->storage, "rbox %s: Failed to read newly created dbox header",
                              mailbox_get_path(&mbox->box));
    FUNC_END_RET("ret == -1; Failed to read newly created dbox header");
    return -1;
  }
  memcpy(mbox->mailbox_guid, hdr.mailbox_guid, sizeof(mbox->mailbox_guid));
  i_assert(!guid_128_is_empty(mbox->mailbox_guid));
  rbox_dbg_print_rbox_mailbox(mbox, "rbox_mailbox_create", NULL);
  FUNC_END();
  return 0;
}

static int rbox_mailbox_get_metadata(struct mailbox *box, enum mailbox_metadata_items items,
                                     struct mailbox_metadata *metadata_r) {
  FUNC_START();
  struct rbox_mailbox *mbox = (struct rbox_mailbox *)box;

  i_debug("rbox_mailbox_get_metadata: items = 0x%04x", items);
  rbox_dbg_print_rbox_mailbox(mbox, "rbox_mailbox_get_metadata", NULL);

  if (index_mailbox_get_metadata(box, items, metadata_r) < 0) {
    FUNC_END_RET("ret == -1; index_mailbox_get_metadata failed");
    return -1;
  }
  if ((items & MAILBOX_METADATA_GUID) != 0) {
    memcpy(metadata_r->guid, mbox->mailbox_guid, sizeof(metadata_r->guid));
  }
  FUNC_END();
  return 0;
}

static int rbox_mailbox_update(struct mailbox *box, const struct mailbox_update *update) {
  FUNC_START();
  if (!box->opened) {
    if (mailbox_open(box) < 0) {
      FUNC_END_RET("ret == -1; mailbox_open failed");
      return -1;
    }
  }
  if (rbox_mailbox_create_indexes(box, update, NULL) < 0) {
    FUNC_END_RET("ret == -1; rbox_mailbox_create_indexes failed");
    return -1;
  }
  rbox_dbg_print_mailbox(box, "rbox_mailbox_update", NULL);
  FUNC_END();
  return index_storage_mailbox_update_common(box, update);
}

static void rbox_notify_changes(struct mailbox *box) {
  FUNC_START();
  const char *dir, *path;

  if (box->notify_callback == NULL)
    mailbox_watch_remove_all(box);
  else {
    if (mailbox_get_path_to(box, MAILBOX_LIST_PATH_TYPE_INDEX, &dir) <= 0) {
      return;
    }
    path = t_strdup_printf("%s/" MAIL_INDEX_PREFIX ".log", dir);
    mailbox_watch_add(box, path);
  }
  rbox_dbg_print_mailbox(box, "rbox_notify_changes", NULL);
  FUNC_END();
}

// TODO(jrse): remove test function to generate oid (used in rbox-mail.c, rbox-save.c)
void generate_oid(char *oid, char *username, int mail_uid) { sprintf(oid, "INBOX.%s%d", username, mail_uid); }

struct mail_storage rbox_storage = {
    .name = RBOX_STORAGE_NAME,
    .class_flags = static_cast<mail_storage_class_flags>(
        MAIL_STORAGE_CLASS_FLAG_FILE_PER_MSG | MAIL_STORAGE_CLASS_FLAG_HAVE_MAIL_GUIDS |
        MAIL_STORAGE_CLASS_FLAG_HAVE_MAIL_SAVE_GUIDS | MAIL_STORAGE_CLASS_FLAG_BINARY_DATA |
        MAIL_STORAGE_CLASS_FLAG_STUBS),
    .v = {
        NULL, rbox_storage_alloc, rbox_storage_create, rbox_storage_destroy, NULL, rbox_storage_get_list_settings,
        rbox_storage_autodetect, rbox_mailbox_alloc, NULL, NULL,
    }};

struct mailbox_vfuncs rbox_mailbox_vfuncs = {index_storage_is_readonly,
                                             index_storage_mailbox_enable,
                                             index_storage_mailbox_exists,
                                             rbox_mailbox_open,
                                             rbox_mailbox_close,
                                             index_storage_mailbox_free,
                                             rbox_mailbox_create,
                                             rbox_mailbox_update,
                                             index_storage_mailbox_delete,
                                             index_storage_mailbox_rename,
                                             index_storage_get_status,
                                             rbox_mailbox_get_metadata,
                                             index_storage_set_subscribed,
                                             index_storage_attribute_set,
                                             index_storage_attribute_get,
                                             index_storage_attribute_iter_init,
                                             index_storage_attribute_iter_next,
                                             index_storage_attribute_iter_deinit,
                                             index_storage_list_index_has_changed,
                                             index_storage_list_index_update_sync,
                                             rbox_storage_sync_init,
                                             index_mailbox_sync_next,
                                             index_mailbox_sync_deinit,
                                             NULL,
                                             rbox_notify_changes,
                                             index_transaction_begin,
                                             index_transaction_commit,
                                             index_transaction_rollback,
                                             NULL,
                                             rbox_mail_alloc,
                                             index_storage_search_init,
                                             index_storage_search_deinit,
                                             index_storage_search_next_nonblock,
                                             index_storage_search_next_update_seq,
                                             rbox_save_alloc,
                                             rbox_save_begin,
                                             rbox_save_continue,
                                             rbox_save_finish,
                                             rbox_save_cancel,
                                             rbox_copy,
                                             rbox_transaction_save_commit_pre,
                                             rbox_transaction_save_commit_post,
                                             rbox_transaction_save_rollback,
                                             index_storage_is_inconsistent};

struct mailbox rbox_mailbox = {};

/*
struct mailbox rbox_mailbox = {.v = {index_storage_is_readonly,
                                     index_storage_mailbox_enable,
                                     index_storage_mailbox_exists,
                                     rbox_mailbox_open,
                                     rbox_mailbox_close,
                                     index_storage_mailbox_free,
                                     rbox_mailbox_create,
                                     rbox_mailbox_update,
                                     index_storage_mailbox_delete,
                                     index_storage_mailbox_rename,
                                     index_storage_get_status,
                                     rbox_mailbox_get_metadata,
                                     index_storage_set_subscribed,
                                     index_storage_attribute_set,
                                     index_storage_attribute_get,
                                     index_storage_attribute_iter_init,
                                     index_storage_attribute_iter_next,
                                     index_storage_attribute_iter_deinit,
                                     index_storage_list_index_has_changed,
                                     index_storage_list_index_update_sync,
                                     rbox_storage_sync_init,
                                     index_mailbox_sync_next,
                                     index_mailbox_sync_deinit,
                                     NULL,
                                     rbox_notify_changes,
                                     index_transaction_begin,
                                     index_transaction_commit,
                                     index_transaction_rollback,
                                     NULL,
                                     rbox_mail_alloc,
                                     index_storage_search_init,
                                     index_storage_search_deinit,
                                     index_storage_search_next_nonblock,
                                     index_storage_search_next_update_seq,
                                     rbox_save_alloc,
                                     rbox_save_begin,
                                     rbox_save_continue,
                                     rbox_save_finish,
                                     rbox_save_cancel,
                                     rbox_copy,
                                     rbox_transaction_save_commit_pre,
                                     rbox_transaction_save_commit_post,
                                     rbox_transaction_save_rollback,
                                     index_storage_is_inconsistent}};
*/

struct dbox_storage_vfuncs rbox_dbox_storage_vfuncs = {rbox_file_free,
                                                       rbox_file_create_fd,
                                                       rbox_mail_open,
                                                       rbox_mailbox_create_indexes,
                                                       rbox_get_attachment_path_suffix,
                                                       rbox_set_mailbox_corrupted,
                                                       rbox_set_file_corrupted};
