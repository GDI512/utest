cmake_minimum_required (VERSION 3.15)

function (add_test_executable target source)
    add_executable (${target})
    target_sources (${target} PRIVATE ${source})
    target_link_libraries (${target} PRIVATE utest::utest)
    add_test (NAME ${source} COMMAND ${target})
endfunction ()

add_test_executable (main main.cpp)
add_test_executable (state state.cpp)
add_test_executable (assert assert.cpp)
