cmake_minimum_required(VERSION 3.10)
project(wmediumd-srv)

set(DEB_PACKAGE_NAME ${CMAKE_PROJECT_NAME})
set(DEB_PACKAGE_VERSION "1.0.1")
set(DEB_PACKAGE_SECTION "misc")
set(DEB_PACKAGE_DESRCIPTION "WiFi Medium Simulator")
set(DEB_PACKAGE_MAINTAINER "Aleksandr Loshkarev <hi@aloshkarev.ru>")
set(DEB_PACKAGE_ARCH "amd64")
set(DEB_PACKAGE_DEPENDS "libnl-3-dev, libnl-genl-3-dev, libevent-dev")

# find libraries
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/deb_packaging.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/FindNetLink.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/FindLibEvent.cmake)

find_package(Threads)
find_package(PkgConfig)

include_directories(/usr/include/libnl3/)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu11 -Wall -Wextra -Wno-unused-parameter -O2 -m64 -DCONFIG_LIBNL30")

# set source files
set(SOURCE_FILES
        wmediumd/config.c
        wmediumd/per.c
        wmediumd/wmediumd.c
        wmediumd/wmediumd_dynamic.c
        wmediumd/wserver.c
        wmediumd/wserver_messages.c
        wmediumd/wserver_messages_network.c)

# add executables
add_executable(wmediumd ${SOURCE_FILES})
target_link_libraries(wmediumd config event m nl-genl-3 nl-3 pthread)
install(TARGETS wmediumd DESTINATION /usr/local/bin/)

