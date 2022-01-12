#ifndef UTEST_ASSERT_HPP
#define UTEST_ASSERT_HPP

#include "state.hpp"

namespace test {

    using core::source_location;
    using core::require_error;

    inline auto check(bool expression,
      source_location source = source_location::current()) noexcept {
        core::report(expression, source);
        return expression;
    }

    auto check_throw(auto&& callable,
      source_location source = source_location::current()) noexcept {
        const auto result = core::check_throw(callable);
        core::report(result, source);
        return result;
    }

    auto check_noexcept(auto&& callable,
      source_location source = source_location::current()) noexcept {
        const auto result = core::check_noexcept(callable);
        core::report(result, source);
        return result;
    }

    auto check_all_of(auto first, auto last, auto&& predicate,
      source_location source = source_location::current()) noexcept {
        const auto result = core::check_all_of(first, last, predicate);
        core::report(result, source);
        return result;
    }

    auto check_any_of(auto first, auto last, auto&& predicate,
      source_location source = source_location::current()) noexcept {
        const auto result = core::check_any_of(first, last, predicate);
        core::report(result, source);
        return result;
    }

    auto check_none_of(auto first, auto last, auto&& predicate,
      source_location source = source_location::current()) noexcept {
        const auto result = core::check_none_of(first, last, predicate);
        core::report(result, source);
        return result;
    }

    inline auto require(bool expression,
      source_location source = source_location::current()) {
        if (!check(expression, source))
            throw require_error();
    }

    auto require_throw(auto&& callable,
      source_location source = source_location::current()) {
        if (!check_throw(callable, source))
            throw require_error();
    }

    auto require_noexcept(auto&& callable,
      source_location source = source_location::current()) {
        if (!check_noexcept(callable, source))
            throw require_error();
    }

    auto require_all_of(auto first, auto last, auto&& predicate,
      source_location source = source_location::current()) {
        if (!check_all_of(first, last, predicate, source))
            throw require_error();
    }

    auto require_any_of(auto first, auto last, auto&& predicate,
      source_location source = source_location::current()) {
        if (!check_any_of(first, last, predicate, source))
            throw require_error();
    }

    auto require_none_of(auto first, auto last, auto&& predicate,
      source_location source = source_location::current()) {
        if (!check_none_of(first, last, predicate, source))
            throw require_error();
    }

}

#endif
