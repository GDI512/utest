#include "assert.hpp"
#include "state.hpp"

#include <string_view>
#include <iostream>

using namespace std::string_view_literals;

int main(int argc, char** argv) {
    std::cerr.rdbuf()->pubsetbuf(new char[4096], 4096);
    if (argc > 1 && argv[1] == "--silent"sv)
        test::output.silent();
    test::test();
    return test::state.get();
}
