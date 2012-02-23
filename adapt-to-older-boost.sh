#!/bin/bash

sed -i s/boost::random::/boost::/g src/*.cpp src/*.h
sed -i s/uniform_real_distribution/uniform_real/g src/*.cpp

