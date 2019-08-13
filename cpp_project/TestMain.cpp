
#include <thread>
#include <iostream>

#include "MonoBridge.h"

MonoBridge* m = NULL;

void foo() {
    // call Foo in the mono assembly
    m->foo();
}

int main(int argc, char **argv) {

    m = new MonoBridge();

    /*
    // works ok:
    for (int i=0; i<100; i++){
        foo();
    }
    */

    // fails: calling foo in a new thread locks up mono
    std::cout << "This should call Foo a hundred times, but hangs..." << std::endl;
    for (int i=0; i<100; i++){
        std::cout << "call Foo " << i << std::endl;
        std::thread t(&foo);
        t.join();
    }
    return 0;
}
