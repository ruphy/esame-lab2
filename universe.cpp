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

#define foreach BOOST_FOREACH

#include "universe.h"

#include "generator.h"
#include "obstacle.h"
#include "sensor.h"
#include "particle.h"

#include <iostream>
#include <time.h>

#include <boost/foreach.hpp>

Universe::Universe()
{
    reset();
    m_deltat = 0;
}

Universe::~Universe()
{
    delete m_entropyGenerator;
}

void Universe::init()
{
    // Determine the smallest deltat

    real smallestWidth = m_obstacles.front()->minimumSize();
    real fastestSpeed = 0.0;

    foreach(const Generator::Ptr generator, m_generators) {
        if (generator->particlesSpeed() > fastestSpeed) {
            fastestSpeed = generator->particlesSpeed();
        }
    }

    foreach(const Obstacle::Ptr obstacle, m_obstacles) {
        if (obstacle->minimumSize() < smallestWidth) {
            smallestWidth = obstacle->minimumSize();
        }
    }

    m_deltat = smallestWidth / fastestSpeed;
    m_deltat *= 0.9; // make it a wee little bit smaller
    
    // TODO: kill all particles that travel past the last sensor.
}

void Universe::reset()
{
//     m_obstacles.clear();
//     m_particles.clear();
//     m_generators.clear();
    m_entropyGenerator = new boost::random::mt19937(time(0));
    m_stepCount = 0;
    m_deltat = 0;
}


void Universe::nextBatch()
{
    if (m_generators.empty()) {
        std::cout << "No generators found. Ending simulation" << std::endl;
        return;
    }

    if (m_stepCount == 0 or m_deltat == 0) {
        init();
    }

    // TODO Try to use pointers here and see if it performs better.
    foreach(const Generator::Ptr generator, m_generators) {
        // Add newly generated particles to our list
        Particle::List newList = generator->generateNewBatch();

//         std::cout << "ROW  " << std::endl;
//         newList.front().speed().dump();
        
        if(!newList.empty()) {
            m_particles.splice(m_particles.end(), newList);
        }
    }

    while (!m_particles.empty()) {

        // HACK TERMINATE FOR NOW
        if (m_stepCount > 4) {
//             reset();
            return;
        }
        m_stepCount++;
        for(Particle::List::iterator it = m_particles.begin(); it != m_particles.end(); ++it) {

//             Particle p = *it;
//             printf("%p", it);
            // (*it) is the current particle
            if ((*it).alive()) {
                moveParticle(*it);
            }

            if(!(*it).alive()) {
                std::cout << "Deleting a particle" << std::endl;
                it = m_particles.erase(it);
            }
        }
    }
}

void Universe::moveParticle(Particle& particle)
{
//             p.move(m_deltat);
//     particle.speed().dump();
//     std::cout << "move particle with above speed of this deltax" << std::endl;
    Vector deltax = particle.speed()*m_deltat;
//     deltax.dump();
    
    particle.move(m_deltat);
    Vector newPos = particle.position();
    
    foreach(const Obstacle::Ptr obstacle, m_obstacles) {
        if (obstacle->contains(newPos)) {
            obstacle->tryAbsorb(particle, deltax.abs());
        }
    }
}

void Universe::addGenerator(Generator::Ptr generator)
{
    generator->setEntropyGenerator(m_entropyGenerator);
    m_generators.push_back(generator);
}

void Universe::addObstacle(Obstacle::Ptr obstacle)
{
    m_obstacles.push_back(obstacle);
}

void Universe::addSensor(Sensor::Ptr sensor)
{
    m_obstacles.push_back(sensor);
    // TODO also keep in mind that this is a sensor, for killing particles purposes
}

// kate: indent-mode cstyle; space-indent on; indent-width 4; replace-tabs on;  replace-tabs on;
