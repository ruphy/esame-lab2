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

#include <boost/python.hpp>
using namespace boost::python;

#include "universe.h"


BOOST_PYTHON_MODULE(libesame)
{
    class_<Vector>("Vector")
        .def(init<double, double, double>())
        .add_property("x", &Vector::x, &Vector::setX)
        .add_property("y", &Vector::y, &Vector::setY)
        .add_property("z", &Vector::z, &Vector::setZ)
        .def(self + Vector())
        .def(self - Vector())
        .def(self == Vector())
        .def("normalized", &Vector::normalized)
        .def("abs", &Vector::abs)
        .def("dump", &Vector::dump)
        .def("dot", &Vector::dot)
        .def("cross", &Vector::cross)
        .staticmethod("dot")
        .staticmethod("cross")
    ;

    class_<Box>("Box")
        .add_property("top_left", &Box::topLeft, &Box::setTopLeft)
        .add_property("bottom_left", &Box::bottomLeft, &Box::setBottomLeft)
        .add_property("top_right", &Box::topRight, &Box::setTopRight)
    ;
    class_<Sensor, bases<Box> >("Sensor")
        .add_property("pixel_rows", &Sensor::pixelRows, &Sensor::setPixelRows)
        .add_property("pixel_columns", &Sensor::pixelColumns, &Sensor::setPixelColumns)
    ;
    class_<Generator>("Generator")
        .add_property("position", &Generator::position, &Generator::setPosition)
        .add_property("particles_speed", &Generator::particlesSpeed, &Generator::setParticlesSpeed)
        .add_property("fire_rate", &Generator::fireRate, &Generator::setFireRate)
    ;
    
    class_<Universe>("Universe")
        .def("nextBatch", &Universe::nextBatch)
        .def("reset", &Universe::reset)
        .def("addGenerator", &Universe::addGenerator)
        .def("addObstacle", &Universe::addObstacle)
        .def("addSensor", &Universe::addSensor)
        .add_property("accuracy", &Universe::accuracy, &Universe::setAccuracy)
        .add_property("boundary", &Universe::boundary, &Universe::setBoundary)
    ;
}

