
#include <iostream>

#include "vector.h"

int main(int argc, char **argv)
{
    Vector v1, v2;
    v1.setX(3);
    v1.setY(2);
    v1.setZ(1);
    v2.setX(1);
    v2.setY(2);
    v2.setZ(3);
    
   Vector::cross(v1,v2).dump();
    
    std::cout << "Hello, world!" << std::endl;
    return 0;
}


// kate: indent-mode cstyle; space-indent on; indent-width 4; replace-tabs on; 
