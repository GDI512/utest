#include "assert.hpp"
#include "state.hpp"

int main() {
    test::set_output_buffer();
    test::test();
    return test::exit_code();
}
