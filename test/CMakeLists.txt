cmake_minimum_required (VERSION 3.15)

function (add_test_executable target source)
    add_executable (${target})
    target_sources (${target} PRIVATE ${source})
    target_link_libraries (${target} PRIVATE utest_static)
    add_test (NAME ${source} COMMAND ${target})
endfunction ()

add_test_executable (assert assert.cpp)
add_test_executable (sample sample.cpp)
