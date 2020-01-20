//
// Created by Karbust on 30/10/2019.
//

#ifndef PROJETOPOO_FACE_H
#define PROJETOPOO_FACE_H
#include <cmath>
#include <vector>
#include <set>
#include "Aresta.h"
#include "Vertice.h"
#include "Utils.h"

using namespace std;

class Face {
private:
    int FaceID{};
    vector<int> VerticeID;
    vector<Vertice *> Vertices;
    Vertice *Normal;
    float area = 0.0f, curvatura = 0.0f, T = 0.0f, D = 0.0f, W1 = 0.0f, W2 = 0.0f, W3 = 0.0f;
    static Vertice *CalcularCoordVetor(Vertice *V1, Vertice *V2);

    //LHS - Left Hand side || RHS - Right Hand side
    struct LessByFaceId{
        bool operator()(Face* lhs, Face* rhs) const { return lhs->FaceID < rhs->FaceID; }
    };
public:
    void CalcularArea(); //Calcula a área da face
    void CalcularFaceNormal(); //Calcula a normal da face (normalizada)
    void CalcularD(); //Calcula o D da face
    bool Intersecao(float Ax, float Ay, float Az, float Vx, float Vy, float Vz); //Calcula a interseção
    Vertice *CalcularIntersecao(float Ax, float Ay, float Az, float Vx, float Vy, float Vz); //Devolve o vértice onde faz interseção na face
    bool VerificaPontoNoPlano(Vertice *V){ return fabs(W1 * V->ReturnVX() + W2 * V->ReturnVY() + W3 * V->ReturnVZ() + D) <= TOL; }; //Verifica se o ponto de interseção se encontra no plano
    bool EstaNaFace(Vertice *V); //Verifica se o ponto está na face
    vector<Face *> DeterminarFacesVizinhas(const vector<Face *>& Faces) const; //Determina as faces vizinhas (pelos vértices)
    void SetCurvatura(float curv) { curvatura = curv; }; //Preenche o valor da curvatura
    void Add(int fID, int vID, Vertice *V){
        FaceID = fID;
        VerticeID.push_back(vID);
        Vertices.push_back(V);
    } //Preenche o valor do ID da face e adiciona os ID's dos vértices e os vértices aos respetivos vetores.
    int ReturnfID() { return FaceID; }; //Devolve o ID da Face
    vector<int> ReturnvID() { return VerticeID; }; //Deolve os ID's dos vértices
    vector<Vertice *> ReturnVertices() { return Vertices; }; //Devolve os vértices
    float ReturnArea() { return area; }; //Devolve a área da face
    float ReturnCurvatura() { return curvatura; }; //Devolve a curvatura da face
    Vertice *ReturnNormal() { return Normal; }; //Devolve a normal da face
};


#endif //PROJETOPOO_FACE_H
