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


#ifndef UNIVERSEBATCH_H
#define UNIVERSEBATCH_H

#include "particle.h"
#include "obstacle.h"

class UniverseBatch 
{

public:
    UniverseBatch();
    virtual ~UniverseBatch();

    void setParticleList(Particle::List list);
    void setObstacleList(std::list<Obstacle::Ptr> list);

    void setBatchNumber(int batch);
    real batchNumber() const;

    void setDeltaT(real deltat);
    real deltaT() const;
    void setBoundary(real boundary);
    real boundary() const;

    virtual void run();

private:
    void moveParticle(Particle &particle);

    real m_deltat;
    real m_boundary;
    int m_batchNumber;

    std::list<Obstacle::Ptr> m_obstacles;
    Particle::List m_particles;
};

#endif // UNIVERSEBATCH_H
