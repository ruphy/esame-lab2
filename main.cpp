
#include <iostream>

#include "universe.h"


int main(int argc, char **argv)
{
    Universe u;

    Sensor::Ptr s(new Sensor);
    Generator::Ptr g(new Generator);
    Sphere::Ptr p(new Sphere);

    s->setPixelRows(300);
    s->setPixelColumns(300);
    s->setTopLeft(Vector(0.0, -15.0, 15.0));
    s->setTopRight(Vector(0.0, 15.0, 15.0));
    s->setBottomLeft(Vector(0.0, -15.0, -15.0));

    p->setRadius(3);
    p->setCenter(Vector(3, 0, 0));
//     p->setAccuracy(0.1);
    
    g->setFireRate(10000);
    g->setParticlesSpeed(1);
    g->setPosition(Vector(10, 0.0, 0.0));

    u.addGenerator(g);
    u.addObject(s);
    u.addObject(p);
    u.setBoundary(40);

    // run 100 batches
    for (int i = 0; i < 100; i++) {
        u.nextBatch();
    }

    s->dump();
    
    std::cout << "Hello, world!" << std::endl;
    return 0;
}


// kate: indent-mode cstyle; space-indent on; indent-width 4; replace-tabs on; 
