cmake_minimum_required(VERSION 3.15)
project(ProjetoPOO)

set(CMAKE_CXX_STANDARD 17)

include_directories("C:\\Visual Leak Detector\\include")

add_executable(ProjetoPOO main.cpp Utils.cpp Utils.h SGestao.cpp SGestao.h Vertice.cpp Vertice.h Aresta.cpp Aresta.h Face.cpp Face.h Modelo.cpp Modelo.h XMLWriter.cpp XMLWriter.h)