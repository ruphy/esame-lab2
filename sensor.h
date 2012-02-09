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

    Vector normal() const;
    Vector center() const;
    real size() const;

    void setNormal(const Vector &normal);
    void setCenter(const Vector &center);
    void setPixelSize(real size);

    virtual bool contains(const Vector& point) const;
    virtual real minimumSize() const;

    virtual void tryAbsorb(Particle& particle, real lenght);

private:
    real m_pixelSize;
    Vector m_normal;
    Vector m_center;

    // Plane specification: p = normal dot center
    real m_p;
};

#endif // SENSOR_H
// kate: indent-mode cstyle; space-indent on; indent-width 4; replace-tabs on; 
