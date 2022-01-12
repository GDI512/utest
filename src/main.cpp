#include "assert.hpp"
#include "state.hpp"

#include <cstring>
#include <cstdio>

char stdbuf[BUFSIZ];

int main(int argc, char** argv) {
    setvbuf(stderr, stdbuf, _IOFBF, BUFSIZ);
    if (argc > 1 && strcmp(argv[1], "--silent") == 0)
        test::output.silence();
    test::test();
    return test::state.get();
}
