cmake_minimum_required(VERSION 3.15)
project(ProjetoPOO)

set(CMAKE_CXX_STANDARD 17)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g -DDEBUG_MODE")
set(CMAKE_CXX_FLAGS_RELEASE "-Ofast -funroll-loops -march=native -mfpmath=sse")

add_executable(ProjetoPOO main.cpp Utils.cpp Utils.h SGestao.cpp SGestao.h Vertice.cpp Vertice.h Aresta.cpp Aresta.h Face.cpp Face.h Modelo.cpp Modelo.h XMLWriter.cpp XMLWriter.h)