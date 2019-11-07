# --------------------------------------------------------- #
#  libuv                                                    #
# --------------------------------------------------------- #
set(BUILD_TESTING OFF CACHE BOOL "" FORCE)
set(libuv_buildtests OFF CACHE BOOL "" FORCE)

set(LIBUV_DIR lib/libuv)
set(LIBUV_LIB uv_a)

add_subdirectory(${LIBUV_DIR})