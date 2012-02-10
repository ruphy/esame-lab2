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

#include "particle.h"

#include "obstacle.h"
#include <math.h>
#include <boost/random/uniform_real_distribution.hpp>

Obstacle::Obstacle()
{
    m_gen = 0;
}

void Obstacle::setAbsorbingCoefficient(real mu)
{
    m_mu = mu;
}

void Obstacle::tryAbsorb(Particle& particle, real lenght)
{
    boost::random::uniform_real_distribution<real> dist(0.0, 1.0);
    real n1 = dist(*m_gen);
    if (n1 > exp(-m_mu*lenght) ) {
        particle.absorb();
    }
}


// kate: indent-mode cstyle; space-indent on; indent-width 4; replace-tabs on; 
