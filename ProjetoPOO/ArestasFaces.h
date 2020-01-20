//
// Created by Karbust on 04/01/2020.
//

#ifndef PROJETOPOO_ARESTASFACES_H
#define PROJETOPOO_ARESTASFACES_H

#include <vector>
#include "Aresta.h"
#include "Face.h"

using namespace std;

class Face;

class ArestasFaces {
    int F;
    vector<Aresta *> A;
public:
    ArestasFaces();
    ~ArestasFaces();
    void Add(vector<Aresta *> VAresta, int fID) {
        F = fID;
        A = VAresta;
    };
    int ReturnFace() { return F; };
    vector<Aresta *> ReturnAresta() { return A; };
};


#endif //PROJETOPOO_ARESTASFACES_H
