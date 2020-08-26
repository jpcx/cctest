#ifndef CCTEST_H_INCLUDED
#define CCTEST_H_INCLUDED
/////                                                                      c++17
////////////////////////////////////////////////////////////////////////////////
/// @brief cctest - a small static/dynamic testing framework for C++17
/// @file
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

/// @file
/// @code
///   #include <cctest/cctest.h>
///
///   // use a namespace to respect ODR across TUs (alternatively, use `static`)
///
///   namespace unique {
///
///   // use the cctest namespace for operator overloads
///   using namespace cctest;
///
///   test t0 = "compiletime test with cctest::static_[pass/fail] "
///             "or cctest::static_fail"
///             << static_pass;
///
///   test t1 = "runtime test with ccctest::dynamic_[pass/fail]"
///             << dynamic_pass;
///
///   // note: static_require<cond>  specializes to static_pass or static_fail
///   //       dynamic_require(cond) specializes to dynamic_pass or dynamic_fail
///   test t2 = "static and dynamic testing may be chained"
///             << (static_require<true> && static_pass && !static_fail)
///             << dynamic_pass && dynamic_require(true);
///
///   test t3 = "predicates may also be used; must return `static_pass`, "
///             "`static_fail` `dynamic_pass`, `dynamic_fail`, or `void`"
///             << [](){
///               if constexpr (some_condition) {
///                 return static_pass;
///               } else {
///                 return static_fail;
///               }
///             };
///
///   test t4 = "different types of test methods may be combined"
///             << static_pass
///             << dynamic_pass
///             << [](){ return static_pass; }
///             << [](){ return dynamic_pass; };
///
///   // descriptions are not required
///   test t5 = static_pass;
///
///   } // namespace unique
///
/// @endcode
///
/// @code
///   #include <cctest/cctest.h>
///
///   // usage of the cctest namespace is not required
///   static auto t0 = cctest::test{"description must be put here instead"}
///                    << cctest::static_pass
///                    << cctest::dynamic_pass;
/// @endcode
///
/// @note use the provided helper macros to reduce syntax
/// @note helper macros may be disabled with `#define CCTEST_DISABLE_MACROS`
///
/// @code
///   #include <cctest/cctest.h>
///
///   TEST(my.cool.feature, "can be tested like this as well")
///       << STATIC_REQUIRE(some_static_condition<int>)
///       << DYNAMIC_REQUIRE(some_dynamic_condition(0));
///
///   TEST_SCOPE(open.up.a.scope, "local scopes are helpful") {
///     constexpr int my_nice_value = 32;
///     STATIC_CHECK(some_other_static_condition(my_nice_value));
///   };
///
///   TEST_SCOPE(scoped.combinations, "static + dynamic checks") {
///     STATIC_CHECK(true);   // if constexpr (!true) return static_fail;
///     DYNAMIC_CHECK(true);  // if (!true)           return dynamic_fail;
///     CLOSE_SCOPE;          // returns cctest::dynamic_pass; necessary for
///                           // dynamic scopes (lambda must return a value)
///   };
/// @endcode
///
/// @note use this main structure to print "All Tests Passed!" on compile.
///       all failures either prevent compilation or terminate execution.
///
/// @code
///   #define CCTEST_MAIN
///   #include <cctest/cctest.h>
/// @endcode
/// OR
/// @code
///   #include <cctest/cctest.h>
///
///   int
///   main(int, char**) {
///     cctest::success();
///     return 0;
///   }
/// @endcode

#include <iostream>
#include <string_view>

namespace cctest {

struct static_pass_type;
struct static_fail_type;
struct dynamic_result_type;

/*.----------------------------------------------------------------------------,
 /                             internal concepts                             */

namespace detail_ {

/// equivalent to std::remove_cvref_t<T>
/// @private
template <class T> using nocvref = std::remove_cv_t<std::remove_reference_t<T>>;

/// true if T is a static_pass_type
/// @private
template <class T>
inline constexpr bool is_static_pass_type =
    std::is_same_v<nocvref<T>, static_pass_type>;

/// true if T is a static_fail_type
/// @private
template <class T>
inline constexpr bool is_static_fail_type =
    std::is_same_v<nocvref<T>, static_fail_type>;

/// true if T is a static_pass_type or static_fail_type
/// @private
template <class T>
inline constexpr bool is_static_result_type =
    is_static_pass_type<T> || is_static_fail_type<T>;

/// true if T is a dynamic_result_type
/// @private
template <class T>
inline constexpr bool is_dynamic_result_type =
    std::is_same_v<nocvref<T>, dynamic_result_type>;

namespace is_static_pass_predicate_ {
/// sfinae fallback false
/// @private
template <class, class = void> struct test {
  static constexpr bool result = false;
};
/// sfinae valid if F returns a static_pass_type
/// @private
template <class F>
struct test<
    F, std::enable_if_t<is_static_pass_type<decltype(std::declval<F>()())>>> {
  static constexpr bool result = true;
};
} // namespace is_static_pass_predicate_

/// true if F is a callable type that returns a static_pass_type
/// @private
template <class F>
inline constexpr bool is_static_pass_predicate =
    is_static_pass_predicate_::test<F>::result;

namespace is_static_fail_predicate_ {
/// sfinae fallback false
/// @private
template <class, class = void> struct test {
  static constexpr bool result = false;
};
/// sfinae valid if F returns a static_fail_type
/// @private
template <class F>
struct test<
    F, std::enable_if_t<is_static_fail_type<decltype(std::declval<F>()())>>> {
  static constexpr bool result = true;
};
} // namespace is_static_fail_predicate_

/// true if F is a callable type that returns a static_fail_type
/// @private
template <class F>
inline constexpr bool is_static_fail_predicate =
    is_static_fail_predicate_::test<F>::result;

/// true if F is a callable type that returns a static result type
/// @private
template <class F>
inline constexpr bool is_static_result_predicate =
    is_static_pass_predicate<F> || is_static_fail_predicate<F>;

namespace is_static_pass_void_ {
/// sfinae fallback false
/// @private
template <class, class = void> struct test {
  static constexpr bool result = false;
};
/// sfinae valid if F returns void
/// @private
template <class F>
struct test<
    F, std::enable_if_t<std::is_same_v<void, decltype(std::declval<F>()())>>> {
  static constexpr bool result = true;
};
} // namespace is_static_pass_void_

/// true if F is a callable type that returns void
/// @private
template <class F>
inline constexpr bool is_static_pass_void =
    is_static_pass_void_::test<F>::result;

namespace is_dynamic_result_predicate_ {
/// sfinae fallback false
/// @private
template <class, class = void> struct test {
  static constexpr bool result = false;
};
/// sfinae valid if F returns void
/// @private
template <class F>
struct test<F, std::enable_if_t<
                   is_dynamic_result_type<decltype(std::declval<F>()())>>> {
  static constexpr bool result = true;
};
} // namespace is_dynamic_result_predicate_

/// true if F is a callable type that returns a dynamic_result_type
/// @private
template <class F>
inline constexpr bool is_dynamic_result_predicate =
    is_dynamic_result_predicate_::test<F>::result;

/// true if T is a static result type or static result callable
/// @private
template <class T>
inline constexpr bool is_static_resulter =
    is_static_result_type<T> || is_static_result_predicate<T> ||
    is_static_pass_void<T>;

/// true if T is a dynamic result type or dynamic result callable
/// @private
template <class F>
inline constexpr bool is_dynamic_resulter =
    is_dynamic_result_type<F> || is_dynamic_result_predicate<F>;

} // namespace detail_

/*.----------------------------------------------------------------------------,
 /                        cctest::test test framework                        */

/// assertion class and description logger
struct test {
  /// default constructor
  constexpr test() = default;
  /// default copy constructor
  constexpr test(const test &) = default;
  /// default move constructor
  constexpr test(test &&) = default;
  /// default destructor
  ~test() = default;
  /// load the description from an `std::string_view`
  test(const std::string_view &description) : description_(description.data()) {
    print_attempt<>();
  };
  /// load the description from a `const char *`
  test(const char *description) : description_(description) {
    print_attempt<>();
  };
  /// skip a description; load only a static result
  template <
      class Result,
      std::enable_if_t<detail_::is_static_result_type<Result>> * = nullptr>
  constexpr test(Result &&) {
    static_assert(detail_::nocvref<Result>::value);
  };
  /// skip a description; load only a static result predicate
  template <
      class Pred,
      std::enable_if_t<detail_::is_static_result_predicate<Pred>> * = nullptr>
  constexpr test(Pred &&) {
    static_assert(detail_::is_static_pass_predicate<Pred>);
  };
  /// skip a description; load only a static pass void
  template <class Void,
            std::enable_if_t<detail_::is_static_pass_void<Void>> * = nullptr>
  constexpr test(Void &&) {
    static_assert(true);
  };
  /// skip a description; load only a dynamic result
  template <
      class Result,
      std::enable_if_t<detail_::is_dynamic_result_type<Result>> * = nullptr>
  test(Result &&result) {
    if (!result.value)
      dynamic_fail();
  };
  /// skip a description; load only a dynamic result predicate
  template <
      class Pred,
      std::enable_if_t<detail_::is_dynamic_result_predicate<Pred>> * = nullptr>
  test(Pred &&pred) {
    if (!pred().value)
      dynamic_fail();
  };

  /// print a description to the console
  inline const test &
  operator<<(const std::string_view &description) const noexcept {
    print_attempt<false>(description);
    return *this;
  }

  /// print a description to the console
  inline test &operator<<(const std::string_view &description) noexcept {
    description_ = description.data();
    print_attempt<>();
    return *this;
  }

  /// assert a static result
  template <
      class Result,
      std::enable_if_t<detail_::is_static_result_type<Result>> * = nullptr>
  constexpr inline const test &operator<<(Result &&) const noexcept {
    static_assert(detail_::nocvref<Result>::value);
    return *this;
  }

  /// assert a static result
  template <
      class Result,
      std::enable_if_t<detail_::is_static_result_type<Result>> * = nullptr>
  constexpr inline test &operator<<(Result &&) noexcept {
    static_assert(detail_::nocvref<Result>::value);
    return *this;
  }

  /// invoke/assert a static result predicate
  template <
      class Pred,
      std::enable_if_t<detail_::is_static_result_predicate<Pred>> * = nullptr>
  constexpr inline const test &operator<<(Pred &&pred) const noexcept {
    static_assert(detail_::nocvref<decltype(pred())>::value);
    return *this;
  }

  /// invoke/assert a static result predicate
  template <
      class Pred,
      std::enable_if_t<detail_::is_static_result_predicate<Pred>> * = nullptr>
  constexpr inline test &operator<<(Pred &&pred) noexcept {
    static_assert(detail_::nocvref<decltype(pred())>::value);
    return *this;
  }

  /// assert true; void functions are static passes
  template <class Void,
            std::enable_if_t<detail_::is_static_pass_void<Void>> * = nullptr>
  constexpr inline const test &operator<<(Void &&) const noexcept {
    static_assert(true);
    return *this;
  }

  /// assert true; void functions are static passes
  template <class Void,
            std::enable_if_t<detail_::is_static_pass_void<Void>> * = nullptr>
  constexpr inline test &operator<<(Void &&) noexcept {
    static_assert(true);
    return *this;
  }

  /// assert a dynamic result
  template <
      class Result,
      std::enable_if_t<detail_::is_dynamic_result_type<Result>> * = nullptr>
  inline const test &operator<<(Result &&result) const noexcept {
    if (!result.value)
      dynamic_fail();
    return *this;
  }

  /// assert a dynamic result
  template <
      class Result,
      std::enable_if_t<detail_::is_dynamic_result_type<Result>> * = nullptr>
  inline test &operator<<(Result &&result) noexcept {
    if (!result.value)
      dynamic_fail();
    return *this;
  }

  /// invoke/assert a dynamic result predicate
  template <
      class Pred,
      std::enable_if_t<detail_::is_dynamic_result_predicate<Pred>> * = nullptr>
  constexpr inline const test &operator<<(Pred &&pred) const noexcept {
    if (!pred().value)
      dynamic_fail();
    return *this;
  }

  /// invoke/assert a dynamic result predicate
  template <
      class Pred,
      std::enable_if_t<detail_::is_dynamic_result_predicate<Pred>> * = nullptr>
  constexpr inline test &operator<<(Pred &&pred) noexcept {
    if (!pred().value)
      dynamic_fail();
    return *this;
  }

private:
  /// pointer to description chars
  /// @private
  const char *description_ = "";
  /// logs a failure message in case of dynamic test failure
  /// @private
  void dynamic_fail() const noexcept {
    std::cout << "\033[01m\033[31mFAIL\033[0m\033[0m " << description_ << '\n';
    std::terminate();
  }
  /// logs the test record from either the member description or argument
  /// @private
  template <bool use_member = true>
  void print_attempt(
      const std::string_view &provided_description = "") const noexcept {
    std::cout << "\033[90mtest\033[0m " << ([&]() {
      if constexpr (use_member)
        return description_;
      else
        return provided_description.data();
    })() << '\n';
  }
};

/*.----------------------------------------------------------------------------,
 /                    cctest namespace operator overloads                   */

/// creates a cctest::test from a string_view and static resulter
///
/// @anchor cctest_stream_operator
/// @ingroup cctest
/// @code
///   auto t0 = "creates a cctest::test" << static_pass;
///   auto t1 = "creates a cctest::test" << [] { return static_pass; };
///   auto t2 = "void functions are pass" << [] { };
/// @endcode
template <class Rhs,
          std::enable_if_t<detail_::is_static_resulter<Rhs>> * = nullptr>
constexpr inline test operator<<(const std::string_view &description,
                                 Rhs &&rhs) {
  test cs{description};
  return cs << rhs;
}

/// creates a cctest::test from a string_view and dynamic resulter
///
/// @anchor cctest_stream_operator
/// @ingroup cctest
/// @code
///   auto t0 = "creates a cctest::test" << dynamic_pass;
///   auto t1 = "creates a cctest::test" << [] { return dynamic_pass; };
/// @endcode
template <class Rhs,
          std::enable_if_t<detail_::is_dynamic_resulter<Rhs>> * = nullptr>
inline test operator<<(const std::string_view &description, Rhs &&rhs) {
  test cs{description};
  return cs << rhs;
}

/*.----------------------------------------------------------------------------,
 /                              static_pass_type                             */

/// represents a static test pass
struct static_pass_type {
  /// static value of the type
  static constexpr bool value = true;

  /// operator&& overload for boolean logic
  template <class Rhs,
            std::enable_if_t<detail_::is_static_result_type<Rhs>> * = nullptr>
  constexpr inline auto operator&&(Rhs) const noexcept
      -> std::conditional_t<detail_::is_static_pass_type<Rhs>,
                            static_pass_type &, static_fail_type>;

  /// operator|| overload for boolean logic
  template <class Rhs,
            std::enable_if_t<detail_::is_static_result_type<Rhs>> * = nullptr>
  constexpr inline auto operator||(Rhs) const noexcept -> static_pass_type;

  /// operator! overload for boolean logic
  constexpr inline auto operator!() const noexcept -> static_fail_type;

  /// operator== overload for boolean comparison
  constexpr inline auto operator==(bool cmp) const noexcept { return cmp; }

  /// operator== overload for boolean comparison
  friend constexpr inline auto operator==(bool cmp,
                                          static_pass_type &) noexcept {
    return cmp;
  }

  /// operator!= overload for boolean comparison
  constexpr inline auto operator!=(bool cmp) const noexcept { return !cmp; }

  /// operator!= overload for boolean comparison
  friend constexpr inline auto operator!=(bool cmp,
                                          static_pass_type &) noexcept {
    return !cmp;
  }
};

/*.----------------------------------------------------------------------------,
 /                              static_fail_type                             */

struct static_fail_type {
  /// static value of the type
  static constexpr bool value = false;

  /// operator&& overload for boolean logic
  template <class Rhs,
            std::enable_if_t<detail_::is_static_result_type<Rhs>> * = nullptr>
  constexpr inline auto operator&&(Rhs) const noexcept -> static_fail_type;

  /// operator|| overload for boolean logic
  template <class Rhs,
            std::enable_if_t<detail_::is_static_result_type<Rhs>> * = nullptr>
  constexpr inline auto operator||(Rhs) const noexcept
      -> std::conditional_t<detail_::is_static_pass_type<Rhs>, static_pass_type,
                            static_fail_type &>;

  /// operator! overload for boolean logic
  constexpr inline auto operator!() const noexcept -> static_pass_type;

  /// operator== overload for boolean comparison
  constexpr inline auto operator==(bool cmp) const noexcept { return !cmp; }

  /// operator== overload for boolean comparison
  friend constexpr inline auto operator==(bool cmp,
                                          static_fail_type &) noexcept {
    return !cmp;
  }

  /// operator!= overload for boolean comparison
  constexpr inline auto operator!=(bool cmp) const noexcept { return cmp; }

  /// operator!= overload for boolean comparison
  friend constexpr inline auto operator!=(bool cmp,
                                          static_fail_type &) noexcept {
    return cmp;
  }
};

/*.----------------------------------------------------------------------------,
 /                   static_pass_type operator definitions                   */

/// operator&& overload for boolean logic
template <class Rhs, std::enable_if_t<detail_::is_static_result_type<Rhs>> *>
constexpr inline auto static_pass_type::operator&&(Rhs) const noexcept
    -> std::conditional_t<detail_::is_static_pass_type<Rhs>, static_pass_type &,
                          static_fail_type> {
  if constexpr (detail_::is_static_pass_type<Rhs>) {
    return *this;
  } else {
    return static_fail_type{};
  }
}

/// operator|| overload for boolean logic
template <class Rhs, std::enable_if_t<detail_::is_static_result_type<Rhs>> *>
constexpr inline auto static_pass_type::operator||(Rhs) const noexcept
    -> static_pass_type {
  return *this;
}

/// operator! overload for boolean logic
constexpr inline auto static_pass_type::operator!() const noexcept
    -> static_fail_type {
  return static_fail_type{};
}

/*.----------------------------------------------------------------------------,
 /                   static_fail_type operator definitions                   */

/// operator&& overload for boolean logic
template <class Rhs, std::enable_if_t<detail_::is_static_result_type<Rhs>> *>
constexpr inline auto static_fail_type::operator&&(Rhs) const noexcept
    -> static_fail_type {
  return *this;
}

/// operator|| overload for boolean logic
template <class Rhs, std::enable_if_t<detail_::is_static_result_type<Rhs>> *>
constexpr inline auto static_fail_type::operator||(Rhs) const noexcept
    -> std::conditional_t<detail_::is_static_pass_type<Rhs>, static_pass_type,
                          static_fail_type &> {
  if constexpr (detail_::is_static_pass_type<Rhs>) {
    return static_pass_type{};
  } else {
    return *this;
  }
}

/// operator! overload for boolean logic
constexpr inline auto static_fail_type::operator!() const noexcept
    -> static_pass_type {
  return static_pass_type{};
}

/*.----------------------------------------------------------------------------,
 /                            dynamic_result_type                            */

struct dynamic_result_type {
  /// runtime value of the type
  const bool value = true;

  /// operator&& overload for boolean logic
  inline dynamic_result_type
  operator&&(const dynamic_result_type &other) const noexcept {
    return {value && other.value};
  };

  /// operator|| overload for boolean logic
  inline dynamic_result_type
  operator||(const dynamic_result_type &other) const noexcept {
    return {value || other.value};
  };

  /// operator! overload for boolean logic
  inline dynamic_result_type operator!() const noexcept { return {!value}; };

  /// operator== overload for boolean comparison
  inline bool operator==(bool cmp) const noexcept { return value == cmp; }

  /// operator== overload for boolean comparison
  friend inline auto operator==(bool cmp,
                                const dynamic_result_type &object) noexcept {
    return cmp == object.value;
  }

  /// operator!= overload for boolean comparison
  inline bool operator!=(bool cmp) const noexcept { return value != cmp; }

  /// operator!= overload for boolean comparison
  friend inline auto operator!=(bool cmp,
                                const dynamic_result_type &object) noexcept {
    return cmp != object.value;
  }
};

/*.----------------------------------------------------------------------------,
 /           static_require and dynamic_require result-type helpers          */

/// creates a `static_pass_type` or `static_fail_type` depending on `cond`
template <bool cond>
constexpr std::conditional_t<cond, static_pass_type, static_fail_type>
    static_require;

/// creates a `dynamic_result_type` loaded with the value of `cond`
constexpr dynamic_result_type dynamic_require(bool cond) { return {cond}; }

/*.----------------------------------------------------------------------------,
 /                   main execution success message logger                   */

/// prints "All Tests Passed!" in bold green to the console to indicate success
///
/// @note any static or dynamic test failures cease execution before this point
inline void success() noexcept {
  std::cout << "\n\033[01m\033[32mAll Tests Passed!\033[0m\033[0m\n";
}

/*.----------------------------------------------------------------------------,
 /                     live test result semantic objects                     */

/// represents a static test pass result
constexpr static_pass_type static_pass;
/// represents a static test fail result
constexpr static_fail_type static_fail;

/// represents a dynamic test pass result
const dynamic_result_type dynamic_pass{true};
/// represents a dynamic test fail result
const dynamic_result_type dynamic_fail{false};

} // namespace cctest

/*.----------------------------------------------------------------------------,
 /                               helper macros                               */

#ifndef CCTEST_DISABLE_MACROS

/// concatenates two tokens
#define CCTEST_DETAIL_PPCAT(a, b) CCTEST_DETAIL_PPCAT_X(a, b)
/// concatenates two tokens (secondary expansion)
#define CCTEST_DETAIL_PPCAT_X(a, b) a##b

/// creates a static test object unique to the line number
///
/// @param feature       - single token feature name to put in "[brackets]"
/// @param literal_descr - descriptive string literal to print to console
/// @code
///   #include <cctest/cctest.h>
///   TEST(my.cool.feature, "here is a test example") << static_require<true>;
/// @endcode
#define TEST(feature, literal_descr)                                           \
  static const auto CCTEST_DETAIL_PPCAT(test_, __LINE__) = cctest::test {      \
    "[" #feature "] " literal_descr                                            \
  }

/// creates a static test object unique to the line number and opens a scope
///
/// @param feature       - single token feature name to put in "[brackets]"
/// @param literal_descr - descriptive string literal to print to console
/// @code
///   #include <cctest/cctest.h>
///   TEST_SCOPE(my.cool.feature, "here is a test scope example") {
///     if constexpr (false) return static_fail;
///     if (false) return dynamic_fail;
///     return dynamic_pass;
///   };
/// @endcode
#define TEST_SCOPE(feature, literal_descr) TEST(feature, literal_descr) << []

/// shorthand for `cctest::static_require<...>`
#define STATIC_REQUIRE(...) cctest::static_require<__VA_ARGS__>
/// shorthand for `cctest::dynamic_require(...)`
#define DYNAMIC_REQUIRE(...) cctest::dynamic_require(__VA_ARGS__)

/// shorthand for `if constexpr(!(...)) return cctest::static_fail`
#define STATIC_CHECK(...)                                                      \
  if constexpr (!(__VA_ARGS__))                                                \
    return cctest::static_fail;

/// shorthand for `if (!(...)) return cctest::dynamic_fail`
#define DYNAMIC_CHECK(...)                                                     \
  if (!(__VA_ARGS__))                                                          \
    return cctest::dynamic_fail;

/// closes a dynamic test scope with a pass (functions must return values)
#define CLOSE_SCOPE return cctest::dynamic_pass;

#endif // CCTEST_DISABLE_MACROS

#ifdef CCTEST_MAIN
int main(int, char **) {
  cctest::success();
  return 0;
}
#endif // CCTEST_MAIN

#endif
