/*
 * Copyright (c) 2017 Tallence AG and the authors
 *
 * This is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License version 2.1, as published by the Free Software
 * Foundation.  See file COPYING.
 */
#ifndef SRC_LIBRMB_TESTING_MOCK_TEST_H_
#define SRC_LIBRMB_TESTING_MOCK_TEST_H_

#include "interfaces/rados-storage-interface.h"
#include "interfaces/rados-dictionary-interface.h"
#include "interfaces/rados-cluster-interface.h"

#include "gmock/gmock.h"

namespace librmbtest {
using namespace librmb;

class RadosStorageMock : public RadosStorage {
 public:
  MOCK_METHOD0(get_io_ctx, librados::IoCtx &());
  MOCK_METHOD3(stat_object, int(const std::string &oid, uint64_t *psize, time_t *pmtime));
  MOCK_METHOD1(set_namespace, void(const std::string &nspace));
  MOCK_METHOD0(get_max_write_size, int());
  MOCK_METHOD0(get_max_write_size_bytes, int());
  MOCK_METHOD5(split_buffer_and_exec_op, int(const char *buffer, size_t buffer_length, RadosMailObject *current_object,
                                             librados::ObjectWriteOperation *write_op_xattr, uint64_t max_write));
  MOCK_METHOD3(read_mail, int(const std::string &oid, uint64_t *size_r, char *mail_buffer));
  MOCK_METHOD1(load_xattr, int(RadosMailObject *mail));
  MOCK_METHOD2(set_xattr, int(const std::string &oid, RadosXAttr &xattr));

  MOCK_METHOD1(delete_mail, int(RadosMailObject *mail));
  MOCK_METHOD1(delete_mail, int(std::string oid));
  MOCK_METHOD4(aio_operate, int(librados::IoCtx *io_ctx_, const std::string &oid, librados::AioCompletion *c,
                                librados::ObjectWriteOperation *op));
  MOCK_METHOD1(find_objects, librados::NObjectIterator(RadosXAttr *attr));
  MOCK_METHOD2(open_connection, int(const std::string &poolname, const std::string &ns));
};

class RadosDictionaryMock : public RadosDictionary {
 public:
  MOCK_METHOD1(get_full_oid, const std::string(const std::string &key));
  MOCK_METHOD0(get_shared_oid, const std::string());
  MOCK_METHOD0(get_private_oid, const std::string());
  MOCK_METHOD0(get_oid, const std::string &());
  MOCK_METHOD0(get_username, const std::string &());
  MOCK_METHOD0(get_io_ctx, librados::IoCtx &());
  MOCK_METHOD1(remove_completion, void(librados::AioCompletion *c));
  MOCK_METHOD1(push_back_completion, void(librados::AioCompletion *c));
  MOCK_METHOD0(wait_for_completions, void());
  MOCK_METHOD2(get, int(const std::string &key, std::string *value_r));
};

class RadosClusterMock : public RadosCluster {
 public:
  MOCK_METHOD1(init, int(std::string *error_r));
  MOCK_METHOD0(deinit, void());
  MOCK_METHOD1(pool_create, int(const std::string &pool));
  MOCK_METHOD1(io_ctx_create, int(const std::string &pool));
  MOCK_METHOD2(get_config_option, int(const char *option, std::string *value));
  MOCK_METHOD0(get_io_ctx, librados::IoCtx &());
};
}

#endif /* SRC_LIBRMB_TESTING_MOCK_TEST_H_ */