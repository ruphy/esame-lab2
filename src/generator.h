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


#ifndef GENERATOR_H
#define GENERATOR_H

#include <boost/shared_ptr.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/thread/mutex.hpp>

#include "vector.h"
#include "particle.h"

/**
 * A generator is a source of particles. It is a dimensionless
 * point and generates a number of particles controlled by
 * fireRate at every batch.
 */

class Generator
{
public:
    typedef boost::shared_ptr<Generator> Ptr;

    Generator();
    virtual ~Generator() {};

    /**
     * Scalar speed of the generated particles
     */
    void setParticlesSpeed(real speed);
    real particlesSpeed();
    
    void setPosition(const Vector &position);
    Vector position() const;

    void setFireRate(real genRate);
    real fireRate() const;

    Particle::List generateNewBatch();

private:
    real m_particlesSpeed;
    real m_fireRate;
    Vector m_position;

    boost::random::mt19937 *m_gen;
    boost::mutex *m_mutex;
};

#endif // GENERATOR_H
// kate: indent-mode cstyle; space-indent on; indent-width 4; replace-tabs on; 
