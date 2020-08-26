CXXFLAGS += -std=c++17 -I.

# set prefix to /usr/local by default
ifeq ($(PREFIX),)
    PREFIX := /usr/local
endif

all: testcctest

testcctest: testcctest.cc cctest/cctest.h
	${CXX} ${CXXFLAGS} $< -o $@

test: testcctest
	./testcctest

install: cctest/cctest.h
	install -d ${DESTDIR}${PREFIX}/include/cctest
	install -m 644 $< ${DESTDIR}${PREFIX}/include/cctest

clean:
	${RM} -f testcctest

.PHONY: all test install clean
