#include "state.hpp"

#include <string_view>
#include <iostream>

using namespace std::string_view_literals;

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
        if (is_open)
            std::cerr << source.file_name() << ':' << source.line() << ':' << source.column()
              << ": "sv << "assertion failure"sv << '\n';
    }

    auto console::open() noexcept -> void {
        is_open = true;
    }

    auto console::silent() noexcept -> void {
        is_open = false;
    }

}
