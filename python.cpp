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
#include <boost/foreach.hpp>

using namespace boost::python;

#include "universe.h"

template<typename T>
struct custom_vvector_to_list{
        static PyObject* convert(const std::vector<std::vector<T> >& vv){
                boost::python::list ret;
                BOOST_FOREACH(const std::vector<T>& v, vv) {
                        boost::python::list ret2;
                        BOOST_FOREACH(const T& e, v) {
                            ret2.append(e);
                        }
                        ret.append(ret2);
                }
                return incref(ret.ptr());
        }
};

struct ObstacleWrap : Obstacle, wrapper<Obstacle> {
    real minimumSize() const
    {
        return this->get_override("minimumSize")();
    };

    bool contains(const Vector& point) const
    {
        return this->get_override("contains")();
    };
};

BOOST_PYTHON_MODULE(libesame)
{

    to_python_converter<std::vector<std::vector<integer> >,custom_vvector_to_list<integer> >();

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

    class_<ObstacleWrap, boost::noncopyable>("Obstacle")
        .def("minimumSize", pure_virtual(&ObstacleWrap::minimumSize))
        .def("contains", pure_virtual(&ObstacleWrap::contains))
    ;

    class_<Sphere, bases<ObstacleWrap> >("Sphere")
        .add_property("radius", &Sphere::radius, &Sphere::setRadius)
        .add_property("center", &Sphere::center, &Sphere::setCenter)
        .add_property("accuracy", &Sphere::accuracy, &Sphere::setAccuracy)
        .def("setAbsorbingCoefficient", &Sphere::setAbsorbingCoefficient)
    ;

    class_<Box>("Box")
        .add_property("top_left", &Box::topLeft, &Box::setTopLeft)
        .add_property("bottom_left", &Box::bottomLeft, &Box::setBottomLeft)
        .add_property("top_right", &Box::topRight, &Box::setTopRight)
    ;

    class_<Sensor, bases<Box> >("Sensor")
        .add_property("pixel_rows", &Sensor::pixelRows, &Sensor::setPixelRows)
        .add_property("pixel_columns", &Sensor::pixelColumns, &Sensor::setPixelColumns)
        .def("dump", &Sensor::dump)
        .def("data", &Sensor::data)
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
        .def("addSphere", &Universe::addSphere)
        .def("addSensor", &Universe::addSensor)
        .add_property("accuracy", &Universe::accuracy, &Universe::setAccuracy)
        .add_property("boundary", &Universe::boundary, &Universe::setBoundary)
    ;
}

