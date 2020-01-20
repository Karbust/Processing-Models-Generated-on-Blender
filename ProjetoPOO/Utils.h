//
// Created by Karbust on 15/11/2019.
//

#ifndef PROJETOPOO_UTILS_H
#define PROJETOPOO_UTILS_H

#define TOL 0.0000001

#include <iostream>
#include <vector>
#include "Vertice.h"
#include "Face.h"
#include "Aresta.h"

using namespace std;

enum Tipo {VERTICES, FACES, ARESTAS};

class Utils {
public:
    static bool CompararVertice(Vertice *v1, Vertice *v2);
    static bool CompararAresta(Aresta *A1, Aresta *A2);
    static Aresta *CompararArestas(Aresta *A, const vector<Aresta *>& Arestas);
};


#endif //PROJETOPOO_UTILS_H
