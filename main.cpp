
#include <iostream>

#include "universe.h"

int main(int argc, char **argv)
{
    Universe u;
    Sensor s;

    // run 100 batches
    for (int i = 0; i < 100; i++) {
        u.nextBatch();
    }
        
    std::cout << "Hello, world!" << std::endl;
    return 0;
}


// kate: indent-mode cstyle; space-indent on; indent-width 4; replace-tabs on; 
