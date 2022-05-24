#include <stdio.h>

#include "../Core/String.h"

int parseArguments();

///

int main(
    int argc, 
    const char * argv[]) {

    // printf("hello world\n");

    auto a = parseArguments();

    ///

    using namespace Core;

    String s = String();

    

    auto n = s.foo();

    ///

    return 0;
}

///

int parseArguments() {

    printf("parse arguments\n");

    ///

    return 0;
}