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

#include "vector.h"
#include "particle.h"

/**
 * A generator is a source of particles. It is a point
 * and generates a number of particles controlled by
 * setGenerationRate at every batch.
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
    real particlesSpeed();

    void setPosition(const Vector &position);

    void setParticlesSpeed(real speed);
    void setGenerationRate(real genRate);

    Particle::List generateNewBatch();
    
private:
    void setEntropyGenerator(boost::random::mt19937 *gen);
    
    real m_particlesSpeed;
    real m_genRate;
    Vector m_position;

    boost::random::mt19937 *m_gen;
    
    friend class Universe;
};

#endif // GENERATOR_H
// kate: indent-mode cstyle; space-indent on; indent-width 4; replace-tabs on; 
