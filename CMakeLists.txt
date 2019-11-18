cmake_minimum_required(VERSION 3.12)

# --------------------------------------------------------- #
# Project declaration                                       #
# --------------------------------------------------------- #
set(PROG_NAME Blyss-Server)
set(LIB_NAME Lib${PROG_NAME})
project (${PROG_NAME})

# --------------------------------------------------------- #
# C++ 17 standard                                           #
# --------------------------------------------------------- #
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --------------------------------------------------------- #
# Include modules                                           #
# --------------------------------------------------------- #
include(cmake/embed.cmake)
include(cmake/add.cmake)

# --------------------------------------------------------- #
# Include dependencies                                      #
# --------------------------------------------------------- #
include(cmake/lib/spdlog.cmake)
include(cmake/lib/libuv.cmake)
#include(cmake/lib/libprotobuf.cmake)

# --------------------------------------------------------- #
# Include sources                                           #
# --------------------------------------------------------- #
include(cmake/sources.cmake)

# --------------------------------------------------------- #
# Blyss version                                             #
# --------------------------------------------------------- #
add_compile_definitions(BLYSS_VERSION_MAJOR="0")
add_compile_definitions(BLYSS_VERSION_MINOR="0")
add_compile_definitions(BLYSS_VERSION_PATCH="1")

# --------------------------------------------------------- #
# Blyss library                                             #
# --------------------------------------------------------- #
add_library(${LIB_NAME} ${BLYSS_SRCS} ${BLYSS_HDRS})

# --------------------------------------------------------- #
# Include directories                                       #
# --------------------------------------------------------- #
target_include_directories(${LIB_NAME} PUBLIC
    ${BLYSS_INCLUDE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# --------------------------------------------------------- #
# Library linking                                           #
# --------------------------------------------------------- #
target_link_libraries(${LIB_NAME}
    ${SPDLOG_LIB}
    ${LIBUV_LIB}
)

# --------------------------------------------------------- #
# Executable linking                                        #
# --------------------------------------------------------- #
set(BLYSS_SERVER_EXECUTABLE ON CACHE BOOL "Build Executable")
if(${BLYSS_SERVER_EXECUTABLE})
    add_executable(${PROG_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)
    target_link_libraries(${PROG_NAME} ${LIB_NAME})
endif(${BLYSS_SERVER_EXECUTABLE})

# --------------------------------------------------------- #
# Testing                                                   #
# --------------------------------------------------------- #
set(BLYSS_TEST_SERVER OFF CACHE BOOL "Run Tests")
if(${BLYSS_TEST_SERVER})
    set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
    set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
    set(gtest_force_shared_crt ON)
    enable_testing()
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib/googletest)

    set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test)

    set(TEST_SRCS 
        ${TEST_DIR}/packet_buffer_tests.cpp
        ${TEST_DIR}/packet_reader_tests.cpp
    )

    include(GoogleTest)
    add_executable(MainTest ${TEST_SRCS})
    target_link_libraries(MainTest gtest gtest_main ${LIB_NAME})
    gtest_discover_tests(MainTest)
endif(${BLYSS_TEST_SERVER})
