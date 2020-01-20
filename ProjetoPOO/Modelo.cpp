//
// Created by Karbust on 30/10/2019.
//

#include "Modelo.h"

Modelo::Modelo(const string &fich){
    ifstream objeto (fich);

    if(objeto.fail())
        throw exception();

    string line, temp, v;
    int i = 0, w = 1;
    float VertexX = 0.0f, VertexY = 0.0f, VertexZ = 0.0f;

    while(!objeto.eof()){
        getline (objeto,line);
        if (line[0] == 'v'){
            istringstream iss(line);
            iss >> v >> VertexX >> VertexY >> VertexZ;
            AddValueVertices(VertexX, VertexY, VertexZ);
        }
        else if(line[0] == 'f'){
            istringstream iss(line);
            Face *novaFace = new Face();
            i = 0;
            while(iss >> temp){
                if(i != 0)
                    novaFace->Add(w, stoi(temp), ReturnVertices()[stoi(temp)-1]);
                i++;
            }

            temp.clear();

            vector<Aresta *> A;

            for(size_t j = 0; j < novaFace->ReturnVertices().size(); j++){
                size_t z = j + 1;
                if (z == (novaFace->ReturnVertices().size()))
                    z = 0;
                auto *aresta = new Aresta(novaFace->ReturnVertices()[j], novaFace->ReturnVertices()[z]);

                auto check = Utils::CompararArestas(aresta, Arestas);

                if (!check){
                    Arestas.push_back(aresta);
                    A.push_back(aresta);
                }else{
                    delete aresta;
                    A.push_back(check);
                }
            }

            novaFace->SetArestas(A);
            novaFace->CalcularArea();
            novaFace->CalcularFaceNormal();

            Faces.push_back(novaFace);
            area += novaFace->ReturnArea();

            w++;
        }
    }

    float temp_area = 0.0f;

    for(auto & Face : Faces){
        if(Face->ReturnArea() > temp_area){
            temp_area = Face->ReturnArea();
            FaceMaiorArea = Face;
        }
    }

    for(auto & F : Faces){
        vector<Face *> ListaFacesVizinhas = F->DeterminarFacesVizinhas(Faces);

        float normal = 0.0f;

        for(auto & LFV : ListaFacesVizinhas)
            normal += F->ReturnNormal()->ProdInterno(LFV->ReturnNormal());

        F->SetCurvatura(acos(normal)*180/M_PI);
    }

    float temp_curv = 0.0f;

    for(auto & Face : Faces){
        if(Face->ReturnCurvatura() > temp_curv){
            temp_curv = Face->ReturnCurvatura();
            FaceMaiorCurvatura = Face;
        }
    }

    Nome = fich;
    m_VerticesCount = ReturnVertices().size();
    m_FacesCount = ReturnFaces().size();
    m_ArestasCount = ReturnArestas().size();

    Memoria = sizeof(string) * Nome.size() +
              sizeof(vector<Vertice *>) + sizeof(Vertice) * Vertices.size() +
              sizeof(vector<Face *>) + sizeof(Face) * Faces.size() +
              sizeof(vector<Aresta *>) + sizeof(Aresta) * Arestas.size() +
              sizeof(size_t) * m_VerticesCount +
              sizeof(size_t) * m_FacesCount +
              sizeof(size_t) * m_ArestasCount;
}

Modelo::~Modelo(){
    cout << __FUNCTION__ << endl;
    for(auto & Vertice : Vertices)
        delete Vertice;
    for(auto & Aresta : Arestas)
        delete Aresta;
    for(auto & Face : Faces){
        delete Face->ReturnNormal();
        delete Face;
    }
    /*for(auto & ArestaFace : ArestasFace)
        delete ArestaFace;*/

    Vertices.clear();
    Faces.clear();
    Arestas.clear();
};

void Modelo::DisplayVertices() {
    cout << "Vértices: " << endl;
    for (auto & Vertice : Vertices)
        cout << fixed << Vertice->ReturnVX() << " " << Vertice->ReturnVY() << " " << Vertice->ReturnVZ() << endl;

}

void Modelo::DisplayFace() {
    cout << "Faces: " << endl;
    for(size_t i = 0; i < Faces.size(); i++){
        cout << "Face: " << i+1 << endl;
        cout << fixed << "Área: " << Faces[i]->ReturnArea() << endl;
        cout << fixed << "Normal: (" << Faces[i]->ReturnNormal()->ReturnVX() << ", " << Faces[i]->ReturnNormal()->ReturnVY() << ", " << Faces[i]->ReturnNormal()->ReturnVZ() << ")" << endl;
        for(size_t j = 0; j < Faces[i]->ReturnVertices().size(); j++){
            cout << "Vértice " << Faces[i]->ReturnvID()[j] << ": ";
            cout << fixed << Faces[i]->ReturnVertices()[j]->ReturnVX() << " " << Faces[i]->ReturnVertices()[j]->ReturnVY() << " " << Faces[i]->ReturnVertices()[j]->ReturnVZ() << " " << endl;
        }
    }
}

void Modelo::DisplayArestas() {
    cout << "Arestas: " << endl;
    for (auto & Aresta : Arestas)
        cout << fixed << "[(" << Aresta->ReturnVertex1()->ReturnVX() << ", " << Aresta->ReturnVertex1()->ReturnVY() << ", " << Aresta->ReturnVertex1()->ReturnVZ() << "); (" << Aresta->ReturnVertex2()->ReturnVX() << ", " << Aresta->ReturnVertex2()->ReturnVY() << ", " << Aresta->ReturnVertex2()->ReturnVZ() << ")]" << /*"\tComprimento: " << Aresta->ReturnComprimento() <<*/ endl;
}

void Modelo::DisplayAresta(Aresta *A) {
    cout << fixed << "[(" << A->ReturnVertex1()->ReturnVX() << ", " << A->ReturnVertex1()->ReturnVY() << ", " << A->ReturnVertex1()->ReturnVZ() << "); (" << A->ReturnVertex2()->ReturnVX() << ", " << A->ReturnVertex2()->ReturnVY() << ", " << A->ReturnVertex2()->ReturnVZ() << ")]" << endl;
}

