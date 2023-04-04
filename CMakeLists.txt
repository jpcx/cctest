# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
#                __                   __
#               /\ \__               /\ \__
#     ___    ___\ \ ,_\    __    ____\ \ ,_\
#    /'___\ /'___\ \ \/  /'__`\ /',__\\ \ \/
#   /\ \__//\ \__/\ \ \_/\  __//\__, `\\ \ \_
#   \ \____\ \____\\ \__\ \____\/\____/ \ \__\
#    \/____/\/____/ \/__/\/____/\/___/   \/__/
# 
#   a tiny test framework for C++17
#   Copyright (C) 2020-2023 Justin Collier <m@jpcx.dev>
# 
#     This program is free software: you can redistribute it and/or modify
#     it under the terms of the GNU General Public License as published by
#     the Free Software Foundation, either version 3 of the License, or
#     (at your option) any later version.
# 
#     This program is distributed in the hope that it will be useful,
#     but WITHOUT ANY WARRANTY; without even the implied warranty of
#     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#     GNU General Public License for more details.
#
#   You should have received a copy of the GNU General Public License
#   along with this program.  If not, see <https://www.gnu.org/licenses/>.
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

# - - - - - - - - - - - - - - - - - project - - - - - - - - - - - - - - - - -  #

cmake_minimum_required (VERSION 3.0)
project (cctest
         VERSION 0.5.2
         DESCRIPTION "a small static/dynamic testing framework for C++17"
         HOMEPAGE_URL "https://github.com/jpcx/cctest"
         LANGUAGES CXX)

configure_file (
  ${PROJECT_SOURCE_DIR}/cmake/${PROJECT_NAME}-config-version.cmake.in
  ${PROJECT_SOURCE_DIR}/cmake/${PROJECT_NAME}-config-version.cmake @ONLY)

configure_file (
  ${PROJECT_SOURCE_DIR}/cmake/README.md.in
  ${PROJECT_SOURCE_DIR}/README.md @ONLY)

configure_file (
  ${PROJECT_SOURCE_DIR}/cmake/CHANGELOG.md.in
  ${PROJECT_SOURCE_DIR}/CHANGELOG.md @ONLY)

configure_file (
  ${PROJECT_SOURCE_DIR}/cmake/Makefile.in
  ${PROJECT_SOURCE_DIR}/Makefile @ONLY)

# - - - - - - - - - - - - - - - - - variables - - - - - - - - - - - - - - - -  #

set (INCLUDE_DEST "include/${PROJECT_NAME}-${PROJECT_VERSION}")
set (LIB_DEST "lib/cmake/${PROJECT_NAME}-${PROJECT_VERSION}")
set (CMAKE_EXPORT_COMPILE_COMMANDS ON)

# - - - - - - - - - - - - - - - - - interface - - - - - - - - - - - - - - - -  #

add_library (${PROJECT_NAME} INTERFACE)

target_compile_options     (${PROJECT_NAME} INTERFACE ${CMAKE_CXX_FLAGS})

target_include_directories (${PROJECT_NAME} INTERFACE 
                            $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
                            $<INSTALL_INTERFACE:${INCLUDE_DEST}>)

# - - - - - - - - - - - - - - - - - install - - - - - - - - - - - - - - - - -  #

install (TARGETS ${PROJECT_NAME}
         EXPORT ${PROJECT_NAME}
         DESTINATION ${INCLUDE_DEST})

install (FILES ${PROJECT_SOURCE_DIR}/cmake/${PROJECT_NAME}-config.cmake
         DESTINATION ${LIB_DEST})

install (FILES ${PROJECT_SOURCE_DIR}/cmake/${PROJECT_NAME}-config-version.cmake
         DESTINATION ${LIB_DEST})

install (FILES ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}.h
         DESTINATION ${INCLUDE_DEST})

install (EXPORT ${PROJECT_NAME}
         DESTINATION ${LIB_DEST})

# - - - - - - - - - - - - - - - - - - test - - - - - - - - - - - - - - - - - - #

add_subdirectory (test)
