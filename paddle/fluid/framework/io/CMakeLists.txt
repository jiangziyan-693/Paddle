file(GLOB framework_io_srcs "*.cc")
if(WITH_CRYPTO)
  file(GLOB framework_io_crypto_srcs "crypto/*.cc")
  set(framework_io_srcs ${framework_io_srcs} ${framework_io_crypto_srcs})
endif()

set(framework_io_deps glog timer)
if(WITH_CRYPTO)
  set(framework_io_deps ${framework_io_deps} cryptopp)
endif()

cc_library(
  framework_io
  SRCS ${framework_io_srcs}
  DEPS ${framework_io_deps})
