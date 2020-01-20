//
// Created by Karbust on 30/10/2019.
//

#ifndef PROJETOPOO_SGESTAO_H
#define PROJETOPOO_SGESTAO_H

#include <string>
#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>
#include "Modelo.h"
#include "Utils.h"
#include "XMLWriter.h"

using namespace std;

class SGestao {
private:
    list<Modelo *> ListaModelos;
    Modelo *ModeloSG;
public:
    SGestao();
    virtual ~SGestao();

    bool Load(const string &fich);
    bool LoadSelec(const string &fich);
    void DisplayModelos();
    void GuardarModelo(Modelo *modelo) {
        ModeloSG = modelo;
        ListaModelos.push_back(modelo);
    }
    Modelo *ReturnModelo() { return ModeloSG; }
    int Contar(Tipo T);
    double AreaModelo(const string &fich);
    bool Envolvente(const string &fich, Vertice &Pmin, Vertice &Pmax);
    unsigned int Memoria();
    unsigned int Memoria(const string &fich);
    Modelo *ModeloMaisMemoria();
    int NumInterseccoes(Vertice *A, Vertice *B);
    bool RemoverModelo(const string &fich);
    void EscreverXML(const string &fich, const string &fich_xml);
    Face *FaceMaiorArea(const string &fich);
    Face *FaceMaiorCurvatura(const string &fich);
};


#endif //PROJETOPOO_SGESTAO_H
