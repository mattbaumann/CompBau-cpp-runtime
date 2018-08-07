#include "catch-1.10.h"
#include "HelloWorld.h"

#include <iostream>

TEST_CASE("Hello World") {
    HelloWorld(std::cout);
}