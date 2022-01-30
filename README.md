# About
This is a small, macro-free unit testing library designed to provide most of the
functionality of larger testing frameworks without the associated compile time overhead.
Instead of relying on the preprocessor, it makes use of the C++20 <source_location> and
lambda expressions, making the structure of your tests more similar to the actual C++
code.

# Getting started
For now, the best way to add μtest to your (CMake) project is to clone this repository and
add it via the `add_subdirectory()` command. This will create the alias target
`utest::utest` that can be linked to your executables just like any other library through `target_link_libraries()`.

The example below is a sample test pasted from *test/vector.cpp*. It demonstrates almost
all of μtest's features, most notably the way your executables interact with the
predefined `main()` function.

```c++
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
```

# Reference

## Test cases and the executable
* `test::executable` - A function pointer with `void` return type and zero arguments. It
  is called from the library's `main()`
* `test::group(const char*, auto&&)` - A test case that defines a context for assertions.
  Catches all unhandled exceptions, can be terminated early by one of `test::require_*`
  functions.

## Assertions
* `test::check(bool)` - Tests the boolean value of an expression
* `test::check_throw(auto&&)` - Fails if the callback function executes without throwing
  any exceptions
* `test::check_noexcept(auto&&)` - Fails if the callback function throws an exception
* `test::check_all_of(auto, auto, auto&&)` - Fails with the first value in designated
  range  that does not satisfy the predicate
* `test::check_any_of(auto, auto, auto&&)` - Fails when none of the values in designated
  range satisfy the predicate
* `test::check_none_of(auto, auto, auto&&)` - Fails with the first value in designated
  range that satisfies the predicate
* `test::require*` - For every `test::check*` there is a corresponding `test::require*`
  assertion that exits the scope of its group when it fails, making it possible to
  effectively exclude some part of the test from execution

## Command line
* If the first option passed to the test executable is *--silent*, the output will be
  disabled
