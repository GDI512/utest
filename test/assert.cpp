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
        test::core::reset();
        test::group("group.empty", [] {});
        assert(test::core::state() == test::core::exit_success);
    }
    {
        test::core::reset();
        test::group("group.throw", [] {
            throw 0;
        });
        assert(test::core::state() == test::core::exit_failure);
    }
    {
        {
            test::core::reset();
            test::group("require.true", [] {
                test::require(true);
            });
            assert(test::core::state() == test::core::exit_success);
        }
        {
            test::core::reset();
            test::group("require.false", [] {
                test::require(false);
            });
            assert(test::core::state() == test::core::exit_failure);
        }
    }
    {
        {
            test::core::reset();
            test::group("require.throw.true", [] {
                test::require_throw([] { throw 0; });
            });
            assert(test::core::state() == test::core::exit_success);
        }
        {
            test::core::reset();
            test::group("require.throw.false", [] {
                test::require_throw([] { return 0; });
            });
            assert(test::core::state() == test::core::exit_failure);
        }
    }
    {
        {
            test::core::reset();
            test::group("require.noexcept.true", [] {
                test::require_noexcept([] { return 0; });
            });
            assert(test::core::state() == test::core::exit_success);
        }
        {
            test::core::reset();
            test::group("require.noexcept.false", [] {
                test::require_noexcept([] { throw 0; });
            });
            assert(test::core::state() == test::core::exit_failure);
        }
    }
    {
        auto list = std::list{1, 1, 1, 1};
        {
            test::core::reset();
            test::group("require.all_of.true", [=] {
                test::require_all_of(list.begin(), list.end(), [](auto x) { return x == 1; });
            });
            assert(test::core::state() == test::core::exit_success);
        }
        {
            test::core::reset();
            test::group("require.all_of.false", [=] {
                test::require_all_of(list.begin(), list.end(), [](auto x) { return x == 2; });
            });
            assert(test::core::state() == test::core::exit_failure);
        }
    }
    {
        auto list = std::list{1, 1, 2, 1};
        {
            test::core::reset();
            test::group("require.any_of.true", [=] {
                test::require_any_of(list.begin(), list.end(), [](auto x) { return x == 2; });
            });
            assert(test::core::state() == test::core::exit_success);
        }
        {
            test::core::reset();
            test::group("require.any_of.false", [=] {
                test::require_any_of(list.begin(), list.end(), [](auto x) { return x == 4; });
            });
            assert(test::core::state() == test::core::exit_failure);
        }
    }
    {
        auto list = std::list{4, 4, 2, 4};
        {
            test::core::reset();
            test::group("require.none__of.true", [=] {
                test::require_none_of(list.begin(), list.end(), [](auto x) { return x == 8; });
            });
            assert(test::core::state() == test::core::exit_success);
        }
        {
            test::core::reset();
            test::group("require.none_of.false", [=] {
                test::require_none_of(list.begin(), list.end(), [](auto x) { return x == 4; });
            });
            assert(test::core::state() == test::core::exit_failure);
        }
    }
}
