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

add_executable(test${PROJECT_NAME} test${PROJECT_NAME}.cc)
target_link_libraries(test${PROJECT_NAME} ${PROJECT_NAME})

add_custom_target(test
  COMMAND ${CMAKE_BINARY_DIR}/test/testcctest
  DEPENDS test${PROJECT_NAME})
