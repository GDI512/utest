#include "common.hpp"

#include <state.hpp>
#include <list>

int main() {
    {
        assert(test::core::state() == test::core::exit_success);
        test::core::error();
        assert(test::core::state() == test::core::exit_failure);
        test::core::reset();
        assert(test::core::state() == test::core::exit_success);
    }
    {
        assert(test::core::check_throw([] { throw 0; }));
        assert(!test::core::check_throw([] { return 0; }));
    }
    {
        assert(test::core::check_noexcept([] { return 0; }));
        assert(!test::core::check_noexcept([] { throw 0; }));
    }
    {
        std::list<int> array[] = {
            {1, 1, 1, 1},
            {2, 1, 1, 1},
            {1, 1, 1, 2},
            {1, 1, 2, 1}
        };
        assert( test::core::check_all_of(array[0].begin(), array[0].end(),
            [](auto x) { return x == 1; }));
        assert(!test::core::check_all_of(array[1].begin(), array[1].end(),
            [](auto x) { return x == 1; }));
        assert(!test::core::check_all_of(array[2].begin(), array[2].end(),
            [](auto x) { return x == 1; }));
        assert(!test::core::check_all_of(array[3].begin(), array[3].end(),
            [](auto x) { return x == 1; }));
    }
    {
        std::list<int> array[] = {
            {4, 2, 2, 2},
            {2, 2, 2, 4},
            {2, 2, 4, 2},
            {2, 2, 2, 2}
        };
        assert( test::core::check_any_of(array[0].begin(), array[0].end(),
            [](auto x) { return x == 4; }));
        assert( test::core::check_any_of(array[1].begin(), array[1].end(),
            [](auto x) { return x == 4; }));
        assert( test::core::check_any_of(array[2].begin(), array[2].end(),
            [](auto x) { return x == 4; }));
        assert(!test::core::check_any_of(array[3].begin(), array[3].end(),
            [](auto x) { return x == 4; }));
    }
    {
        std::list<int> array[] = {
            {8, 4, 4, 4},
            {4, 4, 4, 8},
            {4, 4, 8, 4},
            {4, 4, 4, 4}
        };
        assert(!test::core::check_none_of(array[0].begin(), array[0].end(),
            [](auto x) { return x == 8; }));
        assert(!test::core::check_none_of(array[1].begin(), array[1].end(),
            [](auto x) { return x == 8; }));
        assert(!test::core::check_none_of(array[2].begin(), array[2].end(),
            [](auto x) { return x == 8; }));
        assert( test::core::check_none_of(array[3].begin(), array[3].end(),
            [](auto x) { return x == 8; }));
    }
}
