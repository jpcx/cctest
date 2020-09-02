# cctest 0.2.3 | [_API Docs_](http://jpcx.github.io/cctest/cctest_8h.html) | [_CHANGELOG_](https://github.com/jpcx/cctest/blob/0.2.3/CHANGELOG.md)

```
             __                   __
            /\ \__               /\ \__     auto o = "easy!"
  ___    ___\ \ ,_\    __    ____\ \ ,_\        << static_pass
 /'___\ /'___\ \ \/  /'__`\ /',__\\ \ \/        << dynamic_pass
/\ \__//\ \__/\ \ \_/\  __//\__, `\\ \ \_       << [] {
\ \____\ \____\\ \__\ \____\/\____/ \ \__\           return [...]_pass;
 \/____/\/____/ \/__/\/____/\/___/   \/__/         };

            cctest C++ Testing
```

## About

cctest is a small static and dynamic testing framework for C++17.  
Static tests can be very helpful for development (especially with a good IDE).  
Dynamic assertions are also supported and may be combined with static assertions.

## Requirements

- C++17

## Setup

This is a single-header library!  
Copy `include/cctest.h` into your project or use one of these methods:

### Standard -I

```shell
git clone -b 0.2.3 https://github.com/jpcx/cctest.git
```
```makefile
CXXFLAGS += -I[ccutl install dir]/include
```

### CMake Install

```shell
git clone -b 0.2.3 https://github.com/jpcx/cctest.git
cd cctest

make # mkdir build
     # cmake -Bbuild

# installs header to      ${DESTDIR}${PREFIX}/include/cctest-0.2.3
# installs cmake files to ${DESTDIR}${PREFIX}/lib/cmake/cctest-0.2.3
sudo make install # cmake --install build
```
```cmake
find_package(cctest 0.2 REQUIRED)
target_link_libraries([your target] cctest)
```

### CMake FetchContent

```cmake
include(FetchContent)
FetchContent_Declare(cctest
                     GIT_REPOSITORY https://github.com/jpcx/cctest.git
                     GIT_TAG "0.2.3")
FetchContent_MakeAvailable(cctest)
target_link_libraries([your target] cctest)
```

### CMake add_subdirectory

```shell
git clone -b 0.2.3 https://github.com/jpcx/cctest.git # or git submodule add
```
```cmake
add_subdirectory([cctest download dir])
target_link_libraries([your target] cctest)
```

## Usage

```cpp
#include <cctest.h>

// use a namespace to respect ODR across TUs (alternatively, use `static`)

namespace unique {

// use the cctest namespace for operator overloads
using namespace cctest;

test t0 = "compiletime test with cctest::static_[pass/fail] "
          "or cctest::static_fail"
          << static_pass;

test t1 = "runtime test with ccctest::dynamic_[pass/fail]"
          << dynamic_pass;

// note: static_require<cond>  specializes to static_pass or static_fail
//       dynamic_require(cond) specializes to dynamic_pass or dynamic_fail
test t2 = "static and dynamic testing may be chained"
          << (static_require<true> && static_pass && !static_fail)
          << dynamic_pass && dynamic_require(true);

test t3 = "predicates may also be used; must return `static_pass`, "
          "`static_fail` `dynamic_pass`, `dynamic_fail`, or `void`"
          << [](){
            if constexpr (some_condition) {
              return static_pass;
            } else {
              return static_fail;
            }
          };

test t4 = "different types of test methods may be combined"
          << static_pass
          << dynamic_pass
          << [](){ return static_pass; }
          << [](){ return dynamic_pass; };

// descriptions are not required
test t5 = static_pass;

} // namespace unique

// usage of the cctest namespace is not required
static auto t6 = cctest::test{"description must be put here instead"}
                 << cctest::static_pass
                 << cctest::dynamic_pass;

TEST(my.cool.feature, "can be tested like this as well")
    << STATIC_REQUIRE(some_static_condition<int>)
    << DYNAMIC_REQUIRE(some_dynamic_condition(0));

TEST_SCOPE(open.up.a.scope, "local scopes are helpful") {
  constexpr int my_nice_value = 32;
  STATIC_CHECK(some_other_static_condition(my_nice_value));
};

TEST_SCOPE(scoped.combinations, "static + dynamic checks") {
  STATIC_CHECK(true);   // if constexpr (!true) return static_fail;
  DYNAMIC_CHECK(true);  // if (!true)           return dynamic_fail;
  CLOSE_SCOPE;          // returns cctest::dynamic_pass; necessary for
                        // dynamic scopes (lambda must return a value)
};
```

A main file must be created as well; use it to print a success mesage

```cpp
#include <cctest.h>

int
main(int, char**) {
  cctest::success();
  return 0;
}
```

Alternatively, `#define CCTEST_MAIN`

```cpp
#define CCTEST_MAIN
#include <cctest.h>
```

__Note Regarding Static Tests and Macro Helpers:__  
It is recommended that each test condition is split into separate `<<` statements.  
Test assertions are executed by `operator<<`, so separation allows for easier  
identification of a failed condition. This is lost when testing multiple statements  
within a `TEST_SCOPE`.

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
I'm open to adding new features such as built-in string comparison checks, etc.

## Documentation

[Project documentation](http://jpcx.github.io/cctest) is generated by Doxygen and is hosted by GitHub Pages.
