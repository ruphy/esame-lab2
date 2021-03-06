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


#ifndef SPHERE_H
#define SPHERE_H

#include "obstacle.h"
#include <boost/shared_ptr.hpp>

class Sphere : public Obstacle
{
public:
    typedef boost::shared_ptr<Sphere> Ptr;

    Sphere();
    virtual ~Sphere();

    virtual bool contains(const Vector& point) const;
    virtual real minimumSize() const;

    void setRadius(real radius);
    real radius() const;

    void setCenter(const Vector& center);
    Vector center() const;

    /**
     * This number controls the sensibility of the simulation.
     *
     * It is used to determine the smallest width of this sphere
     * when a particle passes through it, calculated as radius*sensibility;
     *
     * Accuracy must be a real number smaller or equal to 1 and
     * greater than 0, where 0 means perfect sensibility and 1
     * the worse sensibility (it's mostly a cube).
     *
     * Note: setting sensibility to 0 will probably crash the program.
     *
     * Default value: 0.01.
     */
    void setSensibility(real sensibility);
    real sensibility() const;
    
private:
    Vector m_center;
    real m_radius;
    real m_sensibility;
};

#endif // SPHERE_H
