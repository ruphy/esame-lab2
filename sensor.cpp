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
    updateCoordinateSystem();
}

void Sensor::setBottomLeft(const Vector& bottomLeft)
{
    m_bottomLeft = bottomLeft;
    updateCoordinateSystem();
}

void Sensor::setTopRight(const Vector& topRight)
{
    m_topRight = topRight;
    updateCoordinateSystem();
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

    m_e1.normalize();
    m_e2.normalize();
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
    real dist = Vector::dot(m_en, pos) + m_p;
    // Ajust the position so that it's exactly on the plane
    Vector newPos = pos - m_en*dist;
    // Calculate the vector from the "origin" of the plane
    Vector proj = m_topLeft - newPos;
    
    
}

real Sensor::minimumSize() const
{
    // Fake a thickness of pixelSize: assume that all pixels are actually
    // cubical and the particle is revealed when it ends up in there.
    return m_pixelSize;
}

bool Sensor::contains(const Vector& point) const
{
    // The point is contained if the distance between the plane that
    // contains the sensor and the point is less than the thik
    if (abs(Vector::dot(m_en, point) + m_p) > minimumSize()) {
        return false;
    } else {
        return true;
    }
}



// kate: indent-mode cstyle; space-indent on; indent-width 4; replace-tabs on; 
