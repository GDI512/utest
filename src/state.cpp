#include "state.hpp"

#include <cstdlib>
#include <cstdio>

namespace test {

    registry state = {};
    console output = {};

    registry::registry() noexcept : exit_code(exit_success) {}

    auto registry::error() noexcept -> void {
        exit_code = exit_failure;
    }

    auto registry::clear() noexcept -> void {
        exit_code = exit_success;
    }

    auto registry::get() const noexcept -> int {
        return exit_code;
    }

    console::console() noexcept : is_open(true) {}

    auto console::error(source_location source) noexcept -> void {
        if (is_open) {
            fprintf(stderr, "%s:%u:%u: assertion failure\n",
              source.file_name(), source.line(), source.column());
        }
    }

    auto console::open() noexcept -> void {
        is_open = true;
    }

    auto console::silence() noexcept -> void {
        is_open = false;
    }

    auto setvbuf() noexcept -> void {
        static char buffer[BUFSIZ];
        setvbuf(stderr, buffer, _IOFBF, BUFSIZ);
    }

}
