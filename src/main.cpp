#include "assert.hpp"
#include "state.hpp"

#include <string_view>
#include <iostream>

using namespace std::string_view_literals;

int main(int argc, char** argv) {
    if (argc > 1 && argv[1] == "--silent"sv) {
        test::core::disable_output();
    } else {
        std::cout.rdbuf()->pubsetbuf(new char[4096], 4096);
        std::cerr.rdbuf()->pubsetbuf(new char[4096], 4096);
    }
    test::test();
    test::core::write_exit();
    return test::core::state();
}
