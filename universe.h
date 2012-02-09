/*
    Copyright (C) 2012  Riccardo Iaconelli <riccardo@kde.org>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#ifndef UNIVERSE_H
#define UNIVERSE_H

#include "generator.h"
#include "obstacle.h"
#include "sensor.h"

/**
 * This class will take care of automatically deleting any objects that you add to it,
 * thus you do not need to clean up the memory if you don't want to.
 * To do a simulation, just add generators, obstacles and sensors, and you're done.
 */

class Universe
{
public:
    Universe();
    virtual ~Universe();

    void addGenerator(Generator::Ptr generator);
    void addObstacle(Obstacle::Ptr obstacle);
    void addSensor(Sensor::Ptr sensor);
    
    void nextStep();
    
private:
    
};

#endif // UNIVERSE_H
// kate: indent-mode cstyle; space-indent on; indent-width 4; replace-tabs on; 
