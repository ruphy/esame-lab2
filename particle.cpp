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

#include <iostream>

#include "particle.h"

Particle::Particle()
 : m_alive(true),
   m_position(Vector(0, 0, 0)),
   m_source(Vector(0, 0, 0))
{}

Particle::~Particle()
{}

Particle::Particle(const Particle& other)
{
    m_speed = other.m_speed;
    m_alive = other.m_alive;
    m_position = other.m_position;
    m_source = other.m_source;
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
    //  We start at the source.
    m_position = m_source;
}

void Particle::setSpeed(const Vector& speed)
{
    m_speed = speed;
}

void Particle::move(real deltat)
{
    m_position = m_position + m_speed*deltat;
}

Vector Particle::position() const
{
    return m_position;
}

// kate: indent-mode cstyle; space-indent on; indent-width 4; replace-tabs on; 
