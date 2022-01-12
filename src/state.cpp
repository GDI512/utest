#include "state.hpp"

#include <cstdlib>
#include <cstdio>

namespace test {

    int code = EXIT_SUCCESS;

    auto clear_state() noexcept -> void {
        code = EXIT_SUCCESS;
    }

    auto set_output_buffer() noexcept -> void {
        static char buffer[BUFSIZ];
        setvbuf(stderr, buffer, _IOFBF, BUFSIZ);
    }

    auto exit_code() noexcept -> int {
        return code;
    }

    auto report_error(source_location source) noexcept -> void {
        code |= EXIT_FAILURE;
        fprintf(stderr, "%s:%u:%u: assertion failure\n", source.file_name(),
          source.line(), source.column());
    }

}
