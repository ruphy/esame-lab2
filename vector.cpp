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


#include "vector.h"

Vector::Vector()
{
    m_x = m_y = m_z = 0;
}

Vector::Vector(real x, real y, real z)
{
    m_x = x;
    m_y = y;
    m_z = z;
}

Vector::Vector(const Vector& other)
{
    m_x = other.m_x;
    m_y = other.m_y;
    m_z = other.m_z;
}

Vector::~Vector()
{

}

Vector& Vector::operator=(const Vector & other)
{
    m_x = other.m_x;
    m_y = other.m_y;
    m_z = other.m_z;
    return *this;
}

bool Vector::operator==(const Vector& other) const
{
    return ( (m_x == other.m_x)
            and (m_y == other.m_y)
            and (m_z == other.m_z));
}

Vector Vector::operator*(real scalar) const
{
    return Vector(m_x*scalar, m_y*scalar, m_z*scalar);
}

Vector Vector::operator+(const Vector& other) const
{
    return Vector(m_x+other.m_x, m_y+other.m_y, m_z+other.m_z);
}

Vector Vector::operator-(const Vector& other) const
{
    return Vector(m_x-other.m_x, m_y-other.m_y, m_z-other.m_z);
}

Vector Vector::vec(const Vector& other) const
{

}

real Vector::scal(const Vector& other) const
{
    return m_x*other.m_x + m_y*other.m_y + m_z*other.m_z;
}


// kate: indent-mode cstyle; space-indent on; indent-width 4; replace-tabs on; 
