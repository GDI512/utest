#include <assert.hpp>
#include <list>

test::executable test::test = test::group([] {

    test::group([] {
        test::require(true);
        test::check(true);
    });

    test::group([] {
        test::require_throw([] { throw 0; });
        test::check_throw([] { throw 0; });
    });

    test::group([] {

        test::require_noexcept([] { return 0; });
        test::check_noexcept([] { return 0; });

        test::group([] {
            std::list<int> array[] = { {1, 1, 1, 1}, {2, 1, 1, 1}, {1, 1, 1, 2} };
            test::check_all_of(array[0].begin(), array[0].end(), [](auto x) { return x == 1; });
            test::check_any_of(array[1].begin(), array[1].end(), [](auto x) { return x == 2; });
            test::check_none_of(array[2].begin(), array[2].end(), [](auto x) { return x == 4; });
        });

    });

});
