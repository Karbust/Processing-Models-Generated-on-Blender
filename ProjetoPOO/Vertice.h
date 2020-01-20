//
// Created by Karbust on 30/10/2019.
//

#ifndef PROJETOPOO_VERTICE_H
#define PROJETOPOO_VERTICE_H

class Vertice {
private:
    float VerticeX, VerticeY, VerticeZ;
public:
    Vertice(float VertexX, float VertexY, float VertexZ); //Construtor
    float ReturnVX() { return VerticeX; }; //Devolve o valor de X do vértice
    float ReturnVY() { return VerticeY; }; //Devolve o valor de Y do vértice
    float ReturnVZ() { return VerticeZ; }; //Devolve o valor de Z do vértice
    float ProdInterno(Vertice *V) const { return (VerticeX * V->ReturnVX()) + (VerticeY * V->ReturnVY()) + (VerticeZ * V->ReturnVZ()); } //Calcula o Produto Interno
};

#endif
