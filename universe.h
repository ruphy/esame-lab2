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

#include <list>

#include <boost/random/mersenne_twister.hpp>

#include "generator.h"
#include "obstacle.h"
#include "sensor.h"
#include "particle.h"
#include "sphere.h"
#include "universebatch.h"


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
    void addSensor(Sensor::Ptr sensor);
    void addObject(Obstacle::Ptr object);

    void setBatches(int batches);
    void run();
    void do_run();
    
    void nextBatch();
    void reset();

    /**
     * Universe will kill the particle if position.abs() > boundary
     */
    void setBoundary(real boundary);
    real boundary() const;

    /**
     * This number controls the accuracy of the simulation.
     * accuracy must be a real number smaller or equal to 1 and
     * greater than 0, where 0 means perfect accuracy and 1
     * the smallest accuracy (which is still good enough for
     * most situations).
     *
     * Note: setting accuracy to 0 will result in a never-ending
     * simulation.
     *
     * Default value: 1.
     */
    void setAccuracy(real accuracy);
    real accuracy() const;
    
private:
    void init();
    void moveParticle(Particle& particle);

    void createNewJob();
    
    int m_stepCount;
    int m_batches;
    int m_remainingBatches;
    real m_deltat;

    std::list<UniverseBatch *> m_pool;
    
    std::list<Generator::Ptr> m_generators;
    std::list<Obstacle::Ptr> m_obstacles;

    real m_boundary;
    real m_accuracy;

    boost::random::mt19937 *m_entropyGenerator;
    
    Particle::List m_particles;
};


#endif // UNIVERSE_H
// kate: indent-mode cstyle; space-indent on; indent-width 4; replace-tabs on; 
