
#include <iostream>

#include "universe.h"

int main(int argc, char **argv)
{
    Universe u;

    Sensor::Ptr s(new Sensor);
    Generator::Ptr g(new Generator);

    s->setPixelSize(0.20);
    s->setBottomLeft(Vector(1.0, -1.0, -1.0));
    s->setTopLeft(Vector(0.0, 1.0, -1.0));
    s->setTopRight(Vector(0.0, 1.0, 1.0));

    g->setGenerationRate(10);
    g->setParticlesSpeed(0.5);
    g->setPosition(Vector(3, 3, 3));
    
    u.addGenerator(g);
    u.addSensor(s);
    // run 100 batches
    for (int i = 0; i < 100; i++) {
        u.nextBatch();
    }
    s->dump();
        
    std::cout << "Hello, world!" << std::endl;
    return 0;
}


// kate: indent-mode cstyle; space-indent on; indent-width 4; replace-tabs on; 
