cmake_minimum_required(VERSION 3.12)

# --------------------------------------------------------- #
# Project declaration                                       #
# --------------------------------------------------------- #
set(PROG_NAME Blyss-Server)
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
# Blyss executable                                          #
# --------------------------------------------------------- #
add_executable(${PROG_NAME} ${BLYSS_SRCS} ${BLYSS_HDRS})

# --------------------------------------------------------- #
# Include directories                                       #
# --------------------------------------------------------- #
target_include_directories(${PROG_NAME} PUBLIC
    ${BLYSS_INCLUDE_DIR}
)

# --------------------------------------------------------- #
# Library linking                                           #
# --------------------------------------------------------- #
target_link_libraries(${PROG_NAME}
)