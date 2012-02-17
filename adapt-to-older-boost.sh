#!/bin/bash

sed -i s/boost::random::/boost::/g *.cpp *.h
sed -i s/uniform_real_distribution.hpp/uniform_real.hpp/g *.cpp

