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


#include "universe.h"

#include <iostream>
#include <boost/foreach.hpp>

Universe::Universe()
{

}

Universe::~Universe()
{

}

void Universe::init()
{
    // Determine the smallest deltat
    
    real smallestWidth = m_obstacles.front()->minimumSize();
    real fastestParticles = 0;
    
    BOOST_FOREACH(const Generator::Ptr generator, m_generators) {
        if (generator->particlesSpeed() > fastestParticles) {
            fastestParticles = generator->particlesSpeed();
        }
    }
    
    BOOST_FOREACH(const Obstacle::Ptr obstacle, m_obstacles) {
        if (obstacle->minimumSize() < smallestWidth) {
            smallestWidth = obstacle->minimumSize();
        }
    }
}

void Universe::reset()
{
    m_stepCount = 0;
    deltat = 0;
}


void Universe::nextBatch()
{
    if (m_generators.empty()) {
        std::cout << "No generators found. Ending simulation" << std::endl;
        return;
    }
    
    if (m_stepCount == 0) {
        init();
    }
    
}



// kate: indent-mode cstyle; space-indent on; indent-width 4; replace-tabs on; 
