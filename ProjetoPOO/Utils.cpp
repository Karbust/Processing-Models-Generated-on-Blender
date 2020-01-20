//
// Created by Karbust on 15/11/2019.
//

#include "Utils.h"

bool Utils::CompararVertice(Vertice * V1, Vertice * V2) {
    return V1->ReturnVX() == V2->ReturnVX() && V1->ReturnVY() == V2->ReturnVY() && V1->ReturnVZ() == V2->ReturnVZ();
}

bool Utils::CompararAresta(Aresta * A1, Aresta * A2) {
    return (CompararVertice(A1->ReturnVertex1(), A2->ReturnVertex1()) && CompararVertice(A1->ReturnVertex2(), A2->ReturnVertex2()))
            || (CompararVertice(A1->ReturnVertex1(), A2->ReturnVertex2()) && CompararVertice(A1->ReturnVertex2(), A2->ReturnVertex1()));
}

Aresta * Utils::CompararArestas(Aresta * A, const vector<Aresta *>& Arestas) {
    for (auto& Aresta1 : Arestas)
        if ((CompararAresta(Aresta1, A)))
            return A;
    return nullptr;
}
