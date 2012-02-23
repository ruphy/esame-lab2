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

#include "sensor.h"

#include <boost/foreach.hpp>
#define foreach BOOST_FOREACH

#include "particle.h"

Sensor::Sensor()
 : m_pixelRows(1),
   m_pixelColumns(1),
   m_totalCounter(0)
{}

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

//     std::cout << "Pixel Height: " << (long double) m_pixelHeight << std::endl;
//     std::cout << "Pixel Width: " << (long double) m_pixelWidth << std::endl;

//     std::cout << "Total computed rows: " << m_pixelRows << std::endl;
//     std::cout << "Total computed cols: " << m_pixelColumns << std::endl;

    Box::updateCoordinateSystem(); // We've updated our thickness

    std::vector<integer> tempVector;
    tempVector.resize(m_pixelColumns, 0);
    m_pixelGrid.resize(m_pixelRows, tempVector);
}

void Sensor::particleDetected(int row, int column)
{
    m_pixelGrid.at(row).at(column) += 1;
    m_totalCounter++;
}

void Sensor::dump() const
{
    foreach(std::vector<integer> v, m_pixelGrid) {
        foreach(integer i, v) {
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "Total particles seen: " << m_totalCounter << std::endl;
}

void Sensor::tryAbsorb(Particle& particle, real lenght) // FIXME CONSTIFY ME
{
    // This particle will stop here.
    absorb(particle);

    Vector pos = particle.position();
    Vector speed = particle.speed();

    // Distance between the point and the sensor plane calculated on the speed vector.
    real distance = Vector::dot((m_topLeft-pos), m_en)/Vector::dot(speed, m_en);
    // Ajust the position so that it's exactly on the sensor surface
    Vector newPos = particle.position() + speed*distance;
    // Calculate the vector from the "origin" of the surface
    Vector proj = newPos - m_topLeft;

    // Project the lenght of this last vector on the two plane axes
    real e1_len = Vector::dot(proj, m_e1)/m_e1.abs();
    real e2_len = Vector::dot(proj, m_e2)/m_e2.abs();

    int row = abs(floor(e1_len/m_pixelHeight));
    int column = abs(floor(e2_len/m_pixelWidth));
    particleDetected(row, column);

}

std::vector< std::vector< integer > > Sensor::data() const
{
    return m_pixelGrid;
}

// kate: indent-mode cstyle; space-indent on; indent-width 4; replace-tabs on; 
