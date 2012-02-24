Esame labinf 2
==============

NOTE:
To compile this application on non particularly recent systems,
make sure to run the "./adapt-to-older-boost.sh" script before
following this guide.

Dependencies
------------

To compile this application you need:

* boost-devel, and depending on your distro you might also
  need devel packages for the following subcomponents:
    * boost-python, boost-thread(-mt), boost-random
* python-devel

How to compile this application
-------------------------------
To build this application, follow the usual cmake stuff:

    $ mkdir build; cd build
    $ cmake ..
    $ make [-j3]

The install target has not been written yet.

How to run this application
---------------------------

* To run the C++ executable, just launch it on the command line.

* To run the Python executable, make sure to copy it in the
directory where there is also "libesame.so". This is because if
you don't do so Python doesn't know where to search for the
library (it is not installed in the usual paths).

