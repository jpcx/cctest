# std=c++17 and -I. should be the only necessary flags
CXXFLAGS += -std=c++17 -I.

# set prefix to /usr/local by default
ifeq ($(PREFIX),)
    PREFIX := /usr/local
endif

all: testcctest

testcctest: testcctest.cc cctest.h
	${CXX} ${CXXFLAGS} $< -o $@

test: testcctest
	./testcctest

install: cctest.h
	install -d ${DESTDIR}${PREFIX}/include/
	install -m 644 $< ${DESTDIR}${PREFIX}/include/

clean:
	${RM} -f testcctest

.PHONY: all test install clean
