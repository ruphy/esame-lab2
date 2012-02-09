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


#ifndef SENSOR_H
#define SENSOR_H

#include "obstacle.h"

/**
 * A sensor is a square 2d surface, with a given size,
 * normal (for orientation) and center.
 */

class Sensor : public Obstacle
{
public:
    typedef boost::shared_ptr<Sensor> Ptr;
    
    Sensor();
    virtual ~Sensor();
    
    Vector normal();
    Vector center();
    real size();
};

#endif // SENSOR_H
