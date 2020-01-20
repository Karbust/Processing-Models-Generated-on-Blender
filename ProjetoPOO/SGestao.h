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
    SGestao(); //Construtor
    virtual ~SGestao(); //Destrutor

    bool Load(const string &fich); //Carregar o ficheiro
    bool LoadSelec(const string &fich); //Selecionar o ficheiro já carregado
    void DisplayModelos(); //Mostrar os ficheiros em memória (já carregados)
    void GuardarModelo(Modelo *modelo) {
        ModeloSG = modelo;
        ListaModelos.push_back(modelo);
    } //Guardar o ficheiro selecionado em memória
    Modelo *ReturnModelo() { return ModeloSG; } //Devolver o ficheiro selecionado/carregado em memória
    int Contar(Tipo T); //Contar os VERTICES, FACES e ARESTAS
    double AreaModelo(const string &fich); //Devolve a área do modelo
    bool Envolvente(const string &fich, Vertice &Pmin, Vertice &Pmax); //Calcular a envolvente do modelo
    unsigned int Memoria(); //Devolver a memória total
    unsigned int Memoria(const string &fich); //Devolver a memória do um determinado ficheiro
    Modelo *ModeloMaisMemoria(); //Devolver o modelo com mais memória
    int NumInterseccoes(Vertice A, Vertice B); //Calcular o número de interseções que uma semi-reta faz no objeto em memória
    bool RemoverModelo(const string &fich); //Remover um determinado ficheiro da memória
    void EscreverXML(const string &fich, const string &fich_xml); //Exporta o ficheiro em memória para o formato XML
    Face *FaceMaiorArea(const string &fich); //Devolve a Face com maior área
    Face *FaceMaiorCurvatura(const string &fich); //Devolve a Face com maior curvatura
};


#endif //PROJETOPOO_SGESTAO_H
