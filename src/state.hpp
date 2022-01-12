#ifndef UTEST_STATE_HPP
#define UTEST_STATE_HPP

#include <experimental/source_location>

namespace test {

    using std::experimental::source_location;

    class exit_tag {};

    auto set_output_buffer() noexcept -> void;

    auto clear_state() noexcept -> void;

    auto exit_code() noexcept -> int;

    auto report_error(source_location source) noexcept -> void;

    auto assert_throw(auto&& callable) noexcept {
        try {
            callable();
            return false;
        } catch (...) {
            return true;
        }
    }

    auto assert_noexcept(auto&& callable) noexcept {
        try {
            callable();
            return true;
        } catch (...) {
            return false;
        }
    }

    auto assert_all_of(auto first, auto last, auto&& predicate) noexcept {
        for (; first != last; ++first)
            if (!predicate(*first))
                return false;
        return true;
    }

    auto assert_any_of(auto first, auto last, auto&& predicate) noexcept {
        for (; first != last; ++first)
            if (predicate(*first))
                return true;
        return false;
    }

    auto assert_none_of(auto first, auto last, auto&& predicate) noexcept {
        for (; first != last; ++first)
            if (predicate(*first))
                return false;
        return true;
    }

}

#endif
