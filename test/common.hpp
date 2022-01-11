#ifndef CPPLTF_TEST_COMMON_HPP
#define CPPLTF_TEST_COMMON_HPP

#include <cstdlib>
#include <cstdio>

#undef assert
#define assert(x)                                   \
    if (!(x)) {                                     \
        std::printf("Line: %i %s\n", __LINE__, #x); \
        std::exit(1);                               \
    }


#endif
