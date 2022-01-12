#ifndef UTEST_ASSERT_HPP
#define UTEST_ASSERT_HPP

#include "state.hpp"

namespace test {

    using executable = auto (*)() -> void;
    extern executable test;

    auto group(auto&& callable, source_location source = source_location::current()) noexcept {
        try {
            callable();
        } catch (const exit_tag&) {
            ;
        } catch (...) {
            report_error(source);
        }
    }

    inline auto check(bool expression,
      source_location source = source_location::current()) noexcept {
        if (!expression)
            report_error(source);
        return expression;
    }

    auto check_throw(auto&& callable,
      source_location source = source_location::current()) noexcept {
        const auto result = test_throw(callable);
        if (!result)
            report_error(source);
        return result;
    }

    auto check_noexcept(auto&& callable,
      source_location source = source_location::current()) noexcept {
        const auto result = test_noexcept(callable);
        if (!result)
            report_error(source);
        return result;
    }

    auto check_all_of(auto first, auto last, auto&& predicate,
      source_location source = source_location::current()) noexcept {
        const auto result = test_all_of(first, last, predicate);
        if (!result)
            report_error(source);
        return result;
    }

    auto check_any_of(auto first, auto last, auto&& predicate,
      source_location source = source_location::current()) noexcept {
        const auto result = test_any_of(first, last, predicate);
        if (!result)
            report_error(source);
        return result;
    }

    auto check_none_of(auto first, auto last, auto&& predicate,
      source_location source = source_location::current()) noexcept {
        const auto result = test_none_of(first, last, predicate);
        if (!result)
            report_error(source);
        return result;
    }

    inline auto require(bool expression,
      source_location source = source_location::current()) {
        if (!check(expression, source))
            throw exit_tag();
    }

    auto require_throw(auto&& callable,
      source_location source = source_location::current()) {
        if (!check_throw(callable, source))
            throw exit_tag();
    }

    auto require_noexcept(auto&& callable,
      source_location source = source_location::current()) {
        if (!check_noexcept(callable, source))
            throw exit_tag();
    }

    auto require_all_of(auto first, auto last, auto&& predicate,
      source_location source = source_location::current()) {
        if (!check_all_of(first, last, predicate, source))
            throw exit_tag();
    }

    auto require_any_of(auto first, auto last, auto&& predicate,
      source_location source = source_location::current()) {
        if (!check_any_of(first, last, predicate, source))
            throw exit_tag();
    }

    auto require_none_of(auto first, auto last, auto&& predicate,
      source_location source = source_location::current()) {
        if (!check_none_of(first, last, predicate, source))
            throw exit_tag();
    }

}

#endif
