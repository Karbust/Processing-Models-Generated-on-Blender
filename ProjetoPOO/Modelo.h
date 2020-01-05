//
// Created by Karbust on 30/10/2019.
//

#ifndef PROJETOPOO_MODELO_H
#define PROJETOPOO_MODELO_H

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include "Vertice.h"
#include "Face.h"
#include "Aresta.h"
#include "Utils.h"

using namespace std;

class Modelo {
private:
    string Nome;
    vector<Vertice *> Vertices;
    vector<Face *> Faces;
    vector<Aresta *> Arestas;
    size_t m_VerticesCount = 0;
    size_t m_FacesCount = 0;
    size_t m_ArestasCount = 0;

    void AddValueVertices(float VertexX, float VertexY, float VertexZ) {
        Vertices.push_back(new Vertice(VertexX, VertexY, VertexZ));
    }
public:
    explicit Modelo(const string &fich);
    ~Modelo();
    void DisplayVertices();
    void DisplayFace();
    void DisplayArestas();
    void DisplayAresta(Aresta *A);
    string ReturnNome() { return Nome; };
    vector<Vertice *> ReturnVertices() { return Vertices; };
    vector<Face *> ReturnFaces() { return Faces; };
    vector<Aresta *> ReturnArestas() { return Arestas; };
    size_t ReturnVerticesCount() { return m_VerticesCount; };
    size_t ReturnFacesCount() { return m_FacesCount; };
    size_t ReturnArestasCount() { return m_ArestasCount; };
};


#endif //PROJETOPOO_MODELO_H
