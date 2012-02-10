
#include <iostream>

#include "universe.h"

int main(int argc, char **argv)
{
    Universe u;

    Sensor::Ptr s(new Sensor);
    Generator::Ptr g(new Generator);

    s->setPixelSize(1.10);
    s->setTopLeft(Vector(0.0, -10.0, 10.0));
    s->setTopRight(Vector(0.0, 10.0, 10.0));
    s->setBottomLeft(Vector(0.0, -10.0, -10.0));

    g->setGenerationRate(200);
    g->setParticlesSpeed(0.5);
    g->setPosition(Vector(1.0, 0.0, 0));
    
    u.addGenerator(g);
    u.addSensor(s);
    // run 100 batches
    for (int i = 0; i < 1; i++) {
        u.nextBatch();
    }
    s->dump();
        
    std::cout << "Hello, world!" << std::endl;
    return 0;
}


// kate: indent-mode cstyle; space-indent on; indent-width 4; replace-tabs on; 
