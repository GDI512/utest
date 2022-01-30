#ifndef UTEST_ASSERT_HPP
#define UTEST_ASSERT_HPP

#include "state.hpp"

namespace test {

    using core::source_location;
    using executable = auto (*)() -> void;

    extern executable test;

    auto group(const char* label, auto&& callable,
      source_location source = source_location::current()) noexcept {
        core::write_group(label);
        try {
            callable();
        } catch (const core::require_tag&) {
        } catch (...) {
            core::error();
            core::write_error(source);
        }
        core::write_group_exit();
    }

    inline auto check(bool expression,
      source_location source = source_location::current()) noexcept {
        if (!expression) {
            core::error();
            core::write_error(source);
        }
        return expression;
    }

    auto check_throw(auto&& callable,
      source_location source = source_location::current()) noexcept {
        const auto result = core::check_throw(callable);
        if (!result) {
            core::error();
            core::write_error(source);
        }
        return result;
    }

    auto check_noexcept(auto&& callable,
      source_location source = source_location::current()) noexcept {
        const auto result = core::check_noexcept(callable);
        if (!result) {
            core::error();
            core::write_error(source);
        }
        return result;
    }

    auto check_all_of(auto first, auto last, auto&& predicate,
      source_location source = source_location::current()) noexcept {
        const auto result = core::check_all_of(first, last, predicate);
        if (!result) {
            core::error();
            core::write_error(source);
        }
        return result;
    }

    auto check_any_of(auto first, auto last, auto&& predicate,
      source_location source = source_location::current()) noexcept {
        const auto result = core::check_any_of(first, last, predicate);
        if (!result) {
            core::error();
            core::write_error(source);
        }
        return result;
    }

    auto check_none_of(auto first, auto last, auto&& predicate,
      source_location source = source_location::current()) noexcept {
        const auto result = core::check_none_of(first, last, predicate);
        if (!result) {
            core::error();
            core::write_error(source);
        }
        return result;
    }

    inline auto require(bool expression,
      source_location source = source_location::current()) {
        if (!check(expression, source))
            throw core::require_tag();
    }

    auto require_throw(auto&& callable,
      source_location source = source_location::current()) {
        if (!check_throw(callable, source))
            throw core::require_tag();
    }

    auto require_noexcept(auto&& callable,
      source_location source = source_location::current()) {
        if (!check_noexcept(callable, source))
            throw core::require_tag();
    }

    auto require_all_of(auto first, auto last, auto&& predicate,
      source_location source = source_location::current()) {
        if (!check_all_of(first, last, predicate, source))
            throw core::require_tag();
    }

    auto require_any_of(auto first, auto last, auto&& predicate,
      source_location source = source_location::current()) {
        if (!check_any_of(first, last, predicate, source))
            throw core::require_tag();
    }

    auto require_none_of(auto first, auto last, auto&& predicate,
      source_location source = source_location::current()) {
        if (!check_none_of(first, last, predicate, source))
            throw core::require_tag();
    }

}

#endif
