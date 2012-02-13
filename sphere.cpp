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


#include "sphere.h"
#include "vector.h"

Sphere::Sphere(std::string name)
 : Obstacle(name)
{
    m_accuracy = 0.01;
}

real Sphere::accuracy() const
{
    return m_accuracy;
}

void Sphere::setAccuracy(real accuracy)
{
    m_accuracy = accuracy;
}

bool Sphere::contains(const Vector& point) const
{
    Vector t_point = point - m_center;
    if (t_point.abs() < m_radius) {
        return true;
    } else {
        return false;
    }
}

real Sphere::minimumSize() const
{
    return m_accuracy*m_radius;
}

void Sphere::setCenter(const Vector& center)
{
    m_center = center;
}

void Sphere::setRadius(real radius)
{
    m_radius = radius;
}


// kate: indent-mode cstyle; space-indent on; indent-width 0; 
