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


#ifndef BOX_H
#define BOX_H

#include "obstacle.h"


class Box : public Obstacle
{

public:
    virtual bool contains(const Vector& point) const;
    virtual real minimumSize() const;
    virtual void tryAbsorb(Particle& particle, real lenght);


    Vector topLeft() const;
    Vector topRight() const;
    Vector bottomLeft() const;

    void setTopLeft(const Vector &topLeft);
    void setBottomLeft(const Vector &bottomLeft);
    void setTopRight(const Vector &topRight);

protected:
    void updateCoordinateSystem();


    Vector m_topLeft;
    Vector m_topRight;
    Vector m_bottomLeft;
    
    // Orthonormal destrorse coordinate system:
    // m_e1 x m_e2 = m_en
    // m_e2 x m_en = m_e1
    //
    // m_e1 and m_e2 are on the plane
    // m_en is normal to the plane
    Vector m_e1;
    Vector m_e2;
    Vector m_en;

    // Plane specification: p = normal dot center
    real m_p;
};

#endif // BOX_H
// kate: indent-mode cstyle; space-indent on; indent-width 0; 
