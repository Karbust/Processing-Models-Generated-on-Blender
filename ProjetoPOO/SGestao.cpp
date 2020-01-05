//
// Created by Karbust on 30/10/2019.
//
#include "SGestao.h"

SGestao::SGestao(){
    cout << __FUNCTION__ << endl;
}

SGestao::~SGestao(){
    cout << __FUNCTION__ << endl;
    for (auto & ListaModelo : ListaModelos)
        delete ListaModelo;
    ListaModelos.clear();
    //delete ModeloSG;
}

bool SGestao::Load(const string &fich) {
    for(auto & ListaModelo : ListaModelos)
        if(ListaModelo->ReturnNome() == fich)
            return false;

    try {
        auto *newModelo = new Modelo(fich);
        GuardarModelo(newModelo);

        /*newModelo->DisplayVertices();
        cout << endl;
        newModelo->DisplayFace();
        cout << endl;*/
        /*newModelo->DisplayArestas();
        cout << endl;*/
    }
    catch(...){
        cout << "O objeto " << fich << " não existe" << endl;
        return false;
    }

    return true;
}

bool SGestao::LoadSelec(const string &fich) {
    for(auto & ListaModelo : ListaModelos)
        if(ListaModelo->ReturnNome() == fich){
            ModeloSG = ListaModelo;
            return true;
        }
    return false;
}

void SGestao::DisplayModelos(){
    for(auto & ListaModelo : ListaModelos)
        cout << ListaModelo->ReturnNome() << endl;
}

int SGestao::Contar(Tipo T) {
    switch(T){
        case VERTICES: return ReturnModelo()->ReturnVerticesCount();
        case FACES: return ReturnModelo()->ReturnFacesCount();
        case ARESTAS: return ReturnModelo()->ReturnArestasCount();
        default: break;
    }
    return 0;
}

double SGestao::AreaModelo(const string &fich) {
    if (!LoadSelec(fich)){
        cout << "O objeto não existe!" << endl;
        return 0;
    }
    float area = 0.0f;
    for(size_t i = 0; i < ModeloSG->ReturnFacesCount(); i++)
        area += ModeloSG->ReturnFaces()[i]->ReturnArea();
    return area;
}

bool SGestao::Envolvente(const string &fich, Vertice &Pmin, Vertice &Pmax) {
    if (!LoadSelec(fich)){
        cout << "O objeto não existe!" << endl;
        return false;
    }

    float XMenor = 0.0f, YMenor = 0.0f, ZMenor = 0.0f, XMaior = 0.0f, YMaior = 0.0f, ZMaior = 0.0f;
    bool XMenorAlt = false, YMenorAlt = false, ZMenorAlt = false, XMaiorAlt = false, YMaiorAlt = false, ZMaiorAlt = false;

    for(auto & Vertice : ModeloSG->ReturnVertices()){
        if(Vertice->ReturnVX() < XMenor || !XMenorAlt){
            XMenor = Vertice->ReturnVX();
            XMenorAlt = true;
        }
        if(Vertice->ReturnVY() < YMenor || !YMenorAlt){
            YMenor = Vertice->ReturnVY();
            YMenorAlt = true;
        }
        if(Vertice->ReturnVZ() < ZMenor || !ZMenorAlt){
            ZMenor = Vertice->ReturnVZ();
            ZMenorAlt = true;
        }

        if(Vertice->ReturnVX() > XMaior || !XMaiorAlt){
            XMaior = Vertice->ReturnVX();
            XMaiorAlt = true;
        }
        if(Vertice->ReturnVY() > YMaior || !YMaiorAlt){
            YMaior = Vertice->ReturnVY();
            YMaiorAlt = true;
        }
        if(Vertice->ReturnVZ() > ZMaior || !ZMaiorAlt){
            ZMaior = Vertice->ReturnVZ();
            ZMaiorAlt = true;
        }
    }

    Pmin = Vertice(XMenor, YMenor, ZMenor);
    Pmax = Vertice(XMaior, YMaior, ZMaior);

    return true;
}

unsigned int SGestao::Memoria() {
    return sizeof(ModeloSG) +
           sizeof(list<Modelo *>) + sizeof(Modelo) * ListaModelos.size() +
           sizeof(string) * ReturnModelo()->ReturnNome().size() +
           sizeof(vector<Vertice *>) + sizeof(Vertice) * ReturnModelo()->ReturnVertices().size() +
           sizeof(vector<Face *>) + sizeof(Face) * ReturnModelo()->ReturnFaces().size() +
           sizeof(vector<Aresta *>) + sizeof(Aresta) * ReturnModelo()->ReturnArestas().size() +
           sizeof(size_t) * ReturnModelo()->ReturnVerticesCount() +
           sizeof(size_t) * ReturnModelo()->ReturnFacesCount() +
           sizeof(size_t) * ReturnModelo()->ReturnArestasCount();
}

Modelo *SGestao::Memoria(const string &fich) {
    return nullptr;
}

Modelo *SGestao::ModeloMaisMemoria() {
    return nullptr;
}

int SGestao::NumInterseccoes(Vertice *A, Vertice *B) {
    float Vx = B->ReturnVX() - A->ReturnVX();
    float Vy = B->ReturnVY() - A->ReturnVY();
    float Vz = B->ReturnVZ() - A->ReturnVZ();

    float Ax = A->ReturnVX();
    float Ay = A->ReturnVY();
    float Az = A->ReturnVZ();

    int contador = 0;

    for(auto & Face : ModeloSG->ReturnFaces())
        if(Face->Intersecao(Ax, Ay, Az, Vx, Vy, Vz)){
            Vertice *V = Face->CalcularIntersecao(Ax, Ay, Az, Vx, Vy, Vz);
            if(Face->VerificaPontoNoPlano(V) && Face->EstaNaFace(V))
                contador++;
            delete V;
        }

    return contador;
}

bool SGestao::RemoverModelo(const string &fich) {
    for(auto i = ListaModelos.begin(); i != ListaModelos.end(); i++)
        if((*i)->ReturnNome() == fich){
            delete (*i);
            ListaModelos.erase(i);
            return true;
        }
    return false;
}

void SGestao::EscreverXML(const string &fich, const string &fich_xml) {
    cout << __FUNCTION__ << endl;
    if (!LoadSelec(fich)){
        cout << "O objeto não existe!" << endl;
        return;
    }
    auto *XX = new XMLWriter(fich_xml);
    XX->WriteStartElement("OBJETO_" + fich);
    XX->WriteStartElement("ESTATISTICAS"); // Abre o Elemento “ESTATISTICAS”
    XX->WriteElementString("TOTAL_VERTICES",to_string(ModeloSG->ReturnVerticesCount()));
    XX->WriteElementString("TOTAL_FACES",to_string(ModeloSG->ReturnFacesCount()));
    XX->WriteElementString("TOTAL_ARESTAS",to_string(ModeloSG->ReturnArestasCount()));
    XX->WriteElementString("TOTAL_AREA",to_string(AreaModelo(fich)));
    XX->WriteStartElement("FACE_MAIOR_AREA"); // Abre o Elemento “FACE_MAIOR_AREA”
    XX->WriteElementString("FACE_ID",to_string(FaceMaiorArea(fich)->ReturnfID()));
    XX->WriteElementString("AREA",to_string(FaceMaiorArea(fich)->ReturnArea()));
    XX->WriteEndElement(); // Fecha o Elemento “FACE_MAIOR_AREA”
    XX->WriteEndElement(); // Fecha o Elemento “ESTATISTICAS”
    XX->WriteStartElement("VERTICES"); // Abre o Elemento “VERTICES”
    for (int i = 0; i < ModeloSG->ReturnVertices().size(); i++){
        XX->WriteStartElement("VERTICE_" + to_string(i+1)); // Abre o Elemento “VERTICE_<id>”
        XX->WriteElementString("X",to_string(ModeloSG->ReturnVertices()[i]->ReturnVX()));
        XX->WriteElementString("Y",to_string(ModeloSG->ReturnVertices()[i]->ReturnVY()));
        XX->WriteElementString("Z",to_string(ModeloSG->ReturnVertices()[i]->ReturnVZ()));
        XX->WriteEndElement(); // Fecha o Elemento “VERTICE_<id>”
    }
    XX->WriteEndElement(); // Fecha o Elemento “VERTICES”
    XX->WriteStartElement("FACES"); // Abre o Elemento “FACES”
    for(size_t i = 0; i < ModeloSG->ReturnFaces().size(); i++){
        XX->WriteStartElement("FACE_" + to_string(i+1)); // Abre o Elemento “FACE_<id>”
        XX->WriteElementString("AREA",to_string(ModeloSG->ReturnFaces()[i]->ReturnArea()));
        for(size_t j = 0; j < ModeloSG->ReturnFaces()[i]->ReturnVertices().size(); j++){
            XX->WriteStartElement("VERTICE_" + to_string(ModeloSG->ReturnFaces()[i]->ReturnvID()[j])); // Abre o Elemento “VERTICE_<id>”
            XX->WriteElementString("X",to_string(ModeloSG->ReturnFaces()[i]->ReturnVertices()[j]->ReturnVX()));
            XX->WriteElementString("Y",to_string(ModeloSG->ReturnFaces()[i]->ReturnVertices()[j]->ReturnVY()));
            XX->WriteElementString("Z",to_string(ModeloSG->ReturnFaces()[i]->ReturnVertices()[j]->ReturnVZ()));
            XX->WriteEndElement(); // Fecha o Elemento “VERTICE_<id>”
        }
        XX->WriteEndElement(); // Fecha o Elemento “FACE_<id>”
    }
    XX->WriteEndElement(); // Fecha o Elemento “FACES”
    XX->WriteStartElement("ARESTAS"); // Abre o Elemento “ARESTAS”
    for(size_t i = 0; i < ModeloSG->ReturnArestas().size(); i++){
        //cout << fixed << "[(" << ModeloSG->ReturnArestas()[i]->ReturnVertex1()->ReturnVX() << ", " << ModeloSG->ReturnArestas()[i]->ReturnVertex1()->ReturnVY() << ", " << ModeloSG->ReturnArestas()[i]->ReturnVertex1()->ReturnVZ() << "); (" << ModeloSG->ReturnArestas()[i]->ReturnVertex2()->ReturnVX() << ", " << ModeloSG->ReturnArestas()[i]->ReturnVertex2()->ReturnVY() << ", " << ModeloSG->ReturnArestas()[i]->ReturnVertex2()->ReturnVZ() << ")]" << endl;
        XX->WriteStartElement("ARESTA_" + to_string(i+1));

        XX->WriteStartElement("PONTO_1");
        XX->WriteElementString("X",to_string(ModeloSG->ReturnArestas()[i]->ReturnVertex1()->ReturnVX()));
        XX->WriteElementString("Y",to_string(ModeloSG->ReturnArestas()[i]->ReturnVertex1()->ReturnVY()));
        XX->WriteElementString("Z",to_string(ModeloSG->ReturnArestas()[i]->ReturnVertex1()->ReturnVZ()));
        XX->WriteEndElement(); // Fecha o Elemento “PONTO_1”

        XX->WriteStartElement("PONTO_2");
        XX->WriteElementString("X",to_string(ModeloSG->ReturnArestas()[i]->ReturnVertex2()->ReturnVX()));
        XX->WriteElementString("Y",to_string(ModeloSG->ReturnArestas()[i]->ReturnVertex2()->ReturnVY()));
        XX->WriteElementString("Z",to_string(ModeloSG->ReturnArestas()[i]->ReturnVertex2()->ReturnVZ()));
        XX->WriteEndElement(); // Fecha o Elemento “PONTO_2”

        XX->WriteEndElement(); // Fecha o Elemento “FACE_<id>”
    }

    XX->WriteEndElement(); // Fecha o Elemento “ARESTAS”
    XX->WriteEndElement(); // Fecha o Elemento “DADOS”

    delete XX;
}

Face *SGestao::FaceMaiorArea(const string &fich) {
    if (!LoadSelec(fich)){
        cout << "O objeto não existe!" << endl;
        return nullptr;
    }

    Face *temp = nullptr;
    float temp_area = 0.0f;

    for(auto & Face : ModeloSG->ReturnFaces()){
        if(Face->ReturnArea() > temp_area){
            temp_area = Face->ReturnArea();
            temp = Face;
        }
    }

    return temp;
}

Face *SGestao::FaceMaiorCurvatura(const string &fich) {
    if (!LoadSelec(fich)){
        cout << "O objeto não existe!" << endl;
        return nullptr;
    }

    //vector<Face *> ListaFacesVizinhas = ModeloSG->ReturnFaces()[5]->DeterminarFacesVizinhas(ModeloSG->ReturnFaces(), ModeloSG->ReturnArestasFace());

    for(size_t i = 0; i < ModeloSG->ReturnFaces().size(); i++){
        vector<Face *> ListaFacesVizinhas = ModeloSG->ReturnFaces()[i]->DeterminarFacesVizinhas(ModeloSG->ReturnFaces());

        float normal = 0.0f;

        /*for(size_t j = 1; j < ListaFacesVizinhas.size() - 1; j++)
            normal += ModeloSG->ReturnFaces()[i]->ReturnNormal()->ProdInterno(ListaFacesVizinhas[j+1]->ReturnNormal());*/
            //normal += ModeloSG->ReturnFaces()[i]->ReturnNormal()->ProdInterno(ListaFacesVizinhas[j]->ReturnNormal());

        //cout << "ListaFacesVizinhas = " << ListaFacesVizinhas.size() << endl;

        //cout << fixed << "Normal " << i << ": " << acos(normal) << endl;

        //ModeloSG->ReturnFaces()[i]->SetCurvatura(acos(normal));
    }

    Face *temp = nullptr;
    /*float temp_curv = 0.0f;

    for(auto & Face : ModeloSG->ReturnFaces()){
        if(Face->ReturnCurvatura() > temp_curv){
            temp_curv = Face->ReturnCurvatura();
            temp = Face;
        }
    }*/

    return ModeloSG->ReturnFaces()[1];
}
