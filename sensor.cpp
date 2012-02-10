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
    m_pixelRows = 1;
    m_pixelColumns = 1;
    m_alreadyInitd = false;
}

Sensor::~Sensor()
{}

void Sensor::setPixelColumns(int columns)
{
    m_pixelColumns = columns;
    updateCoordinateSystem();
}

void Sensor::updateCoordinateSystem()
{
    Box::updateCoordinateSystem();
    real size1 = m_e1.abs()/m_pixelRows;
    real size2 = m_e2.abs()/m_pixelColumns;
//     std::cout << "UPDATE" << size2 << "   ";
    (size1 < size2) ? setThickness(size1) : setThickness(size2);
}

void Sensor::setPixelRows(int rows)
{
    m_pixelRows = rows;
    updateCoordinateSystem();
}

void Sensor::init()
{
    if (m_alreadyInitd) {
        return;
    }
    m_alreadyInitd = true;
    
    // Ensure we always have enough pixels
    int rows = floor((m_topLeft-m_bottomLeft).abs()) + 1;
    int columns = floor((m_topLeft-m_topRight).abs()) + 1;

    std::cout << "Total computed rows: " << rows << std::endl;
    std::cout << "Total computed cols: " << columns << std::endl;

    std::vector<integer> tempVector;
    tempVector.resize(columns, 0);
    m_pixelGrid.resize(rows, tempVector);
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

void Sensor::tryAbsorb(Particle& particle, real lenght) // FIXME CONSTIFY ME
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
    absorb(particle);

    Vector pos = particle.position();

    // Ajust the position so that it's exactly on the sensor plane
    Vector newPos = pos - m_en*getPointDistance(pos);
    // Calculate the vector from the "origin" of the plane
    Vector proj = newPos - m_topLeft;

    proj.dump();
    m_e1.dump();
    m_e2.dump();
    Vector e1_n = m_e1;
    Vector e2_n = m_e2;
//     e1_n.normalize();
//     real totPixels = m_e1.abs()/m_pixelSize;
//     e2_n.normalize();
    
    // Project the lenght of this last vector on the two plane axes
    real e1_len = fabs(Vector::dot(proj, e1_n))/e1_n.abs();
    real e2_len = fabs(Vector::dot(proj, e2_n))/e2_n.abs();

    std::cout << "Trying to assign a particle to a pixel:" << std::endl;
    std::cout << "e1_len = " << e1_len << std::endl;
    std::cout << "e2_len = " << e2_len << std::endl;

    real pixelHeight = (m_e1.abs()/m_pixelRows);
    real pixelWidth = (m_e2.abs()/m_pixelColumns);
    int row = floor(e1_len/pixelHeight);
    int column = floor(e2_len/pixelWidth);
    particleDetected(row, column);

    std::cout << std::endl;
    std::cout << std::endl;
}

bool Sensor::contains(const Vector& point) const
{
    return Box::contains(point);
}



// kate: indent-mode cstyle; space-indent on; indent-width 4; replace-tabs on; 
