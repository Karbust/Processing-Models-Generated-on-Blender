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
    float area = 0.0f;
    Face *FaceMaiorArea, *FaceMaiorCurvatura;
    unsigned int Memoria;
public:
    explicit Modelo(const string &fich); //Construtor
    ~Modelo(); //Destrutor
    string ReturnNome() { return Nome; } //Devolve o Nome do ficheiro
    vector<Vertice *> ReturnVertices() { return Vertices; } //Devolve o vetor dos vértices
    vector<Face *> ReturnFaces() { return Faces; } //Devolve o vetor das faces
    vector<Aresta *> ReturnArestas() { return Arestas; } //Devolve o vetor das arestas
    size_t ReturnVerticesCount() { return m_VerticesCount; } //Devolve a contagem de vértices
    size_t ReturnFacesCount() { return m_FacesCount; } //Devolve a contagem de faces
    size_t ReturnArestasCount() { return m_ArestasCount; } //Devolve a contagem de arestas
    float ReturnArea() { return area; } //Devolve a área do modelo
    Face *ReturnFaceMaiorArea() { return FaceMaiorArea; } //Devolve a face com maior área
    Face *ReturnFaceMaiorCurvatura() { return FaceMaiorCurvatura; } //Devolve a Face com maior curvatura
    unsigned int ReturnMemoria() { return Memoria; } //Devolve a memória ocupada pelo modelo
    void DisplayVertices(); //Mostra os vértices
    void DisplayFace(); //Mostra as faces
    void DisplayArestas(); //Mostra as arestas
};


#endif //PROJETOPOO_MODELO_H
