Esame labinf 2
==============

A simple, multithreaded and extremely generic engine for montecarlo simulations.

Dependencies
------------

To compile this application you need:

* boost-devel
* python-devel

Depending on your distro you might also need development packages
for the following boost subcomponents:

* boost-python
* boost-thread(-mt)
* boost-random

How to compile this application
-------------------------------
To build this application, follow the usual cmake stuff:

    $ mkdir build; cd build
    $ cmake ..
    $ make [-j3]

The install target has not been written yet.

**NOTE:**
To compile this application on non particularly recent systems,
on systems where boost is not recent enough and doesn't contain
some of the new namespaces, you need some adjustments in the code.
For this purpose, a script has been created, you just need to run

    ./adapt-to-older-boost.sh


How to run this application
---------------------------

* To run the C++ executable, just launch it on the command line.

* To run the Python executable, make sure to copy it in the
directory where there is also "libesame.so". This is because if
you don't do so Python doesn't know where to search for the
library (it is not installed in the usual paths).

