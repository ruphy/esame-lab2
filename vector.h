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


#ifndef VECTOR_H
#define VECTOR_H

// #include <boost/rational.hpp>

typedef long long int integer;
typedef long double real;

class Vector
{

public:
    Vector();
    Vector(real x, real y, real z);

    Vector(const Vector& other);
    
    virtual ~Vector();
    virtual Vector& operator=(const Vector& other);
    virtual bool operator==(const Vector& other) const;
    
    // Standard operations
    virtual Vector operator+(const Vector& other) const;
    virtual Vector operator-(const Vector& other) const;
    virtual Vector operator*(real scalar) const;
    
    real abs();
    Vector normalize();
    
    real x() const {return m_x;};
    real y() const {return m_x;};
    real z() const {return m_x;};
    
    void setX(real x) {m_x = x;};
    void setY(real y) {m_y = y;};
    void setZ(real z) {m_z = z;};
    
    static Vector cross(const Vector &a, const Vector& b);
    static real dot(const Vector &a, const Vector& b);
    
    
    // debug feature
    void dump() const;
    
private:
    real m_x, m_y, m_z;

};

#endif // VECTOR_H
// kate: indent-mode cstyle; space-indent on; indent-width 4; replace-tabs on; 
