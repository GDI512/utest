#include "common.hpp"

#include <assert.hpp>
#include <cstdlib>
#include <list>

int main() {
    {
        assert(test::check(true));
        assert(!test::check(false));
    }
    {
        assert(test::check_throw([] { throw 0; }));
        assert(!test::check_throw([] { return 0; }));
    }
    {
        assert(test::check_noexcept([] { return 0; }));
        assert(!test::check_noexcept([] { throw 0; }));
    }
    {
        auto list = std::list{1, 1, 1, 1};
        assert(test::check_all_of(list.begin(), list.end(), [](auto x) { return x == 1; }));
        assert(!test::check_all_of(list.begin(), list.end(), [](auto x) { return x == 2; }));
    }
    {
        auto list = std::list{1, 1, 2, 1};
        assert(test::check_any_of(list.begin(), list.end(), [](auto x) { return x == 2; }));
        assert(!test::check_any_of(list.begin(), list.end(), [](auto x) { return x == 4; }));
    }
    {
        auto list = std::list{4, 4, 2, 4};
        assert(test::check_none_of(list.begin(), list.end(), [](auto x) { return x == 8; }));
        assert(!test::check_none_of(list.begin(), list.end(), [](auto x) { return x == 4; }));
    }
    {
        {
            test::clear_state();
            test::group([] {
                test::require(true);
            });
            assert(test::exit_code() == EXIT_SUCCESS);
        }
        {
            test::clear_state();
            test::group([] {
                test::require(false);
            });
            assert(test::exit_code() == EXIT_FAILURE);
        }
    }
    {
        {
            test::clear_state();
            test::group([] {
                test::require_throw([] { throw 0; });
            });
            assert(test::exit_code() == EXIT_SUCCESS);
        }
        {
            test::clear_state();
            test::group([] {
                test::require_throw([] { return 0; });
            });
            assert(test::exit_code() == EXIT_FAILURE);
        }
    }
    {
        {
            test::clear_state();
            test::group([] {
                test::require_noexcept([] { return 0; });
            });
            assert(test::exit_code() == EXIT_SUCCESS);
        }
        {
            test::clear_state();
            test::group([] {
                test::require_noexcept([] { throw 0; });
            });
            assert(test::exit_code() == EXIT_FAILURE);
        }
    }
    {
        auto list = std::list{1, 1, 1, 1};
        {
            test::clear_state();
            test::group([=] {
                test::require_all_of(list.begin(), list.end(), [](auto x) { return x == 1; });
            });
            assert(test::exit_code() == EXIT_SUCCESS);
        }
        {
            test::clear_state();
            test::group([=] {
                test::require_all_of(list.begin(), list.end(), [](auto x) { return x == 2; });
            });
            assert(test::exit_code() == EXIT_FAILURE);
        }
    }
    {
        auto list = std::list{1, 1, 2, 1};
        {
            test::clear_state();
            test::group([=] {
                test::require_any_of(list.begin(), list.end(), [](auto x) { return x == 2; });
            });
            assert(test::exit_code() == EXIT_SUCCESS);
        }
        {
            test::clear_state();
            test::group([=] {
                test::require_any_of(list.begin(), list.end(), [](auto x) { return x == 4; });
            });
            assert(test::exit_code() == EXIT_FAILURE);
        }
    }
    {
        auto list = std::list{4, 4, 2, 4};
        {
            test::clear_state();
            test::group([=] {
                test::require_none_of(list.begin(), list.end(), [](auto x) { return x == 8; });
            });
            assert(test::exit_code() == EXIT_SUCCESS);
        }
        {
            test::clear_state();
            test::group([=] {
                test::require_none_of(list.begin(), list.end(), [](auto x) { return x == 4; });
            });
            assert(test::exit_code() == EXIT_FAILURE);
        }
    }
}
