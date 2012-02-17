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
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition_variable.hpp>

#include "threadpool/threadpool.hpp"
// #include <ThreadWeaver/JobCollection>

Universe::Universe()
{
    reset();
    m_deltat = 0;
    m_boundary = 0;
    m_accuracy = 1;
    m_mutex = new boost::mutex;
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
        std::cout << "Min size: "<< (long double) obstacle->minimumSize() << std::endl;
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

    std::cout << "calculated deltat: " << (long double) m_deltat << std::endl;
}

void Universe::setBatches(int batches)
{
    m_batches = batches;
}

void Universe::run()
{
    if (m_generators.empty()) {
        std::cout << "No generators found. Ending simulation" << std::endl;
        return;
    }

    if (m_stepCount == 0 or m_deltat == 0) {
        init();
    }

    m_remainingBatches = m_batches;

    unsigned cpus = boost::thread::hardware_concurrency() + 1; // Maximum optimization!
    if (cpus == 0) {
        cpus = 1; // run at least one thread.
    }

    std::cout << "Running with " << cpus << " threads." << std::endl;
    
    boost::threadpool::pool pool(cpus);
    
    while (m_remainingBatches) {
        pool.schedule(boost::bind(&Universe::createNewJob, this, m_batches-m_remainingBatches+1));
        m_remainingBatches--;
    }

//     pool.resize(2);
    pool.wait();
        
}

void Universe::createNewJob(int nBatch)
{
    Particle::List list;
    // TODO Try to use pointers here and see if it performs better.
    foreach(const Generator::Ptr generator, m_generators) {

        boost::mutex::scoped_lock lock(*m_mutex);
        // Add newly generated particles to our list
         Particle::List newList = generator->generateNewBatch();

        if(!newList.empty()) {
            list.splice(list.end(), newList);
        }
    }

    UniverseBatch b;// = new UniverseBatch;
    b.setObstacleList(m_obstacles);
    b.setParticleList(list);
    b.setBoundary(m_boundary);
    b.setDeltaT(m_deltat);
    b.setBatchNumber(nBatch);
    b.run();
}

void Universe::reset()
{
    m_entropyGenerator = new boost::random::mt19937(time(0) + getpid());
    m_stepCount = 0;
    m_deltat = 0;
}

void Universe::addGenerator(Generator::Ptr generator)
{
    generator->setEntropyGenerator(m_entropyGenerator);
    m_generators.push_back(generator);
}

void Universe::addObject(Obstacle::Ptr object)
{
    m_obstacles.push_back(object);
//     object->setEntropyGenerator();
}

void Universe::addSensor(Sensor::Ptr sensor)
{
    m_obstacles.push_back(sensor);
    // TODO also keep in mind that this is a sensor, for killing particles purposes
}

// kate: indent-mode cstyle; space-indent on; indent-width 4; replace-tabs on;  replace-tabs on;
