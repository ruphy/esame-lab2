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

#include <boost/random/normal_distribution.hpp>
#include <boost/random/uniform_real_distribution.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/math/constants/constants.hpp>

#include <time.h>

#include <boost/thread/mutex.hpp>

#include "generator.h"

Generator::Generator()
 : m_fireRate(0),
   m_gen(new boost::random::mt19937(time(0) + getpid()))
{
}

void Generator::setParticlesSpeed(real speed)
{
    m_particlesSpeed = speed;
}

void Generator::setPosition(const Vector& position)
{
    m_position = position;
}

Vector Generator::position() const
{
    return m_position;
}

void Generator::setFireRate(real genRate)
{
    m_fireRate = genRate;
}

real Generator::fireRate() const
{
    return m_fireRate;
}

Particle::List Generator::generateNewBatch()
{
    if (!m_gen) {
        std::cerr << "I don't have an entropy generator set! This will crash." << std::endl;
    }

    Particle::List list;
    boost::random::uniform_real_distribution<real> dist(-1, 1);

    for (int i = 1; i <= m_fireRate; i++) {
        Vector direction;
        do {
            direction.setX(2 * dist(*m_gen) - 1),
            direction.setY(2 * dist(*m_gen) - 1),
            direction.setZ(2 * dist(*m_gen) - 1);
        } while(direction.abs() > 1);

        Vector speed = direction.normalized();

        Particle p;
        p.setSource(m_position);
        p.setSpeed(speed);
        
        list.push_back(p);
    }
    
    return list;
}


real Generator::particlesSpeed()
{
    return m_particlesSpeed;
}

// kate: indent-mode cstyle; space-indent on; indent-width 4; replace-tabs on; 
