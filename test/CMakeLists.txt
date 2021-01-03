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

add_executable(test${PROJECT_NAME}
  test${PROJECT_NAME}.cc
  test${PROJECT_NAME}.main.cc)
target_compile_options(test${PROJECT_NAME} PRIVATE
                       ${CMAKE_CXX_FLAGS}
                       -std=c++17
                       -Wall
                       -Wextra
                       -pedantic-errors
                       $<$<CXX_COMPILER_ID:Clang>:-Weverything>
                       -Werror
                       $<$<CXX_COMPILER_ID:Clang>:${CLANG_WARNINGS}>)
target_link_libraries(test${PROJECT_NAME} ${PROJECT_NAME})
set_target_properties(test${PROJECT_NAME} PROPERTIES
                      EXCLUDE_FROM_ALL TRUE
                      EXCLUDE_FROM_DEFUALT_BUILD TRUE)
