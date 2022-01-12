#ifndef UTEST_STATE_HPP
#define UTEST_STATE_HPP

#include <experimental/source_location>

namespace test::core {

    using std::experimental::source_location;

    class require_tag {};

    constexpr auto exit_success = 0;
    constexpr auto exit_failure = 1;

    auto error() noexcept -> void;

    auto state() noexcept -> int;

    auto reset() noexcept -> void;

    auto write_group(const char* label) noexcept -> void;

    auto write_group_exit() noexcept -> void;

    auto write_exit() noexcept -> void;

    auto write_error(source_location source) noexcept -> void;

    auto enable_output() noexcept -> void;

    auto disable_output() noexcept -> void;

    auto check_throw(auto&& callable) noexcept {
        try {
            callable();
            return false;
        } catch (...) {
            return true;
        }
    }

    auto check_noexcept(auto&& callable) noexcept {
        try {
            callable();
            return true;
        } catch (...) {
            return false;
        }
    }

    auto check_all_of(auto first, auto last, auto&& predicate) noexcept {
        for (; first != last; ++first)
            if (!predicate(*first))
                return false;
        return true;
    }

    auto check_any_of(auto first, auto last, auto&& predicate) noexcept {
        for (; first != last; ++first)
            if (predicate(*first))
                return true;
        return false;
    }

    auto check_none_of(auto first, auto last, auto&& predicate) noexcept {
        for (; first != last; ++first)
            if (predicate(*first))
                return false;
        return true;
    }

}

#endif
