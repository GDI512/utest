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
        auto silent() noexcept -> void;
    };

    extern registry state;
    extern console output;

}

#endif
