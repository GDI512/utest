#include "common.hpp"

#include <state.hpp>
#include <list>

int main() {
    {
        assert(test::exit_code() == EXIT_SUCCESS);
        test::report_error(test::source_location::current());
        assert(test::exit_code() == EXIT_FAILURE);
        test::clear_state();
        assert(test::exit_code() == EXIT_SUCCESS);
    }
    {
        assert(test::assert_throw([] { throw 0; }));
        assert(!test::assert_throw([] { return 0; }));
    }
    {
        assert(test::assert_noexcept([] { return 0; }));
        assert(!test::assert_noexcept([] { throw 0; }));
    }
    {
        std::list<int> array[] = {
            {1, 1, 1, 1},
            {2, 1, 1, 1},
            {1, 1, 1, 2},
            {1, 1, 2, 1}
        };
        assert( test::assert_all_of(array[0].begin(), array[0].end(), [](auto x) { return x == 1; }));
        assert(!test::assert_all_of(array[1].begin(), array[1].end(), [](auto x) { return x == 1; }));
        assert(!test::assert_all_of(array[2].begin(), array[2].end(), [](auto x) { return x == 1; }));
        assert(!test::assert_all_of(array[3].begin(), array[3].end(), [](auto x) { return x == 1; }));
    }
    {
        std::list<int> array[] = {
            {4, 2, 2, 2},
            {2, 2, 2, 4},
            {2, 2, 4, 2},
            {2, 2, 2, 2}
        };
        assert( test::assert_any_of(array[0].begin(), array[0].end(), [](auto x) { return x == 4; }));
        assert( test::assert_any_of(array[1].begin(), array[1].end(), [](auto x) { return x == 4; }));
        assert( test::assert_any_of(array[2].begin(), array[2].end(), [](auto x) { return x == 4; }));
        assert(!test::assert_any_of(array[3].begin(), array[3].end(), [](auto x) { return x == 4; }));
    }
    {
        std::list<int> array[] = {
            {8, 4, 4, 4},
            {4, 4, 4, 8},
            {4, 4, 8, 4},
            {4, 4, 4, 4}
        };
        assert(!test::assert_none_of(array[0].begin(), array[0].end(), [](auto x) { return x == 8; }));
        assert(!test::assert_none_of(array[1].begin(), array[1].end(), [](auto x) { return x == 8; }));
        assert(!test::assert_none_of(array[2].begin(), array[2].end(), [](auto x) { return x == 8; }));
        assert( test::assert_none_of(array[3].begin(), array[3].end(), [](auto x) { return x == 8; }));
    }
}
