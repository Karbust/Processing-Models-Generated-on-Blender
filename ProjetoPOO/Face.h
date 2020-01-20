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
    vector<Aresta *> Arestas;
    Vertice *Normal;
    float area = 0.0f, curvatura = 0.0f, T = 0.0f, D = 0.0f, W1 = 0.0f, W2 = 0.0f, W3 = 0.0f;
    static Vertice *CalcularCoordVetor(Vertice *V1, Vertice *V2);

    //LHS - Left Hand side || RHS - Right Hand side
    struct LessByFaceId{
        bool operator()(Face* lhs, Face* rhs) const { return lhs->FaceID < rhs->FaceID; }
    };
public:
    void CalcularArea();
    void CalcularFaceNormal();
    void CalcularD();
    bool Intersecao(float Ax, float Ay, float Az, float Vx, float Vy, float Vz);
    Vertice *CalcularIntersecao(float Ax, float Ay, float Az, float Vx, float Vy, float Vz);
    bool VerificaPontoNoPlano(Vertice *V){ return fabs(W1 * V->ReturnVX() + W2 * V->ReturnVY() + W3 * V->ReturnVZ() + D) <= TOL; };
    bool EstaNaFace(Vertice *V);
    vector<Face *> DeterminarFacesVizinhas(const vector<Face *>& Faces) const;
    void SetCurvatura(float curv) { curvatura = curv; };
    void Add(int fID, int vID, Vertice *V){
        FaceID = fID;
        VerticeID.push_back(vID);
        Vertices.push_back(V);
    }
    int ReturnfID() { return FaceID; };
    vector<int> ReturnvID() { return VerticeID; };
    vector<Vertice *> ReturnVertices() { return Vertices; };
    vector<Aresta *> ReturnArestas() { return Arestas; };
    void SetArestas(vector<Aresta *> A){
        Arestas = A;
    };
    float ReturnArea() { return area; };
    float ReturnCurvatura() { return curvatura; };
    Vertice *ReturnNormal() { return Normal; };
};


#endif //PROJETOPOO_FACE_H
