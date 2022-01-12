#include "assert.hpp"
#include "state.hpp"

#include <string_view>
#include <iostream>

using namespace std::string_view_literals;

char coutbuf[4096];
char cerrbuf[4096];

int main(int argc, char** argv) {
    std::cout.rdbuf()->pubsetbuf(coutbuf, 4096);
    std::cerr.rdbuf()->pubsetbuf(cerrbuf, 4096);
    if (argc > 1 && argv[1] == "--silent"sv)
        test::core::disable_output();
    test::test();
    test::core::write_exit();
    return test::core::state();
}
