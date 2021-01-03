/*                                                                         C++17

                                __                   __
                               /\ \__               /\ \__
                     ___    ___\ \ ,_\    __    ____\ \ ,_\
                    /'___\ /'___\ \ \/  /'__`\ /',__\\ \ \/
                   /\ \__//\ \__/\ \ \_/\  __//\__, `\\ \ \_
                   \ \____\ \____\\ \__\ \____\/\____/ \ \__\
                    \/____/\/____/ \/__/\/____/\/___/   \/__/

                        a tiny test framework for C++17

    Copyright (C) 2020, 2021 Justin Collier

      This program is free software: you can redistribute it and/or modify
      it under the terms of the GNU General Public License as published by
      the Free Software Foundation, either version 3 of the License, or
      (at your option) any later version.

      This program is distributed in the hope that it will be useful,
      but WITHOUT ANY WARRANTY; without even the internalied warranty of
      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
      GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>. */

#include <chrono>
#include <string>
#include <thread>

#include <cctest.h>

namespace cctest {
namespace detail_ {
extern std::atomic<int> n_tests_failed;
} // namespace detail_
} // namespace cctest

#if defined(__clang__) && __clang__ == 1
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++98-compat"
#pragma clang diagnostic ignored "-Wexit-time-destructors"
#pragma clang diagnostic ignored "-Wglobal-constructors"
#endif

namespace testcctest {

/*.----------------------------------------------------------------------------,
 /                             construction tests                            */

static_assert(!std::is_default_constructible_v<cctest::test>);
static_assert(!std::is_copy_constructible_v<cctest::test>);
static_assert(!std::is_copy_assignable_v<cctest::test>);
static_assert(std::is_move_constructible_v<cctest::test>);
static_assert(std::is_move_assignable_v<cctest::test>);

static cctest::test assign = "implicit assignment construction";
static cctest::test movedescr =
    cctest::test{"move-assignment with description"};

static cctest::test op_pass =
    cctest::test{"operator overload", __FILE__, __LINE__} << [] {};
TEST("\"operator overload fail\" fails expectedly") {
  int nbefore = cctest::detail_::n_tests_failed;
  static cctest::test op_fail =
      cctest::test{"operator overload fail", __FILE__, __LINE__}
      << [] { throw std::runtime_error("this is an expected failure"); };
  ASSERT(cctest::detail_::n_tests_failed == nbefore + 1);
};

static cctest::test with_file_and_line_pass =
    cctest::test{"test pass with file and line", __FILE__, __LINE__} << [] {};

TEST("\"test fail with file and line\" fails expectedly") {
  int nbefore = cctest::detail_::n_tests_failed;
  static cctest::test with_file_and_line_fail =
      cctest::test{"test fail with file and line", __FILE__, __LINE__}
      << [] { throw std::runtime_error("this is an expected failure"); };
  ASSERT(cctest::detail_::n_tests_failed == nbefore + 1);
};

TEST("TEST macro usage"){};

TEST("\"TEST macro failure\" fails expectedly") {
  int nbefore = cctest::detail_::n_tests_failed;
  TEST("TEST macro failure") {
    throw std::runtime_error("this is an expected failure");
  };
  ASSERT(cctest::detail_::n_tests_failed == nbefore + 1);
};

TEST("ASSERT passes expectedly") {
  ASSERT(1 == 1);
};

TEST("\"ASSERT fails expectedly\" fails expectedly") {
  int nbefore = cctest::detail_::n_tests_failed;
  TEST("ASSERT fails expectedly") {
    ASSERT(false);
 };
  ASSERT(cctest::detail_::n_tests_failed == nbefore + 1);
};

TEST("ASSERT_THROWS catches and returns an exception") {
  auto e = ASSERT_THROWS(std::runtime_error) {
    throw std::runtime_error{"hey"};
  };
  ASSERT(std::string{e.what()} == "hey");
};

TEST("ASSERT_THROWS throws if no throw") {
  auto e = ASSERT_THROWS(std::runtime_error) {
    ASSERT_THROWS(std::runtime_error){};
  };
  ASSERT(std::string{e.what()} == "[cctest]: throw assertion failed");
};

TEST("ASSERT_THROWS throws if unexpected throw type") {
  auto e = ASSERT_THROWS(std::runtime_error) {
    ASSERT_THROWS(std::runtime_error) {
      throw "bad error";
    };
  };
  ASSERT(std::string{e.what()} == "[cctest]: unexpected throw type");
};

TEST("expected tests failed") {
  ASSERT(cctest::detail_::n_tests_failed == 4);
  cctest::detail_::n_tests_failed = 0;
};

} // namespace testcctest

#if defined(__clang__) && __clang__ == 1
#pragma clang diagnostic pop
#endif
