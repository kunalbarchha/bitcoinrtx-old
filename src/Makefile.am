DIST_SUBDIRS = secp256k1
AM_LDFLAGS = $(PTHREAD_CFLAGS) $(LIBTOOL_LDFLAGS)


if EMBEDDED_LEVELDB
LEVELDB_CPPFLAGS += -I$(srcdir)/leveldb/include
LEVELDB_CPPFLAGS += -I$(srcdir)/leveldb/helpers/memenv
LIBLEVELDB += $(builddir)/leveldb/libleveldb.a
LIBMEMENV  += $(builddir)/leveldb/libmemenv.a

# NOTE: This dependency is not strictly necessary, but without it make may try to build both in parallel, which breaks the LevelDB build system in a race
$(LIBLEVELDB): $(LIBMEMENV)

$(LIBLEVELDB) $(LIBMEMENV):
	@echo "Building LevelDB ..." && $(MAKE) -C $(@D) $(@F) CXX="$(CXX)" \
	  CC="$(CC)" PLATFORM=$(TARGET_OS) AR="$(AR)" $(LEVELDB_TARGET_FLAGS) \
          OPT="$(CXXFLAGS) $(CPPFLAGS)"
endif

BITCOINRTX_CONFIG_INCLUDES=-I$(builddir)/config
BITCOINRTX_INCLUDES=-I$(builddir) -I$(builddir)/obj $(BOOST_CPPFLAGS) $(LEVELDB_CPPFLAGS) $(CRYPTO_CFLAGS) $(SSL_CFLAGS)

BITCOINRTX_INCLUDES += -I$(srcdir)/secp256k1/include

LIBBITCOINRTX_SERVER=libbitcoinrtx_server.a
LIBBITCOINRTX_WALLET=libbitcoinrtx_wallet.a
LIBBITCOINRTX_COMMON=libbitcoinrtx_common.a
LIBBITCOINRTX_CLI=libbitcoinrtx_cli.a
LIBBITCOINRTX_UTIL=libbitcoinrtx_util.a
LIBBITCOINRTX_CRYPTO=crypto/libbitcoinrtx_crypto.a
LIBBITCOINRTX_UNIVALUE=univalue/libbitcoinrtx_univalue.a
LIBBITCOINRTXQT=qt/libbitcoinrtxqt.a
LIBSECP256K1=secp256k1/libsecp256k1.la

$(LIBSECP256K1): $(wildcard secp256k1/src/*) $(wildcard secp256k1/include/*)
	$(AM_V_at)$(MAKE) $(AM_MAKEFLAGS) -C $(@D) $(@F)

# Make is not made aware of per-object dependencies to avoid limiting building parallelization
# But to build the less dependent modules first, we manually select their order here:
EXTRA_LIBRARIES = \
  crypto/libbitcoinrtx_crypto.a \
  libbitcoinrtx_util.a \
  libbitcoinrtx_common.a \
  univalue/libbitcoinrtx_univalue.a \
  libbitcoinrtx_server.a \
  libbitcoinrtx_cli.a
if ENABLE_WALLET
BITCOINRTX_INCLUDES += $(BDB_CPPFLAGS)
EXTRA_LIBRARIES += libbitcoinrtx_wallet.a
endif

if BUILD_BITCOINRTX_LIBS
lib_LTLIBRARIES = libbitcoinrtxconsensus.la
LIBBITCOINRTX_CONSENSUS=libbitcoinrtxconsensus.la
else
LIBBITCOINRTX_CONSENSUS=
endif

bin_PROGRAMS =
TESTS =

if BUILD_BITCOINRTXD
  bin_PROGRAMS += bitcoinrtxd
endif

if BUILD_BITCOINRTX_UTILS
  bin_PROGRAMS += bitcoinrtx-cli bitcoinrtx-tx
endif

.PHONY: FORCE
# bitcoinrtx core #
BITCOINRTX_CORE_H = \
  addrman.h \
  alert.h \
  allocators.h \
  amount.h \
  base58.h \
  bloom.h \
  chain.h \
  chainparams.h \
  chainparamsbase.h \
  chainparamsseeds.h \
  checkpoints.h \
  checkqueue.h \
  clientversion.h \
  coincontrol.h \
  coins.h \
  compat.h \
  compressor.h \
  primitives/block.h \
  primitives/transaction.h \
  core_io.h \
  crypter.h \
  db.h \
  eccryptoverify.h \
  ecwrapper.h \
  hash.h \
  init.h \
  key.h \
  keystore.h \
  leveldbwrapper.h \
  limitedmap.h \
  main.h \
  merkleblock.h \
  miner.h \
  mruset.h \
  netbase.h \
  net.h \
  noui.h \
  pow.h \
  protocol.h \
  pubkey.h \
  random.h \
  rpcclient.h \
  rpcprotocol.h \
  rpcserver.h \
  script/interpreter.h \
  script/script.h \
  script/sigcache.h \
  script/sign.h \
  script/standard.h \
  script/script_error.h \
  serialize.h \
  streams.h \
  sync.h \
  threadsafety.h \
  timedata.h \
  tinyformat.h \
  txdb.h \
  txmempool.h \
  ui_interface.h \
  uint256.h \
  undo.h \
  util.h \
  utilstrencodings.h \
  utilmoneystr.h \
  utiltime.h \
  version.h \
  wallet.h \
  wallet_ismine.h \
  walletdb.h \
  compat/sanity.h

JSON_H = \
  json/json_spirit.h \
  json/json_spirit_error_position.h \
  json/json_spirit_reader.h \
  json/json_spirit_reader_template.h \
  json/json_spirit_stream_reader.h \
  json/json_spirit_utils.h \
  json/json_spirit_value.h \
  json/json_spirit_writer.h \
  json/json_spirit_writer_template.h

obj/build.h: FORCE
	@$(MKDIR_P) $(builddir)/obj
	@$(top_srcdir)/share/genbuild.sh $(abs_top_builddir)/src/obj/build.h \
	  $(abs_top_srcdir)
libbitcoinrtx_util_a-clientversion.$(OBJEXT): obj/build.h

# server: shared between bitcoinrtxd and bitcoinrtx-qt
libbitcoinrtx_server_a_CPPFLAGS = $(BITCOINRTX_INCLUDES) $(MINIUPNPC_CPPFLAGS)
libbitcoinrtx_server_a_SOURCES = \
  addrman.cpp \
  alert.cpp \
  bloom.cpp \
  chain.cpp \
  checkpoints.cpp \
  init.cpp \
  leveldbwrapper.cpp \
  main.cpp \
  merkleblock.cpp \
  miner.cpp \
  net.cpp \
  noui.cpp \
  pow.cpp \
  rest.cpp \
  rpcblockchain.cpp \
  rpcmining.cpp \
  rpcmisc.cpp \
  rpcnet.cpp \
  rpcrawtransaction.cpp \
  rpcserver.cpp \
  script/sigcache.cpp \
  timedata.cpp \
  txdb.cpp \
  txmempool.cpp \
  $(JSON_H) \
  $(BITCOINRTX_CORE_H)

# wallet: shared between bitcoinrtxd and bitcoinrtx-qt, but only linked
# when wallet enabled
libbitcoinrtx_wallet_a_CPPFLAGS = $(BITCOINRTX_INCLUDES)
libbitcoinrtx_wallet_a_SOURCES = \
  db.cpp \
  crypter.cpp \
  rpcdump.cpp \
  rpcwallet.cpp \
  wallet.cpp \
  wallet_ismine.cpp \
  walletdb.cpp \
  $(BITCOINRTX_CORE_H)

# crypto primitives library
crypto_libbitcoinrtx_crypto_a_CPPFLAGS = $(BITCOINRTX_CONFIG_INCLUDES)
crypto_libbitcoinrtx_crypto_a_SOURCES = \
  crypto/sha1.cpp \
  crypto/sha256.cpp \
  crypto/sha512.cpp \
  crypto/hmac_sha256.cpp \
  crypto/rfc6979_hmac_sha256.cpp \
  crypto/hmac_sha512.cpp \
  crypto/ripemd160.cpp \
  crypto/common.h \
  crypto/sha256.h \
  crypto/sha512.h \
  crypto/hmac_sha256.h \
  crypto/rfc6979_hmac_sha256.h \
  crypto/hmac_sha512.h \
  crypto/sha1.h \
  crypto/ripemd160.h

# univalue JSON library
univalue_libbitcoinrtx_univalue_a_SOURCES = \
  univalue/univalue.cpp \
  univalue/univalue_read.cpp \
  univalue/univalue_write.cpp \
  univalue/univalue_escapes.h \
  univalue/univalue.h

# common: shared between bitcoinrtxd, and bitcoinrtx-qt and non-server tools
libbitcoinrtx_common_a_CPPFLAGS = $(BITCOINRTX_INCLUDES)
libbitcoinrtx_common_a_SOURCES = \
  allocators.cpp \
  amount.cpp \
  base58.cpp \
  chainparams.cpp \
  coins.cpp \
  compressor.cpp \
  primitives/block.cpp \
  primitives/transaction.cpp \
  core_read.cpp \
  core_write.cpp \
  eccryptoverify.cpp \
  ecwrapper.cpp \
  hash.cpp \
  key.cpp \
  keystore.cpp \
  netbase.cpp \
  protocol.cpp \
  pubkey.cpp \
  script/interpreter.cpp \
  script/script.cpp \
  script/sign.cpp \
  script/standard.cpp \
  script/script_error.cpp \
  $(BITCOINRTX_CORE_H)

# util: shared between all executables.
# This library *must* be included to make sure that the glibc
# backward-compatibility objects and their sanity checks are linked.
libbitcoinrtx_util_a_CPPFLAGS = $(BITCOINRTX_INCLUDES)
libbitcoinrtx_util_a_SOURCES = \
  compat/strnlen.cpp \
  compat/glibc_sanity.cpp \
  compat/glibcxx_sanity.cpp \
  chainparamsbase.cpp \
  clientversion.cpp \
  random.cpp \
  rpcprotocol.cpp \
  sync.cpp \
  uint256.cpp \
  util.cpp \
  utilstrencodings.cpp \
  utilmoneystr.cpp \
  utiltime.cpp \
  $(BITCOINRTX_CORE_H)

if GLIBC_BACK_COMPAT
libbitcoinrtx_util_a_SOURCES += compat/glibc_compat.cpp
libbitcoinrtx_util_a_SOURCES += compat/glibcxx_compat.cpp
endif

# cli: shared between bitcoinrtx-cli and bitcoinrtx-qt
libbitcoinrtx_cli_a_CPPFLAGS = $(BITCOINRTX_INCLUDES)
libbitcoinrtx_cli_a_SOURCES = \
  rpcclient.cpp \
  $(BITCOINRTX_CORE_H)

nodist_libbitcoinrtx_util_a_SOURCES = $(srcdir)/obj/build.h
#

# bitcoinrtxd binary #
bitcoinrtxd_LDADD = \
  $(LIBBITCOINRTX_SERVER) \
  $(LIBBITCOINRTX_COMMON) \
  $(LIBBITCOINRTX_UNIVALUE) \
  $(LIBBITCOINRTX_UTIL) \
  $(LIBBITCOINRTX_CRYPTO) \
  $(LIBLEVELDB) \
  $(LIBMEMENV) \
  $(LIBSECP256K1)

if ENABLE_WALLET
bitcoinrtxd_LDADD += libbitcoinrtx_wallet.a
endif
bitcoinrtxd_SOURCES = bitcoinrtxd.cpp
#

if TARGET_WINDOWS
bitcoinrtxd_SOURCES += bitcoinrtxd-res.rc
endif

bitcoinrtxd_LDADD += $(BOOST_LIBS) $(BDB_LIBS) $(SSL_LIBS) $(CRYPTO_LIBS) $(MINIUPNPC_LIBS)
bitcoinrtxd_CPPFLAGS = $(BITCOINRTX_INCLUDES)
bitcoinrtxd_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

# bitcoinrtx-cli binary #
bitcoinrtx_cli_LDADD = \
  $(LIBBITCOINRTX_CLI) \
  $(LIBBITCOINRTX_UTIL) \
  $(BOOST_LIBS) \
  $(SSL_LIBS) \
  $(CRYPTO_LIBS)

bitcoinrtx_cli_SOURCES = \
  bitcoinrtx-cli.cpp

bitcoinrtx_cli_CPPFLAGS = $(BITCOINRTX_INCLUDES)
#

# bitcoinrtx-tx binary #
bitcoinrtx_tx_LDADD = \
  $(LIBBITCOINRTX_UNIVALUE) \
  $(LIBBITCOINRTX_COMMON) \
  $(LIBBITCOINRTX_UTIL) \
  $(LIBBITCOINRTX_CRYPTO) \
  $(LIBSECP256K1) \
  $(BOOST_LIBS) \
  $(CRYPTO_LIBS)

bitcoinrtx_tx_SOURCES = bitcoinrtx-tx.cpp
bitcoinrtx_tx_CPPFLAGS = $(BITCOINRTX_INCLUDES)
#
bitcoinrtx_tx_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if TARGET_WINDOWS
bitcoinrtx_cli_SOURCES += bitcoinrtx-cli-res.rc
endif
bitcoinrtx_cli_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if BUILD_BITCOINRTX_LIBS
include_HEADERS = script/bitcoinrtxconsensus.h
libbitcoinrtxconsensus_la_SOURCES = \
  primitives/transaction.cpp \
  crypto/hmac_sha512.cpp \
  crypto/sha1.cpp \
  crypto/sha256.cpp \
  crypto/sha512.cpp \
  crypto/ripemd160.cpp \
  eccryptoverify.cpp \
  ecwrapper.cpp \
  hash.cpp \
  pubkey.cpp \
  script/script.cpp \
  script/interpreter.cpp \
  script/bitcoinrtxconsensus.cpp \
  uint256.cpp \
  utilstrencodings.cpp

if GLIBC_BACK_COMPAT
  libbitcoinrtxconsensus_la_SOURCES += compat/glibc_compat.cpp
  libbitcoinrtxconsensus_la_SOURCES += compat/glibcxx_compat.cpp
endif

libbitcoinrtxconsensus_la_LDFLAGS = -no-undefined $(RELDFLAGS)
libbitcoinrtxconsensus_la_LIBADD = $(CRYPTO_LIBS)
libbitcoinrtxconsensus_la_CPPFLAGS = $(CRYPTO_CFLAGS) -I$(builddir)/obj -DBUILD_BITCOINRTX_INTERNAL
if USE_LIBSECP256K1
libbitcoinrtxconsensus_la_LIBADD += secp256k1/libsecp256k1.la
endif
endif

CLEANFILES = leveldb/libleveldb.a leveldb/libmemenv.a *.gcda *.gcno

DISTCLEANFILES = obj/build.h

EXTRA_DIST = leveldb

clean-local:
	-$(MAKE) -C leveldb clean
	-$(MAKE) -C secp256k1 clean
	rm -f leveldb/*/*.gcno leveldb/helpers/memenv/*.gcno
	-rm -f config.h

.rc.o:
	@test -f $(WINDRES)
	$(AM_V_GEN) $(WINDRES) -DWINDRES_PREPROC -i $< -o $@

.mm.o:
	$(AM_V_CXX) $(OBJCXX) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) \
	  $(CPPFLAGS) $(AM_CXXFLAGS) $(QT_INCLUDES) $(CXXFLAGS)  -c -o $@ $<

%.pb.cc %.pb.h: %.proto
	@test -f $(PROTOC)
	$(AM_V_GEN) $(PROTOC) --cpp_out=$(@D) --proto_path=$(abspath $(<D) $<)

if ENABLE_TESTS
include Makefile.test.include
endif

if ENABLE_QT
include Makefile.qt.include
endif

if ENABLE_QT_TESTS
include Makefile.qttest.include
endif
