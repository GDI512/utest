#ifndef UTEST_STATE_HPP
#define UTEST_STATE_HPP

#include <experimental/source_location>

namespace test {

    using std::experimental::source_location;

    constexpr auto exit_success = 0;
    constexpr auto exit_failure = 1;

    class registry {
      private:
        int exit_code;

      public:
        registry() noexcept;

      public:
        auto error() noexcept -> void;
        auto clear() noexcept -> void;
        auto get() const noexcept -> int;
    };

    class console {
      private:
        bool is_open;

      public:
        console() noexcept;

      public:
        auto error(source_location source) noexcept -> void;
        auto open() noexcept -> void;
        auto silence() noexcept -> void;
    };

    extern registry state;
    extern console output;

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
