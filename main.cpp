#include <iostream>
#include "Counter.h"



int main() {

    Counter<std::string> counter;
    counter.add("abc");
    counter.add("a");
    counter.add("abc");
    counter.add("abc");

    counter.add_from_stream(std::cin);

    counter.print_to_stream(std::cout);

}
