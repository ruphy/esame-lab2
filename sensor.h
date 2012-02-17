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

#include "box.h"

#include <vector>

#include <boost/thread/mutex.hpp>

/**
 * A sensor is a square 2d surface, with a given size,
 * normal (for orientation) and center.
 */

class Sensor : public Box
{

public:
    typedef boost::shared_ptr<Sensor> Ptr;

    Sensor();
    virtual ~Sensor();

    void setPixelRows(int rows);
    int pixelRows() {return m_pixelRows;};
    void setPixelColumns(int columns);
    int pixelColumns() {return m_pixelColumns; };

    virtual bool contains(const Vector& point) const;

    virtual void tryAbsorb(Particle& particle, real lenght);

    void dump() const; // just a debug function
    
    std::vector< std::vector<integer> > data() const;
    
protected:
    virtual void init();
    
private:
    void particleDetected(int row, int column);

    int m_pixelRows;
    int m_pixelColumns;

//     boost::mutex m_mutex;
    
    std::vector< std::vector<integer> > m_pixelGrid;
    real m_pixelWidth;
    real m_pixelHeight;
    int counter;
};

#endif // SENSOR_H
// kate: indent-mode cstyle; space-indent on; indent-width 4; replace-tabs on; 
