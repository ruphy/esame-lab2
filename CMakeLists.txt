project(esame-lab2)

cmake_minimum_required(VERSION 2.8)

set(esame_src
    src/box.cpp
    src/generator.cpp
    src/obstacle.cpp
    src/particle.cpp
    src/universe.cpp
    src/universebatch.cpp
    src/vector.cpp
    src/sensor.cpp
    src/sphere.cpp
    )

find_package(PythonLibs)
find_package(Threads REQUIRED)

find_package(Boost COMPONENTS thread-mt REQUIRED)
INCLUDE_DIRECTORIES("${Boost_INCLUDE_DIRS}" ${CMAKE_SOURCE_DIR})

IF(CMAKE_COMPILER_IS_GNUCXX)
  ADD_DEFINITIONS("-Wall")
ELSE()
  MESSAGE(FATAL_ERROR "CMakeLists.txt has not been tested/written for your compiler.")
ENDIF()


add_executable(esame-lab2 src/main.cpp ${esame_src})
target_link_libraries(esame-lab2 ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

## IF PYTHON FOUND!
IF(Boost_FOUND)
INCLUDE_DIRECTORIES("${Boost_INCLUDE_DIRS}" "${PYTHON_INCLUDE_DIRS}")
  SET(Boost_USE_STATIC_LIBS OFF)
  SET(Boost_USE_MULTITHREADED ON)
  SET(Boost_USE_STATIC_RUNTIME OFF)
  find_package(Boost COMPONENTS python REQUIRED)

  ADD_LIBRARY(esame SHARED src/python.cpp ${esame_src})
  TARGET_LINK_LIBRARIES(esame ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} ${PYTHON_LIBRARY})
ELSEIF(NOT Boost_FOUND)
  MESSAGE(FATAL_ERROR "Unable to find correct Boost version. Did you set BOOST_ROOT?")
ENDIF()

