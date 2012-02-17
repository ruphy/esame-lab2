project(esame-lab2)

cmake_minimum_required(VERSION 2.8)

set(esame_src
    box.cpp
    generator.cpp
    obstacle.cpp
    particle.cpp
    universe.cpp
    universebatch.cpp
    vector.cpp
    sensor.cpp
    sphere.cpp
    )

find_package(PythonLibs)
find_package(Threads REQUIRED)

# Use Threadweaver
# find_package(KDE4 REQUIRED)
# include(KDE4Defaults)
find_package(Boost COMPONENTS random python thread REQUIRED)
INCLUDE_DIRECTORIES("${Boost_INCLUDE_DIRS}" ${CMAKE_SOURCE_DIR})
add_definitions("-fexceptions")


## IF PYTHON FOUND!
IF(Boost_FOUND)
INCLUDE_DIRECTORIES("${Boost_INCLUDE_DIRS}" "${PYTHON_INCLUDE_DIRS}")
  SET(Boost_USE_STATIC_LIBS OFF)
  SET(Boost_USE_MULTITHREADED ON)
  SET(Boost_USE_STATIC_RUNTIME OFF)
#   FIND_PACKAGE(Boost COMPONENTS python REQUIRED)

  ADD_LIBRARY(esame SHARED python.cpp ${esame_src})
  TARGET_LINK_LIBRARIES(esame ${Boost_LIBRARIES} ${PYTHON_LIBRARY})
# target_link_libraries(esame-lab2 ${CMAKE_THREAD_LIBS_INIT})
ELSEIF(NOT Boost_FOUND)
  MESSAGE(FATAL_ERROR "Unable to find correct Boost version. Did you set BOOST_ROOT?")
ENDIF()

IF(CMAKE_COMPILER_IS_GNUCXX)
  ADD_DEFINITIONS("-Wall")
ELSE()
  MESSAGE(FATAL_ERROR "CMakeLists.txt has not been tested/written for your compiler.")
ENDIF()


add_executable(esame-lab2 main.cpp ${esame_src})
target_link_libraries(esame-lab2 ${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES})
