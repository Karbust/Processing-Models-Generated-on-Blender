//
// Created by Karbust on 30/10/2019.
//
#include <iostream>
#include "Face.h"

Vertice * Face::CalcularCoordVetor(Vertice *V1, Vertice *V2){
    float dx = V2->ReturnVX() - V1->ReturnVX();
    float dy = V2->ReturnVY() - V1->ReturnVY();
    float dz = V2->ReturnVZ() - V1->ReturnVZ();

    return new Vertice(dx, dy, dz);
}

void Face::CalcularArea(){
    for (size_t i = 0; i < Vertices.size() - 1; i++) {
        auto *F = new Face();
        auto *V = new Vertice(Vertices[0]->ReturnVX(), Vertices[0]->ReturnVY(), Vertices[0]->ReturnVZ());
        auto *V1 = new Vertice(Vertices[i]->ReturnVX(), Vertices[i]->ReturnVY(), Vertices[i]->ReturnVZ());
        auto *V2 = new Vertice(Vertices[i + 1]->ReturnVX(), Vertices[i + 1]->ReturnVY(),Vertices[i + 1]->ReturnVZ());

        F->Add(i, i, V);
        F->Add(i, i, V1);
        F->Add(i, i, V2);

        Vertice *AB = CalcularCoordVetor(F->Vertices[0], F->Vertices[1]);
        Vertice *AC = CalcularCoordVetor(F->Vertices[0], F->Vertices[2]);

        //Produto Externo
        float ProdVector1 = AB->ReturnVY() * AC->ReturnVZ() - AB->ReturnVZ() * AC->ReturnVY();
        float ProdVector2 = AB->ReturnVZ() * AC->ReturnVX() - AB->ReturnVX() * AC->ReturnVZ();
        float ProdVector3 = AB->ReturnVX() * AC->ReturnVY() - AB->ReturnVY() * AC->ReturnVX();

        area += sqrt(pow(ProdVector1, 2) + pow(ProdVector2, 2) + pow(ProdVector3, 2)) / 2;

        delete AB;
        delete AC;
        delete V;
        delete V1;
        delete V2;
        delete F;
    }
}

void Face::CalcularFaceNormal(){
    float NormalX = 0.0f, NormalY = 0.0f, NormalZ = 0.0f;

    //Algoritmo de Newell
    for(size_t i = 0; i < Vertices.size() - 1; i++){
        auto *V1 = new Vertice(Vertices[i]->ReturnVX(), Vertices[i]->ReturnVY(), Vertices[i]->ReturnVZ());
        auto *V2 = new Vertice(Vertices[(i+1) % Vertices.size()]->ReturnVX(), Vertices[(i+1) % Vertices.size()]->ReturnVY(), Vertices[(i+1) % Vertices.size()]->ReturnVZ());

        NormalX += (((V1->ReturnVY()) - (V2->ReturnVY())) * ((V2->ReturnVZ()) + (V1->ReturnVZ())));
        NormalY += (((V1->ReturnVZ()) - (V2->ReturnVZ())) * ((V2->ReturnVX()) + (V1->ReturnVX())));
        NormalZ += (((V1->ReturnVX()) - (V2->ReturnVX())) * ((V2->ReturnVY()) + (V1->ReturnVY())));

        delete V1;
        delete V2;
    }

    float k = sqrt(pow(NormalX, 2) + pow(NormalY, 2) + pow(NormalZ, 2));

    NormalX /= k;
    NormalY /= k;
    NormalZ /= k;

    Normal = new Vertice(NormalX, NormalY, NormalZ);
}

void Face::CalcularD(){
    for (size_t i = 0; i < Vertices.size() - 1; i++) {
        auto *F = new Face();
        auto *V = new Vertice(Vertices[0]->ReturnVX(), Vertices[0]->ReturnVY(), Vertices[0]->ReturnVZ());
        auto *V1 = new Vertice(Vertices[i]->ReturnVX(), Vertices[i]->ReturnVY(), Vertices[i]->ReturnVZ());
        auto *V2 = new Vertice(Vertices[i + 1]->ReturnVX(), Vertices[i + 1]->ReturnVY(),Vertices[i + 1]->ReturnVZ());

        F->Add(i, i, V);
        F->Add(i, i, V1);
        F->Add(i, i, V2);

        Vertice *AB = CalcularCoordVetor(F->Vertices[0], F->Vertices[1]);
        Vertice *AC = CalcularCoordVetor(F->Vertices[0], F->Vertices[2]);

        //Produto Externo
        W1 += AB->ReturnVY() * AC->ReturnVZ() - AB->ReturnVZ() * AC->ReturnVY();
        W2 += AB->ReturnVZ() * AC->ReturnVX() - AB->ReturnVX() * AC->ReturnVZ();
        W3 += AB->ReturnVX() * AC->ReturnVY() - AB->ReturnVY() * AC->ReturnVX();

        D = ((-1) * W1 * Vertices[0]->ReturnVX()) - ((-1) * W2 * Vertices[0]->ReturnVY()) - ((-1) * W3 * Vertices[0]->ReturnVZ());

        delete AB;
        delete AC;
        delete V;
        delete V1;
        delete V2;
        delete F;
    }
}

bool Face::Intersecao(float Ax, float Ay, float Az, float Vx, float Vy, float Vz){
    CalcularD();

    float Den = (W1 * Vx) + (W2 * Vy) + (W3 * Vz);

    if(fabs(Den) <= TOL)
        return false;

    T = ((-1) * D - (W1 * Ax) - (W2 * Ay) - (W3 * Az)) / Den;

    return fabs(T) > TOL;
}

Vertice *Face::CalcularIntersecao(float Ax, float Ay, float Az, float Vx, float Vy, float Vz){
    float Xi, Yi, Zi;

    Xi = Ax + (T * Vx);
    Yi = Ay + (T * Vy);
    Zi = Az + (T * Vz);

    auto *V = new Vertice(Xi, Yi, Zi);

    return V;
}

bool Face::EstaNaFace(Vertice *V){
    float p1, p2;

    vector<vector<float>> Valores;
    //Vetor1 AB
    Valores.push_back({Vertices[1]->ReturnVX() - Vertices[0]->ReturnVX(), Vertices[1]->ReturnVY() - Vertices[0]->ReturnVY(), Vertices[1]->ReturnVZ() - Vertices[0]->ReturnVZ()});
    //Vetor2 BC
    Valores.push_back({Vertices[2]->ReturnVX() - Vertices[1]->ReturnVX(), Vertices[2]->ReturnVY() - Vertices[1]->ReturnVY(), Vertices[2]->ReturnVZ() - Vertices[1]->ReturnVZ()});
    //Vetor3 CA
    Valores.push_back({Vertices[0]->ReturnVX() - Vertices[2]->ReturnVX(), Vertices[0]->ReturnVY() - Vertices[2]->ReturnVY(), Vertices[0]->ReturnVZ() - Vertices[2]->ReturnVZ()});

    //Vetor4 AI
    Valores.push_back({V->ReturnVX() - Vertices[0]->ReturnVX(), V->ReturnVY() - Vertices[0]->ReturnVY(), V->ReturnVZ() - Vertices[0]->ReturnVZ()});
    //Vetor5 BI
    Valores.push_back({V->ReturnVX() - Vertices[1]->ReturnVX(), V->ReturnVY() - Vertices[1]->ReturnVY(), V->ReturnVZ() - Vertices[1]->ReturnVZ()});
    //Vetor6 CI
    Valores.push_back({V->ReturnVX() - Vertices[2]->ReturnVX(), V->ReturnVY() - Vertices[2]->ReturnVY(), V->ReturnVY() - Vertices[2]->ReturnVY()});

    p1 = ((Valores[0][1] * Valores[3][2]) - (Valores[3][1] * Valores[0][2])) * ((Valores[1][1] * Valores[4][2]) - (Valores[4][1] * Valores[1][2])) +
            ((Valores[0][2] * Valores[3][0]) - (Valores[3][2] * Valores[0][0])) * ((Valores[1][2] * Valores[4][0]) - (Valores[4][2] * Valores[1][0])) +
            ((Valores[0][0] * Valores[3][1]) - (Valores[3][0] * Valores[0][1])) * ((Valores[1][0] * Valores[4][1]) - (Valores[4][0] * Valores[1][1])); //Produto Interno

    p2 = ((Valores[0][1] * Valores[3][2]) - (Valores[3][1] * Valores[0][2])) * ((Valores[2][1] * Valores[5][2]) - (Valores[5][1] * Valores[2][2])) +
            ((Valores[0][2] * Valores[3][0]) - (Valores[3][2] * Valores[0][0])) * ((Valores[2][2] * Valores[5][0]) - (Valores[5][2] * Valores[2][0])) +
            ((Valores[0][0] * Valores[3][1]) - (Valores[3][0] * Valores[0][1])) * ((Valores[2][0] * Valores[5][1]) - (Valores[5][0] * Valores[2][1])); //Produto Interno

    Valores.clear();

    return ((p1 > 0) && (p2 > 0)) || ((p1 < 0) && (p2 < 0));
}

vector<Face *> Face::DeterminarFacesVizinhas(const vector<Face *>& Faces) const {
    set<Face *, LessByFaceId> Lista;

    for (const auto& V1 : Vertices)
        for (const auto& Face : Faces)
            for (const auto& V2 : Face->ReturnVertices())
                if (Utils::CompararVertice(V2, V1) && Face->ReturnfID() != FaceID)
                    Lista.insert(Face);

    return {Lista.begin(), Lista.end()};
}
