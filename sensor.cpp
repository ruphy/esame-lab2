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

void Sensor::setTopLeft(const Vector& topLeft)
{
    m_topLeft = topLeft;
}

void Sensor::setBottomLeft(const Vector& bottomLeft)
{

}

void Sensor::setTopRight(const Vector& topRight)
{

}

Vector Sensor::topLeft() const
{
    return m_topLeft;
}

Vector Sensor::bottomLeft() const
{
    return m_bottomLeft;
}

Vector Sensor::topRight() const
{
    return m_topRight;
}

void Sensor::updateCoordinateSystem()
{
    m_e1 = m_topLeft-m_bottomLeft;
    m_e2 = m_topLeft-m_topRight;
    m_en = Vector::cross(m_e1, m_e2);
    
    m_p = -1*Vector::dot(m_en, m_topLeft);
}

void Sensor::setPixelSize(real size)
{
    m_pixelSize = size;
}


void Sensor::tryAbsorb(Particle& particle, real lenght)
{
    particle.absorb();
    Vector pos = particle.position();
    real distance = Vector::dot(m_en, pos) + m_p;
}


real Sensor::minimumSize() const
{
    // Fake a width of pixelSize: assume that all pixels are cubical
    // and the particle is revealed when it ends up there
    return m_pixelSize;
}

bool Sensor::contains(const Vector& point) const
{
    if (abs(Vector::dot(m_en, point) + m_p) > minimumSize()) {
        return false;
    } else {
        return true;
    }
}



// kate: indent-mode cstyle; space-indent on; indent-width 4; replace-tabs on; 
