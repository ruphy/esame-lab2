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

Particle::Particle()
{
    m_alive = true;
}

Particle::~Particle()
{

}

bool Particle::alive()
{
    return m_alive;
}

Vector Particle::source() const
{
    return m_source;
}

Vector Particle::speed() const
{
    return m_speed;
}

void Particle::absorb()
{
    m_alive = false;
}

void Particle::setSource(const Vector& source)
{
    m_source = source;
}

void Particle::setSpeed(const Vector& speed)
{
    m_speed = speed;
}

void Particle::move(const Vector& deltax)
{
    m_position = m_position + deltax;
}

Vector Particle::position() const
{
    return m_position;
}

// kate: indent-mode cstyle; space-indent on; indent-width 4; replace-tabs on; 
