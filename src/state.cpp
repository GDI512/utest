#include "state.hpp"

#include <iostream>

namespace test::core {

    auto exit_code = exit_success;
    auto indent_count = 0;
    auto output_enabled = true;

    auto error() noexcept -> void {
        exit_code = exit_failure;
    }

    auto state() noexcept -> int {
        return exit_code;
    }

    auto reset() noexcept -> void {
        exit_code = exit_success;
    }

    auto write_group(const char* label) noexcept -> void {
        if (output_enabled) {
            for (auto count = 0; count < indent_count; count++)
                std::cout << "  ";
            std::cout << label << ":\n";
            ++indent_count;
        }
    }

    auto write_group_exit() noexcept -> void {
        if (output_enabled)
            --indent_count;
    }

    auto write_exit() noexcept -> void {
        if (output_enabled)
            std::cout << '\n' << "exit code: " << exit_code << '\n';
    }

    auto write_error(source_location source) noexcept -> void {
        if (output_enabled) {
            for (auto count = 0; count < indent_count; count++)
                std::cout << "  ";
            std::cerr << "error at " << source.file_name() << ':' << source.line() << '\n';
        }
    }

    auto enable_output() noexcept -> void {
        output_enabled = true;
    }

    auto disable_output() noexcept -> void {
        output_enabled = false;
    }

}
