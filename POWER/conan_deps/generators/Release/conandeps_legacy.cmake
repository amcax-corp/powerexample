message(STATUS "Conan: Using CMakeDeps conandeps_legacy.cmake aggregator via include()")
message(STATUS "Conan: It is recommended to use explicit find_package() per dependency instead")

find_package(Eigen3)
find_package(Boost)
find_package(saribbonbar)
find_package(Catch2)
find_package(ZLIB)
find_package(sentry-breakpad)
find_package(AMCAXRender)
find_package(AMCAXholefind)
find_package(amcax)

set(CONANDEPS_LEGACY  Eigen3::Eigen  boost::boost  saribbonbar::saribbonbar  Catch2::Catch2WithMain  ZLIB::ZLIB  sentry-breakpad::sentry-breakpad  AMCAXRender  AMCAXholefind  amcax::amcax )