# cctest 0.5.1 | [_API Docs_](http://jpcx.github.io/cctest/cctest_8h.html) | [_CHANGELOG_](https://github.com/jpcx/cctest/blob/0.5.1/CHANGELOG.md)

## About

cctest is a tiny test framework for C++17.  

__The API has been simplified since 0.4.2. Please check the usage instructions and CHANGELOG.__

cctest is thread-safe; one atomic counter is used and each test calls `cout` only once.

## Usage

Creating a main file (may be seperate or as part of a test source):

```cpp
#define CCTEST_MAIN
#include <cctest.h>
```

Creating test files:

```cpp
#include <cctest.h>
#include <cstring>

TEST("test all the things") {
  static_assert(true, "use static_assert wherever possible!");
  ASSERT(1 == 1); // make a runtime assertion
  auto e = ASSERT_THROWS(std::runtime_error) { // returns thrown error by value
    throw std::runtime_error{"hello"};
  };
  ASSERT(strcmp(e.what(), "hello") == 0);
};

TEST("multiple tests per file are OK") {
  static_assert(true, "runtime assertions are not required");
};
```

Execution:

``` shell
${CXX} ${CXXFLAGS} -std=c++17 main.cc test0.cc test1.cc -o test
./test

 > this test passes
 > another passing test
 > sample fail test
     FAIL /path/to/src.cc:50
     what: this is an expected failure

 > tests continue after runtime failure

1 Test Failed
```

## Setup

### Standalone Header

Copy `include/cctest.h` into your project and include it.

__note:__  
There should be no compiler warnings for GCC or Clang with `-Wall -Wextra -pedantic`.
Additionally, `#pragma` statements are used to filter Clang's `-Weverything`,
so simple inclusion should be fine in most cases.

### CMake Install

```shell
git clone -b 0.5.1 https://github.com/jpcx/cctest.git
cd cctest

make # mkdir build
     # cmake -Bbuild

# installs header to      ${DESTDIR}${PREFIX}/include/cctest-0.5.1
# installs cmake files to ${DESTDIR}${PREFIX}/lib/cmake/cctest-0.5.1
sudo make install # cmake --install build
```
```cmake
find_package(cctest 0.5 REQUIRED)
target_link_libraries([your target] cctest)
```

### CMake FetchContent

```cmake
include(FetchContent)
FetchContent_Declare(cctest
                     GIT_REPOSITORY https://github.com/jpcx/cctest.git
                     GIT_TAG "0.5.1")
FetchContent_MakeAvailable(cctest)
target_link_libraries([your target] cctest)
```

### CMake add\_subdirectory

```shell
git clone -b 0.5.1 https://github.com/jpcx/cctest.git # or git submodule add
```
```cmake
add_subdirectory([cctest download dir])
target_link_libraries([your target] cctest)
```

## Testing

All API features are self-tested:

```shell
cd [cctest source dir]
make test # mkdir build
          # cmake -Bbuild
          # cmake --build build --target test

```

## Contributing

Contribution is welcome! Please make a pull request.  
