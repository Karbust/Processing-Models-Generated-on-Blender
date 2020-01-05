//
// Created by Karbust on 30/10/2019.
//

#ifndef PROJETOPOO_VERTICE_H
#define PROJETOPOO_VERTICE_H

#include <cmath>

class Vertice {
private:
    float VerticeX, VerticeY, VerticeZ;
public:
    Vertice(float VertexX, float VertexY, float VertexZ);
    float ReturnVX() { return VerticeX; };
    float ReturnVY() { return VerticeY; };
    float ReturnVZ() { return VerticeZ; };
    float ProdInterno(Vertice *V) const { return (VerticeX * V->ReturnVX()) + (VerticeY * V->ReturnVY()) + (VerticeZ * V->ReturnVZ()); }
};

#endif
