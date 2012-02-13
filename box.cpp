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

Box::Box()
{
    m_minimumSize = 0;
}

void Box::init()
{
    Obstacle::init();
    updateCoordinateSystem();
}

bool Box::contains(const Vector& point) const
{
    // The point is in this box means evaluating those three distances.
    // For how the axes are oriented, if the point is in the box
    // the first one should be a non positive number, the other two
    // should be non negative.
    real t_dist = -1*getPointDistance(m_en, point);
    real h_dist = getPointDistance(m_e1, point);
    real w_dist = getPointDistance(m_e2, point);

    // Note: we multiplied t_dist by -1 to allow for a more consistent method.
    if (t_dist < 0 or h_dist < 0 or w_dist < 0) {
        return false;
    }

    if (t_dist > thickness() or h_dist > m_e1.abs() or w_dist > m_e2.abs()) {
//         std::cout << "Too far away from this box: " << dist << std::endl;
        return false;
    } else {
//         std::cout << "Point is inside the box. Distance: " << dist << std::endl;
        return true;
    }
}

real Box::getPointDistance(const Vector &normal, const Vector& point) const
{
    real p = -1*Vector::dot(normal.normalized(), m_topLeft);

    return Vector::dot(normal.normalized(), point) + p; // TODO update coordinate system if needed.
}

real Box::minimumSize() const
{
    return m_minimumSize;
}

void Box::setThickness(real thickness)
{
    m_thickness = thickness;
//     updateCoordinateSystem();
}

real Box::thickness() const
{
    return m_thickness;
}

void Box::tryAbsorb(Particle& particle, real lenght)
{
    Obstacle::tryAbsorb(particle, lenght);
}

void Box::setTopLeft(const Vector& topLeft)
{
    m_topLeft = topLeft;
//     updateCoordinateSystem();
}

void Box::setBottomLeft(const Vector& bottomLeft)
{
    m_bottomLeft = bottomLeft;
//     updateCoordinateSystem();
}

void Box::setTopRight(const Vector& topRight)
{
    m_topRight = topRight;
//     updateCoordinateSystem();
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
    m_e1 = m_bottomLeft-m_topLeft;
    m_e2 = m_topRight-m_topLeft;
    m_en = Vector::cross(m_e1, m_e2).normalized();

    std::cout << std::endl;
    std::cout << "-- Coordinate system --" << std::endl;
    std::cout << "m_topLeft = "; m_topLeft.dump();
    std::cout << "e1 = "; m_e1.dump();
    std::cout << "e2 = "; m_e2.dump();
    std::cout << "e1 x e2 = "; Vector::cross(m_e1, m_e2).dump();
    std::cout << "Normal (normalized) = "; m_en.dump();
    std::cout << "thickness = " << m_thickness << std::endl;
    std::cout << "-- --" << std::endl;
    std::cout << std::endl;

    if(m_e1.abs() > m_e2.abs()) {
        if (m_e2.abs() > m_thickness) {
            m_minimumSize = m_thickness;
        } else {
            m_minimumSize = m_e2.abs();
        }
    } else {
        if (m_e1.abs() > m_thickness) {
            m_minimumSize = m_thickness;
        } else {
            m_minimumSize = m_e1.abs();
        }
    }
}

// kate: indent-mode cstyle; space-indent on; indent-width 0; indent-width 4;
