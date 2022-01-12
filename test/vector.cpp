#include <assert.hpp>

#include <utility>
#include <vector>

test::executable test::test = test::group([] {

    test::group([] {
        test::group([] {
            const auto object = std::vector<int>();
            test::check(object.empty());
        });

        test::group([] {
            const auto object = std::vector<int>(64);
            test::check(object.size() == 64);
            test::check(object.capacity() == 64);
        });

        test::group([] {
            const auto object = std::vector<int>(64);
            const auto other = std::vector<int>(object);
            test::check(other.size() == 64);
            test::check(other.capacity() == 64);
        });

        test::group([] {
            const auto object = std::vector<int>(64);
            const auto other = std::vector<int>(std::move(object));
            test::check(other.size() == 64);
            test::check(other.capacity() == 64);
        });
    });

    test::group([] {
        test::group([] {
            auto object = std::vector<int>(64);
            object.push_back(8);
            test::check(object.size() == 65);
            test::check(object.capacity() > 65);
        });

        test::group([] {
            auto object = std::vector<int>(64);
            object.pop_back();
            test::check(object.size() == 63);
            test::check(object.capacity() == 64);
        });
    });

    test::group([] {
        auto object = std::vector<int>{4, 4, 4, 4};
        test::check_all_of(object.begin(), object.end(), [&](auto x) { return x == 4; });
        test::check_noexcept([&] { static_cast<void>(object.at(3)); });
        test::check_throw([&] { static_cast<void>(object.at(4)); });
    });

});
