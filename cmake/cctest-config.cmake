# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
# 
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

get_filename_component (SELF_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
include (${SELF_DIR}/cctest.cmake)
