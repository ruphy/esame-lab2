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
    m_boundary = 0;
    m_accuracy = 1;
}

Universe::~Universe()
{
    delete m_entropyGenerator;
}

void Universe::setAccuracy(real accuracy)
{
    m_accuracy = accuracy;
}

real Universe::accuracy() const
{
    return m_accuracy;
}

// TODO: kill all particles that travel past the last sensor:
// try to autodetermine a good enough setting
void Universe::setBoundary(real boundary)
{
    m_boundary = boundary;
}

real Universe::boundary() const
{
    return m_boundary;
}

void Universe::init()
{
    if (m_boundary == 0) {
        std::cout << "Warning: universe boundary is set to 0."
                     "All particles will be killed." << std::endl;
    }
    // Init all the obstacles
    foreach(const Obstacle::Ptr obstacle, m_obstacles) {
        obstacle->init();
        std::cout << "Min size: "<< obstacle->minimumSize() << std::endl;
    }

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
    m_deltat *= m_accuracy; // eventually make it a wee little bit smaller

    std::cout << "calculated deltat: " << m_deltat << std::endl;
}


void Universe::reset()
{
    m_entropyGenerator = new boost::random::mt19937(time(0) + getpid());
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

        if(!newList.empty()) {
            m_particles.splice(m_particles.end(), newList);
        }
    }

    while (!m_particles.empty()) {
        m_stepCount++;
        for(Particle::List::iterator it = m_particles.begin(); it != m_particles.end(); ++it) {
            if ((*it).alive()) {
                moveParticle(*it);
            }

            if(!(*it).alive()) {
//                 std::cout << "Deleting a particle" << std::endl;
                it = m_particles.erase(it);
            }
        }
    }
}

void Universe::moveParticle(Particle& particle)
{
    if (particle.position().abs() > m_boundary) {
        particle.absorb(); // Kill the particle
        return;
    }

    Vector deltax = particle.speed()*m_deltat;

    particle.move(m_deltat);
    Vector newPos = particle.position();

    foreach(const Obstacle::Ptr obstacle, m_obstacles) {
        if (obstacle->contains(newPos)) {
            obstacle->tryAbsorb(particle, deltax.abs());
        }
//         if (!particle.alive()) {
//             break; // Avoid absorbing a particle multiple times? how do you handle colliding objects?
//         }
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
