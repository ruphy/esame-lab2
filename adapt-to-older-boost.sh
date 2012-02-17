#!/bin/bash

sed -i s/boost::random::/boost::/g *.cpp *.h
sed -i s/uniform_real_distribution/uniform_real/g *.cpp

