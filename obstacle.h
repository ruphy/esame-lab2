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


#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "vector.h"
#include <boost/shared_ptr.hpp>

/**
 * This class implements an abstract obstacle, which can absorb a given particle
 * with a reverse exponential probability: exp(-ml), where m is the absorbing coefficient,
 * and l is the lenght of the path inside the object.
 */

class Obstacle
{
public:
    typedef boost::shared_ptr<Obstacle> Ptr;
    Obstacle();

    /**
     * Returns the lenght of the minimum segment intersecting this object
     */
    virtual real minimumSize() const = 0;

protected:
    /**
     * Returns true if the given point is inside this obstacle
     */
    virtual bool isInside(const Vector& point) const = 0;
};


#endif // OBSTACLE_H
// kate: indent-mode cstyle; space-indent on; indent-width 4; replace-tabs on; 
