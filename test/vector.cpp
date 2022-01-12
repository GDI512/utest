#include <utest.hpp>

#include <vector>

test::executable test::test = [] {

    test::group("vector.cons", [] {
        test::group("empty", [] {
            const auto object = std::vector<int>();
            test::check(object.empty());
        });

        test::group("size", [] {
            const auto object = std::vector<int>(64);
            test::check(object.size() == 64);
            test::check(object.capacity() == 64);
        });

        test::group("copy", [] {
            const auto object = std::vector<int>(64);
            const auto other = std::vector<int>(object);
            test::check(other.size() == 64);
            test::check(other.capacity() == 64);
        });

        test::group("move", [] {
            const auto object = std::vector<int>(64);
            const auto other = std::vector<int>(std::move(object));
            test::check(other.size() == 64);
            test::check(other.capacity() == 64);
        });
    });

    test::group("vector.modifiers", [] {
        test::group("push_back", [] {
            auto object = std::vector<int>(64);
            object.push_back(8);
            test::check(object.size() == 65);
            test::check(object.capacity() > 65);
        });

        test::group("pop_back", [] {
            auto object = std::vector<int>(64);
            object.pop_back();
            test::check(object.size() == 63);
            test::check(object.capacity() == 64);
        });
    });

    test::group("vector.data", [] {
        auto object = std::vector<int>{4, 4, 4, 4};
        test::check_all_of(object.begin(), object.end(), [&](auto x) { return x == 4; });
        test::check_noexcept([&] { static_cast<void>(object.at(3)); });
        test::check_throw([&] { static_cast<void>(object.at(4)); });
    });

};
