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

MAKEFLAGS += --no-print-directory

# set prefix to /usr/local by default
ifeq ($(PREFIX),)
    PREFIX := /usr/local
endif

all: build

build: include/cctest.h cmake/*
	mkdir -p $@
	cmake -B$@

build/test/testcctest: build test/testcctest.cc
	cmake --build $< --target testcctest

test: build/test/testcctest
	./$<

install: build
	cmake --install $<

uninstall:
	${RM} -r ${DESTDIR}${PREFIX}/lib/cmake/cctest-0.5.2
	${RM} -r ${DESTDIR}${PREFIX}/include/cctest-0.5.2

clean:
	${RM} -r build

clean-all:
	${RM} -r build
	${RM} cmake/cctest-config-version.cmake
	${RM} CHANGELOG.md
	${RM} README.md

.PHONY: all test install uninstall clean clean-all
