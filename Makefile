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

MAKEFLAGS += --no-print-directory

# set prefix to /usr/local by default
ifeq ($(PREFIX),)
    PREFIX := /usr/local
endif

all: build

build:
	mkdir -p $@
	cmake -B$@

build/test/testcctest: build
	cmake --build $< --target testcctest

test: build/test/testcctest
	./$<

install: build
	cmake --install $<

uninstall:
	${RM} -r ${DESTDIR}${PREFIX}/lib/cmake/cctest-0.2.1
	${RM} -r ${DESTDIR}${PREFIX}/include/cctest-0.2.1

clean:
	${RM} -r build

clean-all:
	${RM} -r build
	${RM} cmake/cctest-config-version.cmake
	${RM} CHANGELOG.md
	${RM} README.md

.PHONY: all test install uninstall clean clean-all
