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


#include "box.h"

bool Box::contains(const Vector& point) const
{

}

real Box::minimumSize() const
{

}

void Box::tryAbsorb(Particle& particle, real lenght)
{
    Obstacle::tryAbsorb(particle, lenght);
}


void Box::setTopLeft(const Vector& topLeft)
{
    m_topLeft = topLeft;
    updateCoordinateSystem();
}

void Box::setBottomLeft(const Vector& bottomLeft)
{
    m_bottomLeft = bottomLeft;
    updateCoordinateSystem();
}

void Box::setTopRight(const Vector& topRight)
{
    m_topRight = topRight;
    updateCoordinateSystem();
}

Vector Box::topLeft() const
{
    return m_topLeft;
}

Vector Box::bottomLeft() const
{
    return m_bottomLeft;
}

Vector Box::topRight() const
{
    return m_topRight;
}

void Box::updateCoordinateSystem()
{
    m_e1 = m_topLeft-m_bottomLeft;
    m_e2 = m_topLeft-m_topRight;

    // I need to calculate m_p before the vectors are normalized.
    m_p = -1*Vector::dot(Vector::cross(m_e1, m_e2), m_topLeft);

//     m_e1.normalize();
//     m_e2.normalize();
    m_en = Vector::cross(m_e1, m_e2);
    m_en.normalize();

//     std::cout << "-- Coordinate system --" << std::endl;
//     std::cout << "Normal = "; m_en.dump();
//     std::cout << "e1 = "; m_e1.dump();
//     std::cout << "e2 = "; m_e2.dump();
//     std::cout << "p = " << m_p << std::endl;
//     std::cout << "e1 x e2 = "; Vector::cross(m_e1, m_e2).dump();
//     std::cout << "m_topLeft = "; m_topLeft.dump();

}

// kate: indent-mode cstyle; space-indent on; indent-width 0; 
