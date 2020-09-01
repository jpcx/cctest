# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
# 
#                __                   __
#               /\ \__               /\ \__     auto o = "easy!"
#     ___    ___\ \ ,_\    __    ____\ \ ,_\        << static_pass
#    /'___\ /'___\ \ \/  /'__`\ /',__\\ \ \/        << dynamic_pass
#   /\ \__//\ \__/\ \ \_/\  __//\__, `\\ \ \_       << [] {
#   \ \____\ \____\\ \__\ \____\/\____/ \ \__\           return [...]_pass;
#    \/____/\/____/ \/__/\/____/\/___/   \/__/         };
# 
#   cctest C++ Testing
#   Copyright (C) 2020 Justin Collier <m@jpcx.dev>
# 
#     This program is free software: you can redistribute it and/or modify
#     it under the terms of the GNU General Public License as published by
#     the Free Software Foundation, either version 3 of the License, or
#     (at your option) any later version.
# 
#     This program is distributed in the hope that it will be useful,
#     but WITHOUT ANY WARRANTY; without even the internalied warranty of
#     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#     GNU General Public License for more details.
#
#   You should have received a copy of the GNU General Public License
#   along with this program.  If not, see <https://www.gnu.org/licenses/>.
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

cmake_minimum_required (VERSION 3.0)
project (cctest
         VERSION 0.2.0
         DESCRIPTION "a small static/dynamic testing framework for C++17"
         HOMEPAGE_URL "https://github.com/jpcx/cctest"
         LANGUAGES CXX)

set (CLANG_WARNINGS
     -Weverything
     -Wno-c++98-c++11-compat
     -Wno-c++98-compat
     -Wno-c++98-compat-pedantic
     -Wno-missing-variable-declarations
     -Wno-global-constructors
     -Wno-documentation-unknown-command)

set (BASE_CXX_FLAGS -std=c++17)

add_library (${PROJECT_NAME} INTERFACE)

target_compile_options     (${PROJECT_NAME} INTERFACE
                            ${CMAKE_CXX_FLAGS}
                            ${BASE_CXX_FLAGS}
                            $<$<CXX_COMPILER_ID:Clang>:${CLANG_WARNINGS}>)
target_compile_features    (${PROJECT_NAME} INTERFACE cxx_std_17)
target_include_directories (${PROJECT_NAME} INTERFACE ${PROJECT_SOURCE_DIR}/include)

add_subdirectory (test)

install (TARGETS ${PROJECT_NAME}
         EXPORT ${PROJECT_NAME}-targets
         ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
         LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
         RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
