#include "common.hpp"

#include <utility.hpp>
#include <state.hpp>
#include <list>

int main() {
    {
        assert(test::state.get() == test::exit_success);
        test::state.error();
        assert(test::state.get() == test::exit_failure);
        test::state.clear();
        assert(test::state.get() == test::exit_success);
    }
}
