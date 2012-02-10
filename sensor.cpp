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

#define foreach BOOST_FOREACH

#include "particle.h"

#include <math.h>
#include <stdexcept>

#include <boost/foreach.hpp>

#include "sensor.h"

Sensor::Sensor()
{
    m_alreadyInitd = false;
}

Sensor::~Sensor()
{

}

void Sensor::setTopLeft(const Vector& topLeft)
{
    m_topLeft = topLeft;
    updateCoordinateSystem();
}

void Sensor::setBottomLeft(const Vector& bottomLeft)
{
    m_bottomLeft = bottomLeft;
    updateCoordinateSystem();
}

void Sensor::setTopRight(const Vector& topRight)
{
    m_topRight = topRight;
    updateCoordinateSystem();
}

Vector Sensor::topLeft() const
{
    return m_topLeft;
}

Vector Sensor::bottomLeft() const
{
    return m_bottomLeft;
}

Vector Sensor::topRight() const
{
    return m_topRight;
}

void Sensor::setPixelSize(real size)
{
    m_pixelSize = size;
    updateCoordinateSystem();
}

void Sensor::init()
{
    if (m_alreadyInitd) {
        return;
    }
    m_alreadyInitd = true;
    
    // Ensure we always have enough pixels
    int rows = floor((m_topLeft-m_bottomLeft).abs()) + 2;
    int columns = floor((m_topLeft-m_topRight).abs()) + 2;

    std::cout << "Total computed rows: " << rows << std::endl;
    std::cout << "Total computed cols: " << columns << std::endl;

    std::vector<integer> tempVector;
    tempVector.resize(columns, 0);
    m_pixelGrid.resize(rows, tempVector);
}

void Sensor::updateCoordinateSystem()
{
    m_e1 = m_topLeft-m_bottomLeft;
    m_e2 = m_topLeft-m_topRight;

    m_e1.normalize();
    m_e2.normalize();
    m_en = Vector::cross(m_e1, m_e2);

    m_p = -1*Vector::dot(m_en, m_topLeft);
}

void Sensor::particleDetected(int row, int column)
{
    std::cout << "Particle detected at " << row << " x " << column << std::endl;
    m_pixelGrid.at(row).at(column) += 1;
}

void Sensor::dump() const
{
    foreach(std::vector<integer> v, m_pixelGrid) {
        std::cout << "Row: ";
        foreach(integer i, v) {
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }
}

void Sensor::tryAbsorb(Particle& particle, real lenght)
{
    if(!m_alreadyInitd) {
        init();
    }
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "Sensor HIT!" << std::endl;
    
    std::cout << "Got a particle with posistion: ";

    particle.position().dump();
    // This particle will stop here.
    particle.absorb();

    Vector pos = particle.position();
    real dist = Vector::dot(m_en, pos) + m_p;
    

    // Ajust the position so that it's exactly on the plane
    Vector newPos = pos - m_en*dist;
    // Calculate the vector from the "origin" of the plane
    Vector proj = m_topLeft - newPos;

    std::cout << "Projected vector:" << std::endl;
    proj.dump();
    std::cout << Vector::dot(proj, m_e1) << std::endl;
    
    // Project the lenght of this last vector on the two plane axes
    real e1_len = fabs(Vector::dot(proj, m_e1))/proj.abs();
    real e2_len = fabs(Vector::dot(proj, m_e2))/proj.abs();

    std::cout << "Trying to assign a particle to a pixel:" << std::endl;
    std::cout << "e1_len" << e1_len << std::endl;
    std::cout << "e2_len" << e2_len << std::endl;

    int row = floor(e1_len/m_pixelSize);
    int column = floor(e2_len/m_pixelSize);
    particleDetected(row, column);

    std::cout << std::endl;
    std::cout << std::endl;
}

real Sensor::minimumSize() const
{
    // Fake a thickness of pixelSize: assume that all pixels are actually
    // cubical and the particle is revealed when it ends up in there.
    return m_pixelSize;
}

bool Sensor::contains(const Vector& point) const
{
    // The point is contained if the distance between the plane that
    // contains the sensor and the point is less than the thik
    if (abs(Vector::dot(m_en, point) + m_p) > minimumSize()) {
        return false;
    } else {
        return true;
    }
}



// kate: indent-mode cstyle; space-indent on; indent-width 4; replace-tabs on; 
