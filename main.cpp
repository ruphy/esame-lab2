
#include <iostream>

#include "vector.h"

int main(int argc, char **argv)
{
    Vector v1, v2;
    v1.setX(23);
    v2 = (v1*3);
    
    if (v2 == (v1*3)) {
        std::cout << v2.scal(v1) << std::endl;
    }
    
    std::cout << "Hello, world!" << std::endl;
    return 0;
}


// kate: indent-mode cstyle; space-indent on; indent-width 4; replace-tabs on; 
