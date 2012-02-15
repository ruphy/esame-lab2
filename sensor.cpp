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
    counter = 0;
}

Sensor::~Sensor()
{}

void Sensor::setPixelColumns(int columns)
{
    m_pixelColumns = columns;
}

void Sensor::setPixelRows(int rows)
{
    m_pixelRows = rows;
}

void Sensor::init()
{
    Box::init();

    m_pixelHeight = (m_e1.abs()/m_pixelRows);
    m_pixelWidth = (m_e2.abs()/m_pixelColumns);
    // Fake a thickness
    (m_pixelHeight < m_pixelWidth) ? setThickness(m_pixelHeight) : setThickness(m_pixelWidth);

    std::cout << "Pixel Height: " << m_pixelHeight << std::endl;
    std::cout << "Pixel Width: " << m_pixelWidth << std::endl;

    std::cout << "Total computed rows: " << m_pixelRows << std::endl;
    std::cout << "Total computed cols: " << m_pixelColumns << std::endl;

    Box::updateCoordinateSystem(); // We've updated our thickness

    std::vector<integer> tempVector;
    tempVector.resize(m_pixelColumns, 0);
    m_pixelGrid.resize(m_pixelRows, tempVector);
}



void Sensor::particleDetected(int row, int column)
{
//     std::cout << "Particle detected at " << row << " x " << column << std::endl;
    m_pixelGrid.at(row).at(column) += 1;
    counter++;
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
    std::cout << "Total particles seen: " << counter << std::endl;
}

void Sensor::tryAbsorb(Particle& particle, real lenght) // FIXME CONSTIFY ME
{
//     std::cout << std::endl;
//     std::cout << std::endl;
//     std::cout << "Sensor HIT!" << std::endl;
//     std::cout << "Got a particle with posistion: ";
//     particle.position().dump();
//     std::cout << "It has a distance of: " << getPointDistance(pos);
    
    // This particle will stop here.
    absorb(particle);

    Vector pos = particle.position();

    // Ajust the position so that it's exactly on the sensor plane
    Vector newPos = pos - m_en*getPointDistance(m_en, pos);
    // Calculate the vector from the "origin" of the plane
    Vector proj = newPos - m_topLeft;

    // Project the lenght of this last vector on the two plane axes
    real e1_len = Vector::dot(proj, m_e1)/m_e1.abs();
    real e2_len = Vector::dot(proj, m_e2)/m_e2.abs();

//     std::cout << "Trying to assign a particle to a pixel:" << std::endl;
//     std::cout << "e1_len = " << e1_len << std::endl;
//     std::cout << "e2_len = " << e2_len << std::endl;

    int row = abs(floor(e1_len/m_pixelHeight));
    int column = abs(floor(e2_len/m_pixelWidth));
    particleDetected(row, column);

//     std::cout << std::endl;
//     std::cout << std::endl;
}

bool Sensor::contains(const Vector& point) const
{
    return Box::contains(point);
}

std::vector< std::vector< integer > > Sensor::data() const
{
    return m_pixelGrid;
}


// kate: indent-mode cstyle; space-indent on; indent-width 4; replace-tabs on; 
