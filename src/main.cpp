#include "assert.hpp"
#include "state.hpp"

int main() {
    test::setvbuf();
    test::test();
    return test::exit_code();
}
