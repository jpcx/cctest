# cctest 0.5.0 | [_API Docs_](http://jpcx.github.io/cctest/cctest_8h.html) | [_CHANGELOG_](https://github.com/jpcx/cctest/blob/0.5.0/CHANGELOG.md)

## About

cctest is a tiny test framework for C++17.  

__The API has been simplified since 0.4.2. Please check the usage instructions and CHANGELOG.__

cctest is thread-safe; one atomic counter is used and each test calls `cout` only once.

## Setup

Copy `include/cctest.h` into your project and include it or use one of these methods:

### CMake Install

```shell
git clone -b 0.5.0 https://github.com/jpcx/cctest.git
cd cctest

make # mkdir build
     # cmake -Bbuild

# installs header to      ${DESTDIR}${PREFIX}/include/cctest-0.5.0
# installs cmake files to ${DESTDIR}${PREFIX}/lib/cmake/cctest-0.5.0
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
                     GIT_TAG "0.5.0")
FetchContent_MakeAvailable(cctest)
target_link_libraries([your target] cctest)
```

### CMake add\_subdirectory

```shell
git clone -b 0.5.0 https://github.com/jpcx/cctest.git # or git submodule add
```
```cmake
add_subdirectory([cctest download dir])
target_link_libraries([your target] cctest)
```

## Usage

```cpp
#include <cctest.h>
#include <cstring>

TEST("test all the things") {
  static_assert(true, "use static_assert wherever possible!");
  ASSERT(1 == 1);
  auto e = ASSERT_THROWS(std::runtime_error) {
    throw std::runtime_error{"hello"};
  };
  ASSERT(strcmp(e.what(), "hello") == 0);
};
```

A main file must be created as well; use it to print a success mesage

```cpp
#define CCTEST_MAIN
#include <cctest.h>
```

## Preview

``` shell
./path/to/test

 > this test passes
 > another passing test
 > sample fail test
     FAIL /path/to/src.cc:50
     what: this is an expected failure

 > tests continue after failure

1 Test Failed
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
