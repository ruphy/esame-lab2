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


#ifndef PARTICLE_H
#define PARTICLE_H

#include "vector.h"
#include <list>

class Generator;

class Particle
{

public:
    typedef std::list<Particle> List;
    
    Particle();
    virtual ~Particle();

    Particle(const Particle& other);
    
    /**
     * @return true if the particle has not been absorbed yet.
     */
    bool alive();
    
    /**
     * @return the current speed of the particle
     */
    Vector speed() const;
    
    /**
     * @return the current position of the particle
     */
    Vector position() const;
    
    /**
     * @return the position of the source where the particle was generated
     */
    Vector source() const;
    
    /**
     * Kill (absorb) the particle
     */
    virtual void absorb();

    /**
     * Move the particle
     */
    void move(real deltat);
    
private:
    void setSource(const Vector& source);
    void setSpeed(const Vector& speed);
    
    bool m_alive;
    Vector m_speed;
    Vector *m_position;
    Vector m_source;
    
    friend class Generator;
};

#endif // PARTICLE_H
// kate: indent-mode cstyle; space-indent on; indent-width 4; replace-tabs on; 
