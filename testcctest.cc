/////                                                                      c++17
////////////////////////////////////////////////////////////////////////////////
/// @brief cctest - a small static/dynamic testing framework for C++17
//               __                   __
//              /\ \__               /\ \__     auto o = "easy!"
//    ___    ___\ \ ,_\    __    ____\ \ ,_\        << static_pass
//   /'___\ /'___\ \ \/  /'__`\ /',__\\ \ \/        << dynamic_pass
//  /\ \__//\ \__/\ \ \_/\  __//\__, `\\ \ \_       << [] {
//  \ \____\ \____\\ \__\ \____\/\____/ \ \__\           return [...]_pass;
//   \/____/\/____/ \/__/\/____/\/___/   \/__/         };
//
//  cctest C++ Testing
//  Copyright (C) 2020 Justin Collier <m@jpcx.dev>
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the internalied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//                                                                            //
//  You should have received a copy of the GNU General Public License        ///
//  along with this program.  If not, see <https://www.gnu.org/licenses/>.  ////
////////////////////////////////////////////////////////////////////////////////

#include <cctest/cctest.h>

using namespace cctest;
#define dsc(...) "[cctest] " __VA_ARGS__

namespace test_ {

/*.----------------------------------------------------------------------------,
 /                             construction tests                            */

namespace construction {

test empty{};
test descr{dsc("description-based construction")};
test assign    = dsc("implicit assignment construction");
test copy      = test{};
test copydescr = test{dsc("copy-assignment with description")};

namespace static_ {
test pass{static_pass};
// test fail{static_fail};
test predpass{[]() { return static_pass; }};
test voidpass{[]() {}};
// test predfail{[]() { return static_fail; }};
} // namespace static_

namespace dynamic {
test pass{dynamic_pass};
// test fail{dynamic_fail};
test predpass{[]() { return dynamic_pass; }};
// test predfail{[]() { return dynamic_fail; }};
} // namespace dynamic

} // namespace construction

/*.----------------------------------------------------------------------------,
 /                       member operator overload tests                      */

namespace member_opoverload {

namespace static_ {
test pass = test{dsc("static_pass member operator overload")} << static_pass;
// test fail = test{dsc("static_fail member operator overload")} <<
//             static_fail;
test predpass = test{dsc("static_pass predicate member operator overload")}
                << []() { return static_pass; };
// test predfail = test{dsc("static_fail predicate member operator overload")}
//                 << []() { return static_fail; };
} // namespace static_

namespace dynamic {
test pass = test{dsc("dynamic_pass member operator overload")} << dynamic_pass;
// test fail = test{dsc("dynamic_fail member operator overload")} <<
//             dynamic_fail;
test predpass = test{dsc("dynamic_pass predicate member operator overload")}
                << []() { return dynamic_pass; };
// test predfail =
//     test{dsc("dynamic_fail predicate member operator overload")}
//     << []() { return dynamic_fail; };
} // namespace dynamic

} // namespace member_opoverload

/*.----------------------------------------------------------------------------,
 /                     namespace operator overload tests                     */

namespace namespace_opoverload {

namespace static_ {
test pass = dsc("static_pass namespace operator overload") << static_pass;
// test fail = dsc("static_fail namespace operator overload") <<
//             static_fail;
test predpass = dsc("static_pass predicate namespace operator overload")
                << []() { return static_pass; };
// test predfail = dsc("static_fail predicate namespace operator overload")
//                 << []() { return static_fail; };
} // namespace static_

namespace dynamic {
test pass = dsc("dynamic_pass namespace operator overload") << dynamic_pass;
// test fail = dsc("dynamic_fail namespace operator overload") <<
//             dynamic_fail;
test predpass = dsc("dynamic_pass predicate namespace operator overload")
                << []() { return dynamic_pass; };
// test predfail =
//     dsc("dynamic_fail predicate namespace operator overload")
//     << []() { return dynamic_fail; };
} // namespace dynamic

} // namespace namespace_opoverload

/*.----------------------------------------------------------------------------,
 /                         test resulter combinations                        */

namespace combinations {

test comb0 = test{dsc("test -> static_pass -> static_pass_pred -> dynamic_pass "
                      "-> dynamic_pass_pred")}
             << static_pass << []() { return static_pass; } << dynamic_pass
             << []() { return dynamic_pass; };
test comb1 =
    dsc("(const char * << static_pass) -> static_pass_pred -> dynamic_pass "
        "-> dynamic_pass_pred")
    << static_pass << []() { return static_pass; } << dynamic_pass
    << []() { return dynamic_pass; };

test comb2 = test{dsc("test -> dynamic_pass -> static_pass")} << dynamic_pass
                                                              << static_pass;

test comb3 = test{dsc("dynamic_pass -> static_pass")} << dynamic_pass
                                                      << static_pass;

} // namespace combinations

} // namespace test_

/*.----------------------------------------------------------------------------,
 /                             test helper macros                            */

TEST(cctest.macros, "provides testing helper macros")
    << STATIC_REQUIRE(true) << DYNAMIC_REQUIRE(true);

TEST(cctest.macros, "facilitates static scopes") << [] { STATIC_CHECK(true); };

TEST(cctest.macros, "facilitates dynamic scopes") << [] {
  DYNAMIC_CHECK(true);
  CLOSE_SCOPE;
};

TEST(cctest.macros, "facilitates static + dynamic scopes") << [] {
  STATIC_CHECK(true);
  DYNAMIC_CHECK(true);
  CLOSE_SCOPE;
};

int
main(int, char **) {
  cctest::success();
}
