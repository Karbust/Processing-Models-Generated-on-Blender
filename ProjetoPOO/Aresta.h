//
// Created by Karbust on 30/10/2019.
//

#ifndef PROJETOPOO_ARESTA_H
#define PROJETOPOO_ARESTA_H
#include "Vertice.h"

class Aresta {
    Vertice *Vertex1, *Vertex2;
public:
    Aresta(Vertice *V1, Vertice *V2); //Construtor
    Vertice *ReturnVertex1() { return Vertex1; }; //Return da variável Vertex1
    Vertice *ReturnVertex2() { return Vertex2; }; //Return da variável Vertex2
};


#endif //PROJETOPOO_ARESTA_H
