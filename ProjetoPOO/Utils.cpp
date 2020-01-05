//
// Created by Karbust on 15/11/2019.
//

#include "Utils.h"

/*float Utils::ComprimentoAresta(Vertice *V1, Vertice *V2) {
    return sqrt(pow(V2->ReturnVX() - V1->ReturnVX(), 2) +
    pow(V2->ReturnVY() - V1->ReturnVY(), 2) +
    pow(V2->ReturnVZ() - V1->ReturnVZ(), 2));
}*/

float Utils::ProdutoInterno(float r1, float r2, float r3, float r4, float r5, float r6){
    return r1 * r4 + r2 * r5 + r4 * r6;
}

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
