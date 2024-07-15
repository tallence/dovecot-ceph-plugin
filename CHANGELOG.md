# Change Log

## Next
- fix: spelling error in README.md

## [1.0.0](https://github.com/ceph-dovecot/dovecot-ceph-plugin/tree/1.0.0) (2023-03-23)
- prod release
## [0.0.52](https://github.com/ceph-dovecot/dovecot-ceph-plugin/tree/0.0.52) (2023-02-27)
- fix: some problems with virtual box and Spica

## [0.0.51](https://github.com/ceph-dovecot/dovecot-ceph-plugin/tree/0.0.51) (2023-02-09)
- fix: not escaped % in i_warning.

## [0.0.50](https://github.com/ceph-dovecot/dovecot-ceph-plugin/tree/0.0.50) (2023-02-02)
- fix: cleanup ceph-index size calculation

## [0.0.49](https://github.com/ceph-dovecot/dovecot-ceph-plugin/tree/0.0.49) (2023-01-29)
- fix: cleanup ceph-index in case of mailbox INBOX delete

## [0.0.48](https://github.com/ceph-dovecot/dovecot-ceph-plugin/tree/0.0.48) (2023-01-26)
- cleanup ceph-index in case of mailbox INBOX delete

## [0.0.47](https://github.com/ceph-dovecot/dovecot-ceph-plugin/tree/0.0.47) (2022-12-05)
- #355 fix gzip trailer when stream is empty
       fix save_method 1+2 buffersize (1 byte short) 
       bugfix-355-fix-buffersize-write-method

## [0.0.46](https://github.com/ceph-dovecot/dovecot-ceph-plugin/tree/0.0.46) (2022-11-23)
- #349 bugfix doveadm rmb create ceph index validate object metadata

## [0.0.45](https://github.com/ceph-dovecot/dovecot-ceph-plugin/tree/0.0.45) (2022-11-22)
- #349 bugfix doveadm rmb return code not set

## [0.0.44](https://github.com/ceph-dovecot/dovecot-ceph-plugin/tree/0.0.44) (2022-11-21)
- #349 additional recovery method (ceph index object)

## [0.0.43](https://github.com/ceph-dovecot/dovecot-ceph-plugin/tree/0.0.43) (2022-10-27)
- #346 segmentation fault (rbox_copy) if rbox_mail is null

## [0.0.42](https://github.com/ceph-dovecot/dovecot-ceph-plugin/tree/0.0.42) (2022-10-18)
- #346 segmentation fault (rbox_copy) if rbox_mail is null

## [0.0.41](https://github.com/ceph-dovecot/dovecot-ceph-plugin/tree/0.0.41) (2022-09-27)
- #342 multithreading bugfix and additional logging        

## [0.0.40](https://github.com/ceph-dovecot/dovecot-ceph-plugin/tree/0.0.40) (2022-09-22)
- #342 multithreading object search for doveadm force-resync (feature toggle) 
       new config params: 
       # search method default = 0 | 1 multithreading
       rbox_object_search_method=1 
       # number of threads to use in case of search_method=1
       rbox_object_search_threads=4

## [0.0.39](https://github.com/ceph-dovecot/dovecot-ceph-plugin/tree/0.0.39) (2022-08-25)
- #339 fail with assert if rados_config cannot be found due to network/connection issue 
       retry ceph read operations / read / xattr with timeout 

## [0.0.38](https://github.com/ceph-dovecot/dovecot-ceph-plugin/tree/0.0.38) (2022-06-24)
- Fix losing \r when saving mail from \n source

## [0.0.37](https://github.com/ceph-dovecot/dovecot-ceph-plugin/tree/0.0.37) (2022-05-23)
- #332: quota: notify message count and type invalid for imap move operation

## [0.0.36](https://github.com/ceph-dovecot/dovecot-ceph-plugin/tree/0.0.36) (2022-05-19)
- #319: force-resync: immediatelly assign unassigned objects to inbox 
- #328: fix segmentation fault copy mail from virtual mailbox

## [0.0.35](https://github.com/ceph-dovecot/dovecot-ceph-plugin/tree/0.0.35) (2022-05-05)
- #322: rbox_write_method parameter with implemtnation of different ways to save huge mails to rados

## [0.0.34](https://github.com/ceph-dovecot/dovecot-ceph-plugin/tree/0.0.34) (2022-05-03)
- #322: [BUGFIX] memory crash appending big attachments (bufferlist)
- #322: [CONFIGURATION] new configuration setting rbox_chunk_size with default 10240 Bytes 

## [0.0.33](https://github.com/ceph-dovecot/dovecot-ceph-plugin/tree/0.0.33) (2022-04-27)
- #316: wait synchronously for rados write operations

## [0.0.32](https://github.com/ceph-dovecot/dovecot-ceph-plugin/tree/0.0.32) (2022-04-05)
- #313: fix crash if append is interrupted. 

## [0.0.31](https://github.com/ceph-dovecot/dovecot-ceph-plugin/tree/0.0.31) (2022-04-03)
- #304: force-resync: preserve mail flags 
- #306: force-resync: restore all mail objects to inbox in case they have no reference to existing mailboxes
- #310: save-mail: check ceph dove size option, if mail size is bigger abort save.

## [0.0.30](https://github.com/ceph-dovecot/dovecot-ceph-plugin/tree/0.0.30) (2022-03-14)

- bugfix: retry ceph operation in case of connection timeout

## [0.0.29](https://github.com/ceph-dovecot/dovecot-ceph-plugin/tree/0.0.29) (2022-03-10)

- bugfix: force-resync
- bugfix: set mail as expunged.

## [0.0.28](https://github.com/ceph-dovecot/dovecot-ceph-plugin/tree/0.0.28) (2022-02-28)


- bugfix: wait for metadata copy before updating index (MOVE Mail)
- enhancement: in case we have more then one mail process (imap, pop3,..) running at the same time, 
               do not print warning message if mail access fails due to old index entry .       

## [0.0.27](https://github.com/ceph-dovecot/dovecot-ceph-plugin/tree/0.0.27) (2022-02-28)

- bugfix initialisation rados_mail->deprecated_uid

## [0.0.26](https://github.com/ceph-dovecot/dovecot-ceph-plugin/tree/0.0.26) (2022-02-28)

- support deprecated uuid format RECORD and MICROSOFT

## [0.0.25](https://github.com/ceph-dovecot/dovecot-ceph-plugin/tree/0.0.25) (2022-02-23)

- virtual_mailbox: bugfix fetch fields (x-guid, date.saved..)

## [0.0.24](https://github.com/ceph-dovecot/dovecot-ceph-plugin/tree/0.0.24) (2022-02-07)

- list namespace object only once, in case of force-resync

## [0.0.23](https://github.com/ceph-dovecot/dovecot-ceph-plugin/tree/0.0.23) (2021-08-09)

- Support SLES 15
- Support Dovecot 2.3.15
- Support Ceph v14.2.x

## [0.0.22](https://github.com/ceph-dovecot/dovecot-ceph-plugin/tree/0.0.22)
**upgrade ceph version**
- upgrade ceph version 12.2.12 
- build against dovecot 2.3.13

## [0.0.21](https://github.com/ceph-dovecot/dovecot-ceph-plugin/tree/0.0.21)

[Full Changelog](https://github.com/ceph-dovecot/dovecot-ceph-plugin/compare/0.0.20...0.0.21)

**Implemented enhancements:**

- pass ceph client configuration via 90-plugin to [\#250](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/250)

**Fixed bugs:**

- doveadm force-resync & virtual Namespace [\#249](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/249)

## [0.0.20](https://github.com/ceph-dovecot/dovecot-ceph-plugin/tree/0.0.20) (2019-02-11)
[Full Changelog](https://github.com/ceph-dovecot/dovecot-ceph-plugin/compare/0.0.19...0.0.20)

**Implemented enhancements:**

- doveadm rmb  [\#247](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/247)
- Performance: rbox backup [\#246](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/246)

**Fixed bugs:**

- Performance: rbox backup [\#246](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/246)
- doveadm rmb check indices shows duplicate folder in output. [\#224](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/224)

**Merged pull requests:**

- Doveadm rmb update jrse & performance [\#248](https://github.com/ceph-dovecot/dovecot-ceph-plugin/pull/248) ([jrse](https://github.com/jrse))

## [0.0.19](https://github.com/ceph-dovecot/dovecot-ceph-plugin/tree/0.0.19) (2019-02-06)
[Full Changelog](https://github.com/ceph-dovecot/dovecot-ceph-plugin/compare/0.0.18...0.0.19)

**Implemented enhancements:**

- MetadataStorage Module: \(improvement\) [\#243](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/243)
- remove duplicate get\_metadata function [\#242](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/242)

**Fixed bugs:**

- sdbox-\>rbox changes [\#244](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/244)
- remove duplicate get\\_metadata function [\#242](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/242)

**Merged pull requests:**

- Metadata improvements jrse + zlib fix \(read buffer\) [\#245](https://github.com/ceph-dovecot/dovecot-ceph-plugin/pull/245) ([jrse](https://github.com/jrse))

## [0.0.18](https://github.com/ceph-dovecot/dovecot-ceph-plugin/tree/0.0.18) (2019-01-25)
[Full Changelog](https://github.com/ceph-dovecot/dovecot-ceph-plugin/compare/0.0.17...0.0.18)

**Implemented enhancements:**

- restore mail guid if not in mail extension header [\#238](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/238)
- rbox mail optimizations: [\#233](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/233)

**Fixed bugs:**

- zlib plugin: broken physical size! [\#239](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/239)
- restore mail guid if not in mail extension header [\#238](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/238)
- Dictionary plugin unit test fail [\#237](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/237)
- Guid Metadata [\#234](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/234)

**Merged pull requests:**

- \#239: invalid reinterpret\_cast in istream\_bufferlist  [\#241](https://github.com/ceph-dovecot/dovecot-ceph-plugin/pull/241) ([jrse](https://github.com/jrse))
- Jrse \#238\#237 [\#240](https://github.com/ceph-dovecot/dovecot-ceph-plugin/pull/240) ([jrse](https://github.com/jrse))
- release 0.0.18 preparations  CHANGELOG and version info in configure.ac and .spec file [\#236](https://github.com/ceph-dovecot/dovecot-ceph-plugin/pull/236) ([jrse](https://github.com/jrse))
- PR: Code Cleanup \#233, \#234 and missing \0 for mail metadata and mail \(if not compressed\) [\#235](https://github.com/ceph-dovecot/dovecot-ceph-plugin/pull/235) ([jrse](https://github.com/jrse))

## [0.0.17](https://github.com/ceph-dovecot/dovecot-ceph-plugin/tree/0.0.17) (2019-01-14)
[Full Changelog](https://github.com/ceph-dovecot/dovecot-ceph-plugin/compare/0.0.16...0.0.17)

**Fixed bugs:**

- fetching pop3.uidl leads to rados storage metadata \(omap\) read [\#230](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/230)

**Merged pull requests:**

- release preparations and CHANGELOG [\#232](https://github.com/ceph-dovecot/dovecot-ceph-plugin/pull/232) ([jrse](https://github.com/jrse))
- Pop3 uidl handling \#230 [\#231](https://github.com/ceph-dovecot/dovecot-ceph-plugin/pull/231) ([jrse](https://github.com/jrse))

## [0.0.16](https://github.com/ceph-dovecot/dovecot-ceph-plugin/tree/0.0.16) (2018-12-18)
[Full Changelog](https://github.com/ceph-dovecot/dovecot-ceph-plugin/compare/0.0.15...0.0.16)

**Implemented enhancements:**

- use shared ptr instead of raw pointer [\#121](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/121)

**Fixed bugs:**

- reusing the rbox\_save\_context [\#225](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/225)
- rbox\_set\_expunge =\> index rebuild [\#222](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/222)
- backup from rbox -\> mdbox : [\#220](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/220)

**Closed issues:**

- iredmail 0.98 \(Dovecot 2.2.33\) on Ubuntu 18.04 LTS - diverse problems [\#210](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/210)

**Merged pull requests:**

- \#185: fix return value assignment, open\_connection: set\_ceph\_wait\_method [\#228](https://github.com/ceph-dovecot/dovecot-ceph-plugin/pull/228) ([jrse](https://github.com/jrse))
- Jrse \#222 [\#227](https://github.com/ceph-dovecot/dovecot-ceph-plugin/pull/227) ([jrse](https://github.com/jrse))
- Merge pull request \#223 from ceph-dovecot/jrse\_\#222 [\#226](https://github.com/ceph-dovecot/dovecot-ceph-plugin/pull/226) ([jrse](https://github.com/jrse))
- Jrse \#222 [\#223](https://github.com/ceph-dovecot/dovecot-ceph-plugin/pull/223) ([jrse](https://github.com/jrse))
- \#220: added \#ifdef around the warning message. If a metadata is not s… [\#221](https://github.com/ceph-dovecot/dovecot-ceph-plugin/pull/221) ([jrse](https://github.com/jrse))

## [0.0.15](https://github.com/ceph-dovecot/dovecot-ceph-plugin/tree/0.0.15) (2018-11-26)
[Full Changelog](https://github.com/ceph-dovecot/dovecot-ceph-plugin/compare/0.0.14...0.0.15)

**Fixed bugs:**

- doveadm rmb revert =\> does return count of deleted files instead of 0 in case of no error. [\#218](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/218)
- doveadm force-resync restore mail \(rbox\_sync\) [\#215](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/215)

**Merged pull requests:**

- Rbox sync rebuild \#215 [\#219](https://github.com/ceph-dovecot/dovecot-ceph-plugin/pull/219) ([jrse](https://github.com/jrse))

## [0.0.14](https://github.com/ceph-dovecot/dovecot-ceph-plugin/tree/0.0.14) (2018-11-22)
[Full Changelog](https://github.com/ceph-dovecot/dovecot-ceph-plugin/compare/0.0.13...0.0.14)

**Fixed bugs:**

- Signal 11: errors in dovecot log [\#207](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/207)
- Casting enum rbox\_metadata\_key to string failes [\#204](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/204)

**Closed issues:**

- ceph wait callbacks [\#212](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/212)
- compare master 2.3 sdbox storage module with the current rbox storage plugin, and apply changes [\#209](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/209)
- dovecot.index reset, view is inconsistent [\#205](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/205)
- Logmessage: Error: Librados obj: a9cd162ed243bf5b8f150000c86de11e, could not be removed  [\#203](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/203)
- Remove Debug messages \(Flag evaluation / Rebuild\) [\#202](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/202)
- Update user handbook Configuration [\#201](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/201)
- Use linux error names instead of error codes in logfile [\#200](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/200)
- is the rmb tool really necessary? [\#199](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/199)
- Fix compiler warnings [\#194](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/194)
- imaptest error messages [\#191](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/191)
- dovadm rmb plugin / rmb tool [\#190](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/190)
- Mail delivery fails on CentOS 7.5 [\#159](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/159)

**Merged pull requests:**

- Jrse 0.0.14 [\#214](https://github.com/ceph-dovecot/dovecot-ceph-plugin/pull/214) ([jrse](https://github.com/jrse))
- Jrse \#212 [\#213](https://github.com/ceph-dovecot/dovecot-ceph-plugin/pull/213) ([jrse](https://github.com/jrse))
- Jrse \#209 [\#211](https://github.com/ceph-dovecot/dovecot-ceph-plugin/pull/211) ([jrse](https://github.com/jrse))
- Jrse minor and minor fixes  [\#208](https://github.com/ceph-dovecot/dovecot-ceph-plugin/pull/208) ([jrse](https://github.com/jrse))
- fix: doveadm rmb plugin crash.  [\#193](https://github.com/ceph-dovecot/dovecot-ceph-plugin/pull/193) ([jrse](https://github.com/jrse))

## [0.0.13](https://github.com/ceph-dovecot/dovecot-ceph-plugin/tree/0.0.13) (2018-09-05)
[Full Changelog](https://github.com/ceph-dovecot/dovecot-ceph-plugin/compare/0.0.12...0.0.13)

**Implemented enhancements:**

- rbox\_save\_update\_header\_flags before commiting save transaction [\#183](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/183)
- add changelog file [\#168](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/168)

**Fixed bugs:**

- Thread::try\_create\(\): pthread\_create failed with error 11 [\#188](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/188)
- doveadm backup \(rbox-\> mdbox\) stops if mailbox index has invalid entries [\#182](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/182)

**Merged pull requests:**

- preparations for v0.13 [\#192](https://github.com/ceph-dovecot/dovecot-ceph-plugin/pull/192) ([jrse](https://github.com/jrse))
- Jrse cleanup [\#187](https://github.com/ceph-dovecot/dovecot-ceph-plugin/pull/187) ([jrse](https://github.com/jrse))
- Jrse \#182 [\#186](https://github.com/ceph-dovecot/dovecot-ceph-plugin/pull/186) ([jrse](https://github.com/jrse))
- Update issue templates [\#184](https://github.com/ceph-dovecot/dovecot-ceph-plugin/pull/184) ([jrse](https://github.com/jrse))
- Jrse changelog [\#181](https://github.com/ceph-dovecot/dovecot-ceph-plugin/pull/181) ([jrse](https://github.com/jrse))

## [0.0.12](https://github.com/ceph-dovecot/dovecot-ceph-plugin/tree/0.0.12) (2018-07-18)
[Full Changelog](https://github.com/ceph-dovecot/dovecot-ceph-plugin/compare/0.0.11...0.0.12)

**Implemented enhancements:**

- doveadm rmb unit tests [\#174](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/174)
- doveadm rmb ls  shows orphaned objects [\#172](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/172)
- create delete all objects command for rmb CLI [\#171](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/171)
- Ls orphaned objects \#172 [\#177](https://github.com/ceph-dovecot/dovecot-ceph-plugin/pull/177) ([jrse](https://github.com/jrse))
- Doveadm rmb unit tests \#174 [\#176](https://github.com/ceph-dovecot/dovecot-ceph-plugin/pull/176) ([jrse](https://github.com/jrse))
- \#171: supports rmb -u \<user\> delete - --yes-i-really-really-mean-it [\#173](https://github.com/ceph-dovecot/dovecot-ceph-plugin/pull/173) ([jrse](https://github.com/jrse))

**Fixed bugs:**

- doveadm rmb delete crashes if object doesn't exist [\#175](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/175)

**Closed issues:**

- cleanup log messages and disable entry-exit function log by default [\#178](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/178)

**Merged pull requests:**

- release version 0.0.12 [\#180](https://github.com/ceph-dovecot/dovecot-ceph-plugin/pull/180) ([jrse](https://github.com/jrse))
- Jrse cleanup log \#178 [\#179](https://github.com/ceph-dovecot/dovecot-ceph-plugin/pull/179) ([jrse](https://github.com/jrse))

## [0.0.11](https://github.com/ceph-dovecot/dovecot-ceph-plugin/tree/0.0.11) (2018-07-10)
[Full Changelog](https://github.com/ceph-dovecot/dovecot-ceph-plugin/compare/0.0.10...0.0.11)

**Implemented enhancements:**

- Savelog: handle move operations differently [\#156](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/156)
- Restore Index \(update xattributes\) [\#155](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/155)
- doveadm force-resync -\> repair all user mailboxes at once [\#149](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/149)
- doveadm force-resync extension to clean up unreferenced objects [\#147](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/147)
- doveadm rbox check -u user [\#113](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/113)

**Fixed bugs:**

- Some more SCA fixes [\#162](https://github.com/ceph-dovecot/dovecot-ceph-plugin/pull/162) ([dalgaaf](https://github.com/dalgaaf))

**Closed issues:**

- use imaptest copybox to eval. copy  [\#165](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/165)
- modify spec file to copy doveadm rmb plugin to doveadm plugin directory [\#164](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/164)
- doveadm rmb mailbox delete cmd [\#163](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/163)
- Delete UserAccount [\#108](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/108)

**Merged pull requests:**

- Jrse 2018 06 29 \#165 [\#170](https://github.com/ceph-dovecot/dovecot-ceph-plugin/pull/170) ([jrse](https://github.com/jrse))
- 20180604 jrse\#156 [\#169](https://github.com/ceph-dovecot/dovecot-ceph-plugin/pull/169) ([jrse](https://github.com/jrse))
- 20180604 jrse \#156 [\#167](https://github.com/ceph-dovecot/dovecot-ceph-plugin/pull/167) ([jrse](https://github.com/jrse))
- Jrse 2018 06 29 \#165 [\#166](https://github.com/ceph-dovecot/dovecot-ceph-plugin/pull/166) ([jrse](https://github.com/jrse))

## [0.0.10](https://github.com/ceph-dovecot/dovecot-ceph-plugin/tree/0.0.10) (2018-06-04)
[Full Changelog](https://github.com/ceph-dovecot/dovecot-ceph-plugin/compare/0.0.9...0.0.10)

**Implemented enhancements:**

- create a logfile which contains all added mail objects [\#148](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/148)
- check for invalid mail objects in user namespace [\#142](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/142)

**Fixed bugs:**

- doveadm force resync \(repair\) without index file [\#150](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/150)
- imap process killed with signal 6 \(copy failure\) [\#143](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/143)
- fixes for g++ and clang++ compiler warnings [\#158](https://github.com/ceph-dovecot/dovecot-ceph-plugin/pull/158) ([dalgaaf](https://github.com/dalgaaf))
- Various fixes from SCA [\#157](https://github.com/ceph-dovecot/dovecot-ceph-plugin/pull/157) ([dalgaaf](https://github.com/dalgaaf))

**Closed issues:**

- Setup "real" ceph cluster [\#104](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/104)

**Merged pull requests:**

- removed regex, due to build issues on suse server [\#160](https://github.com/ceph-dovecot/dovecot-ceph-plugin/pull/160) ([jrse](https://github.com/jrse))
- Fixes from SCA [\#154](https://github.com/ceph-dovecot/dovecot-ceph-plugin/pull/154) ([dalgaaf](https://github.com/dalgaaf))
- Logfile \#148 [\#151](https://github.com/ceph-dovecot/dovecot-ceph-plugin/pull/151) ([jrse](https://github.com/jrse))

## [0.0.9](https://github.com/ceph-dovecot/dovecot-ceph-plugin/tree/0.0.9) (2018-05-23)
[Full Changelog](https://github.com/ceph-dovecot/dovecot-ceph-plugin/compare/0.0.8-cpy-rmb-fix...0.0.9)

**Merged pull requests:**

- Rmb fix [\#146](https://github.com/ceph-dovecot/dovecot-ceph-plugin/pull/146) ([jrse](https://github.com/jrse))

## [0.0.8-cpy-rmb-fix](https://github.com/ceph-dovecot/dovecot-ceph-plugin/tree/0.0.8-cpy-rmb-fix) (2018-05-23)
[Full Changelog](https://github.com/ceph-dovecot/dovecot-ceph-plugin/compare/0.0.8...0.0.8-cpy-rmb-fix)

**Implemented enhancements:**

- Use dbox alternate storage ALT=... as alternate pool name [\#62](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/62)

**Merged pull requests:**

- Fix some smaller issues [\#141](https://github.com/ceph-dovecot/dovecot-ceph-plugin/pull/141) ([dalgaaf](https://github.com/dalgaaf))

## [0.0.8](https://github.com/ceph-dovecot/dovecot-ceph-plugin/tree/0.0.8) (2018-05-15)
[Full Changelog](https://github.com/ceph-dovecot/dovecot-ceph-plugin/compare/0.0.7...0.0.8)

**Closed issues:**

- Thread::try\_create\(\): pthread\_create failed with error 11 [\#139](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/139)
- pop3 travis test [\#138](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/138)
- Inbox.Inbox mailbox [\#134](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/134)

## [0.0.7](https://github.com/ceph-dovecot/dovecot-ceph-plugin/tree/0.0.7) (2018-05-03)
[Full Changelog](https://github.com/ceph-dovecot/dovecot-ceph-plugin/compare/0.0.6...0.0.7)

## [0.0.6](https://github.com/ceph-dovecot/dovecot-ceph-plugin/tree/0.0.6) (2018-04-20)
[Full Changelog](https://github.com/ceph-dovecot/dovecot-ceph-plugin/compare/0.0.5...0.0.6)

**Implemented enhancements:**

- RadosDictionary: atomic Increment / Decrement [\#132](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/132)

**Fixed bugs:**

- copy mail from raw\_storage \(lmtp\) [\#136](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/136)
- copy / move mail Error [\#135](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/135)

**Closed issues:**

- rmb tool \(unknown object in storage pool\) [\#137](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/137)
- Fork imap process [\#133](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/133)

## [0.0.5](https://github.com/ceph-dovecot/dovecot-ceph-plugin/tree/0.0.5) (2018-04-16)
[Full Changelog](https://github.com/ceph-dovecot/dovecot-ceph-plugin/compare/0.0.4...0.0.5)

**Implemented enhancements:**

- travis ci, mount cephfs  [\#126](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/126)

## [0.0.4](https://github.com/ceph-dovecot/dovecot-ceph-plugin/tree/0.0.4) (2018-04-03)
[Full Changelog](https://github.com/ceph-dovecot/dovecot-ceph-plugin/compare/0.0.3...0.0.4)

**Implemented enhancements:**

- travis CI support for imaptests [\#97](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/97)

**Fixed bugs:**

- doveadm force-resync \(rbox\) [\#130](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/130)
- zlib: error trailer has wrong crc [\#129](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/129)

**Closed issues:**

- Write all Immutable Mail metadata to single xattribute [\#124](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/124)
- rmb tool display flag names instead of hex value [\#120](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/120)
- Unable to find the jansson headers [\#114](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/114)
- Unit test update / remove Flags and keywords [\#105](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/105)
- Integrationtest: Use ceph fs for index files and cache [\#103](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/103)

## [0.0.3](https://github.com/ceph-dovecot/dovecot-ceph-plugin/tree/0.0.3) (2018-02-22)
[Full Changelog](https://github.com/ceph-dovecot/dovecot-ceph-plugin/compare/0.0.2...0.0.3)

**Fixed bugs:**

- disabling all xattributes [\#123](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/123)
- zlib and dovecot master  [\#112](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/112)

**Closed issues:**

- ceph compression hint for objectoperation [\#122](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/122)
- backup mdbox -\> rbox \(receive.date\) [\#119](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/119)
- backup mdbox  -\> rbox [\#118](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/118)
- configuration: rbox\_pool\_name not used \(backup\) [\#117](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/117)
- Rados dictionary \(buffer assertion\) [\#116](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/116)
- testing with one mailbox [\#115](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/115)
- Rbox read mail \(buffer\) [\#102](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/102)

## [0.0.2](https://github.com/ceph-dovecot/dovecot-ceph-plugin/tree/0.0.2) (2017-12-11)
**Implemented enhancements:**

- save and update metadata configuration [\#98](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/98)
- librmb, review interfaces [\#93](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/93)
- add googletest: read\_mail [\#92](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/92)
- googletest for copy and move mail [\#80](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/80)
- read mail, unnecessary stat? [\#79](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/79)
- copy mail issue, \(copy input stream to output stream\) [\#78](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/78)
- Remove debug\_print\_...\(\) functions [\#76](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/76)
- Support Dovecot 2.3.x [\#74](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/74)
- librmd comand line tool \(basic\) [\#70](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/70)
- Additional index restore function [\#69](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/69)
- Add config parameter to save mail flags [\#64](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/64)

**Fixed bugs:**

- copy mail : creating a mail duplicate [\#111](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/111)
- Quota reached -\> exception  [\#110](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/110)
- Dictionary and Quota plugin [\#100](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/100)
- segv in rbox\_save\_begin with Dovecot 2.2.21 [\#73](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/73)
- delete mailbox with active dict-rados crashes [\#39](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/39)
- Check lifecycle of rbox\_mail\_alloc [\#37](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/37)
- bad\_alloc exception while reading / writing huge mails ~26mb from rados into std::string buffer  [\#33](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/33)

**Closed issues:**

- Ceph Namespace for user emails [\#109](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/109)
- log errors on error level with RADOS errno [\#107](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/107)
- imap crashes with signal 11 if rados connect fails [\#106](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/106)
- Rmbtool -p default pool [\#101](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/101)
- Integration test sync\_rbox\_2 [\#99](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/99)
- Travis CI support for integrationtests [\#96](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/96)
- Test for LDA [\#95](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/95)
- rmb tool - write manpage [\#94](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/94)
- librmb headers are not installed via 'make install' [\#88](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/88)
- make distcheck not working [\#86](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/86)
- make dist does not package all needed files to build [\#82](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/82)
- integrate googlemock [\#75](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/75)
- Remove all compiler/linker warnings [\#72](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/72)
- Inspect source code with valgrind [\#71](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/71)
- Integrate Google test framework [\#66](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/66)
- Ensure that Dovecots zlib-plugin is working with storage-rbox [\#63](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/63)
- doveadm force-resync does not work [\#61](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/61)
- separate librmb in own git repo [\#60](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/60)
- build RPM package for SUSE [\#58](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/58)
- move mail leads to copy -\> expunge  [\#57](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/57)
- Postpone RADOS cluster initialization to allow lightweight index operations [\#56](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/56)
- Test doveadm move/copy [\#55](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/55)
- Add support for Dovecot mailbox settings [\#54](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/54)
- Test doveadm force-resync [\#53](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/53)
- Use username as RADOS namespace [\#52](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/52)
- Save more immutable mail attributes in the mail object  [\#51](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/51)
- Test doveadm sync mailbox conversion [\#50](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/50)
- Envelop Changed imaptest failure [\#49](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/49)
- Change default name for Dict pool to mail\_dictionaries [\#48](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/48)
- test XATTR \(copy, save\) [\#47](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/47)
- test ceph-dovecot plugin with dovcot-lda [\#46](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/46)
- test dovecot-ceph plugin  LMTP [\#45](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/45)
- Update ceph-dovecot readme [\#44](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/44)
- imaptest \(imap\) [\#43](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/43)
- imaptest \(pop3\) [\#42](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/42)
- Save Xattr data as String \(not binary\) [\#41](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/41)
- make sure mtime is set correctly \(copy mail\) [\#40](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/40)
- rados max file size [\#38](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/38)
- manual tests Delete/Copy/Add Mails [\#36](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/36)
- analyze sync functionality [\#35](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/35)
-  add  asynchronous \(write\) wait\_for\_completion to appropriate dovecot transaction lifecycle method [\#34](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/34)
- Write buffer  [\#31](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/31)
- copy mail [\#30](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/30)
- delete mail [\#29](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/29)
- Rename storage-rados module [\#28](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/28)
- use rados object operations to set / read object xattributes and object data [\#27](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/27)
- Analyse how index\_mail\_get\_/ set\_physical\_size works [\#26](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/26)
- get mails physical size from rados if it can not be read from rados [\#25](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/25)
- use "real" guid to store and read rados objects  [\#24](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/24)
- delete rados mail object in case transaction abort [\#23](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/23)
- Write Rados object asynchronous [\#21](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/21)
- dict-rados - check memory usage [\#19](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/19)
- Define ceph mailbox datatype [\#17](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/17)
- Define RBox-storage Mail datastructure [\#16](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/16)
- pass ceph configuration to rbox-storage plugin [\#15](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/15)
- Ceph Day Germany: Begin of November, Frankfurt Area [\#14](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/14)
- Ceph Day Netherlands: September 20th, EDE [\#13](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/13)
- Abstract Cephalocon 2017 [\#12](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/12)
- Research: Index creation obox [\#11](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/11)
- setup dev/test environment, code: rbox, dict-rados [\#10](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/10)
- create ceph connection class [\#9](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/9)
- creation of mail GUIDs [\#8](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/8)
- research: ceph io context initialisation [\#7](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/7)
- read mail attributes from rados [\#6](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/6)
- save mail attributes in rados [\#5](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/5)
- rbox debug log [\#4](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/4)
- read rados object [\#3](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/3)
- Save rados object [\#2](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/2)
- Test Issue [\#1](https://github.com/ceph-dovecot/dovecot-ceph-plugin/issues/1)

**Merged pull requests:**

- make distcheck [\#90](https://github.com/ceph-dovecot/dovecot-ceph-plugin/pull/90) ([peter-mauritius](https://github.com/peter-mauritius))
- fix indentation and trailing whitespaces [\#89](https://github.com/ceph-dovecot/dovecot-ceph-plugin/pull/89) ([dalgaaf](https://github.com/dalgaaf))
- update spec file with versio from OBS [\#87](https://github.com/ceph-dovecot/dovecot-ceph-plugin/pull/87) ([dalgaaf](https://github.com/dalgaaf))
- make dist not complete [\#85](https://github.com/ceph-dovecot/dovecot-ceph-plugin/pull/85) ([peter-mauritius](https://github.com/peter-mauritius))
- ignore some files from the tests subdirectory [\#84](https://github.com/ceph-dovecot/dovecot-ceph-plugin/pull/84) ([dalgaaf](https://github.com/dalgaaf))
- add script to generate archive for package build [\#83](https://github.com/ceph-dovecot/dovecot-ceph-plugin/pull/83) ([dalgaaf](https://github.com/dalgaaf))
- Travis support [\#81](https://github.com/ceph-dovecot/dovecot-ceph-plugin/pull/81) ([peter-mauritius](https://github.com/peter-mauritius))
- add Wido den Hollander to Thanks [\#77](https://github.com/ceph-dovecot/dovecot-ceph-plugin/pull/77) ([dalgaaf](https://github.com/dalgaaf))
- Fix some smaller code issues [\#59](https://github.com/ceph-dovecot/dovecot-ceph-plugin/pull/59) ([dalgaaf](https://github.com/dalgaaf))
- Some smaller fast fixes [\#32](https://github.com/ceph-dovecot/dovecot-ceph-plugin/pull/32) ([dalgaaf](https://github.com/dalgaaf))
- Feature 2 16 -\> code review and merge  [\#22](https://github.com/ceph-dovecot/dovecot-ceph-plugin/pull/22) ([jrse](https://github.com/jrse))
- dict-rados works async now, namespace removed [\#18](https://github.com/ceph-dovecot/dovecot-ceph-plugin/pull/18) ([peter-mauritius](https://github.com/peter-mauritius))



\* *This Change Log was automatically generated by [github_changelog_generator](https://github.com/skywinder/Github-Changelog-Generator)*
