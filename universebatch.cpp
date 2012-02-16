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


#include "universebatch.h"

#include <boost/foreach.hpp>
#define foreach BOOST_FOREACH
#include <iostream>

UniverseBatch::UniverseBatch()
{
    m_stepCount = 0;
//     std::cout << "New thread" << std::endl;
//     run();
//     m_thread(&UniverseBatch::do_work, this);
}

UniverseBatch::~UniverseBatch()
{
//     m_thread.join();
}

void UniverseBatch::setObstacleList(std::list< Obstacle::Ptr > list)
{
    m_obstacles = list;
}

void UniverseBatch::setParticleList(Particle::List list)
{
    m_particles = list;
}
void UniverseBatch::setBoundary(real boundary)
{
    m_boundary = boundary;
}
void UniverseBatch::setDeltaT(real deltat)
{
    m_deltat = deltat;
}

void UniverseBatch::run()
{
    while (!m_particles.empty()) {
        m_stepCount++;
        for(Particle::List::iterator it = m_particles.begin(); it != m_particles.end(); ++it) {
            if ((*it).alive()) {
                moveParticle(*it);
            }

            if(!(*it).alive()) {
//                 std::cout << "Deleting a particle" << std::endl;
                it = m_particles.erase(it);
            }
        }
    }
    // Thread finished: add another thread and detach
}

void UniverseBatch::moveParticle(Particle& particle)
{
    if (particle.position().abs() > m_boundary) {
//         std::cout << "Particle too far away. killed." << std::endl;
        particle.absorb(); // Kill the particle
        return;
    }
//     particle.speed().dump();

    Vector deltax = particle.speed()*m_deltat;

    particle.move(m_deltat);
    Vector newPos = particle.position();

    foreach(const Obstacle::Ptr obstacle, m_obstacles) {
        if (obstacle->contains(newPos)) {
//             std::cout << "WAA" << std::endl;
            obstacle->tryAbsorb(particle, deltax.abs());
        }
//         if (!particle.alive()) {
//             break; // Avoid absorbing a particle multiple times? how do you handle colliding objects?
//         }
    }
}
