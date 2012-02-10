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

#include <boost/random/uniform_real_distribution.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <time.h>

#include "generator.h"

Generator::Generator()
{

//     m_gen = new boost::random::mt19937(time(0));
//     m_gen.seed(time(0)); //make me a global object?
    m_gen = 0;
    m_genRate = 0;
}

Generator::~Generator()
{
}

void Generator::setParticlesSpeed(real speed)
{
    m_particlesSpeed = speed;
}

void Generator::setPosition(const Vector& position)
{
//     position.dump();
    m_position = position;
}

void Generator::setGenerationRate(real genRate)
{
    m_genRate = genRate;
}

void Generator::setEntropyGenerator(boost::random::mt19937* gen)
{
    m_gen = gen;
}

Particle::List Generator::generateNewBatch()
{
    if (!m_gen) {
        std::cerr << "I don't have an entropy generator set! This will crash." << std::endl;
    }

    Particle::List list;
    
    boost::random::uniform_real_distribution<real> dist(-1.0, 1.0);
    
    for (int i = 0; i <= m_genRate; i++) {
        Vector speed(dist(*m_gen), dist(*m_gen), dist(*m_gen));
        
        speed = speed.normalize()*m_particlesSpeed;
        speed.dump();
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
