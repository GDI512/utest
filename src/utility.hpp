#ifndef UTEST_UTILITY_HPP
#define UTEST_UTILITY_HPP

namespace test {

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
