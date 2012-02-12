
#include <iostream>

#include "universe.h"


int main(int argc, char **argv)
{
    Universe u;

    Sensor::Ptr s(new Sensor);
//     Sensor::Ptr s2(new Sensor);
    Generator::Ptr g(new Generator);
    Generator::Ptr g2(new Generator);

    s->setPixelRows(1);
    s->setPixelColumns(1);
    s->setTopLeft(Vector(0.0, -10.0, 10.0));
    s->setTopRight(Vector(0.0, 10.0, 10.0));
    s->setBottomLeft(Vector(0.0, -10.0, -10.0));

//     s2->setPixelRows(20);
//     s2->setPixelColumns(20);
//     s2->setTopLeft(Vector(5.0, -10.0, 10.0));
//     s2->setTopRight(Vector(5.0, 10.0, 10.0));
//     s2->setBottomLeft(Vector(5.0, -10.0, -10.0));
    
    g->setGenerationRate(500);
    g->setParticlesSpeed(5);
    g->setPosition(Vector(23.0, 0.0, 0.0));


    g2->setGenerationRate(500);
    g2->setParticlesSpeed(5);
    g2->setPosition(Vector(1.0, 0.0, 5.0));
    
    u.addGenerator(g);
//     u.addGenerator(g2);
    u.addSensor(s);
//     u.addSensor(s2);

    // run 100 batches
    for (int i = 0; i < 1; i++) {
        u.nextBatch();
    }

    s->dump();
//     s2->dump();
    
    std::cout << "Hello, world!" << std::endl;
    return 0;
}


// kate: indent-mode cstyle; space-indent on; indent-width 4; replace-tabs on; 
