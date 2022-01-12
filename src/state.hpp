#ifndef UTEST_STATE_HPP
#define UTEST_STATE_HPP

#include <experimental/source_location>

namespace test::core {

    using std::experimental::source_location;

    class require_error {};

    auto report(bool result, source_location source) noexcept -> void;

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
