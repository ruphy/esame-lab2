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


#include "sensor.h"
#include "particle.h"

Sensor::Sensor()
{

}

Sensor::~Sensor()
{

}

void Sensor::setNormal(const Vector& normal)
{
    m_normal = normal;
    m_normal.normalize();
    m_p = -1*Vector::dot(m_normal, m_center);
}

void Sensor::setCenter(const Vector& center)
{
    m_center = center;
    m_p = -1*Vector::dot(m_normal, m_center);
}

void Sensor::setPixelSize(real size)
{
    m_pixelSize = size;
}

Vector Sensor::center() const
{
    return m_center;
}

Vector Sensor::normal() const
{
    return m_normal;
}


void Sensor::tryAbsorb(Particle& particle, real lenght)
{
    particle.absorb();
}


real Sensor::minimumSize() const
{
    // Fake a width of pixelSize: assume that all pixels are cubical
    // and the particle is revealed when it ends up there
    return m_pixelSize;
}

bool Sensor::contains(const Vector& point) const
{
    if (abs(Vector::dot(m_normal, point) + m_p) > minimumSize()) {
        return false;
    } else {
        return true;
    }
}



// kate: indent-mode cstyle; space-indent on; indent-width 4; replace-tabs on; 
