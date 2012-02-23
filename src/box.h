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

/**
 * A thick box.
 * To use it you have to specify three points (top and bottom left, top right),
 * and set the desired thickness.
 *
 * The thickness will all go "behind" the plane where the three points are.
 * Mathematically:
 *  e1 = bottomLeft - topLeft;
 *  e2 = topRight - topLeft;
 * The thickness will be in the direction of e2 x e1.
 */

class Box : public Obstacle
{

public:
    Box();

    virtual bool contains(const Vector& point) const;

    /**
     * This function actively checks what side is smaller, and tries to
     * cache that result.
     */
    virtual real minimumSize() const;
    virtual void tryAbsorb(Particle& particle, real lenght);

    void setTopLeft(const Vector &topLeft);
    Vector topLeft() const;

    void setBottomLeft(const Vector &bottomLeft);
    Vector bottomLeft() const;

    void setTopRight(const Vector &topRight);
    Vector topRight() const;

protected:
    real thickness() const;
    void setThickness(real thickness);

    virtual void updateCoordinateSystem();
    virtual void init();

    /**
     * Returns the distance between the plane passing through the point "topLeft"
     * (with normal "normal"), and the point "point".
     */
    real getPointDistance(const Vector &normal, const Vector &point) const;

    Vector m_topLeft;
    Vector m_topRight;
    Vector m_bottomLeft;

    /**
     * m_e1 = m_bottomLeft-m_topLeft.
     *
     * Part of the orthogonal coordinate system of the box.
     */
    Vector m_e1;
    /**
     * m_e2 = m_topRight-m_topLeft.
     *
     * Part of the orthogonal coordinate system of the box.
     */
    Vector m_e2;
    
    /**
     * m_en is automatically calculated and normalized.
     * It is oriented in the direction of the thickness.
     *
     * m_en = Vector::cross(m_e2, m_e1).
     *
     * Part of the orthogonal coordinate system of the box.
     */
    Vector m_en;

private:
    real m_thickness;
    real m_minimumSize;

};

#endif // BOX_H
// kate: indent-mode cstyle; space-indent on; indent-width 0; indent-width 4;
