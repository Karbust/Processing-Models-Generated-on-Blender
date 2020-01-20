#include <iostream>
#include <iomanip>
#include <ctime>
#include <windows.h>
#include "SGestao.h"

#ifdef DEBUG_MODE
int main() {
#else
int main(int argc, char *argv[]) {
#endif
    //Definir a codificação para UTF-8 para mostrar símbols e carateres especiais
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    streamsize ss = cout.precision(); //Guardar a precisão (número de casas decimais) atual

#ifdef DEBUG_MODE
    //Modo de compilação Debug, testa a memória
    string obj = "cubo.obj";
    while(true){
        cout << "--------------------------------------" << endl;
        auto *SG = new SGestao();
        cout << endl;
        cout << obj << "\n" << endl;
        if(!SG->Load(obj))
            continue;
        cout << "Vértices (Func Contar): " << SG->Contar(VERTICES) << endl;
        cout << "Faces (Func Contar): " << SG->Contar(FACES) << endl;
        cout << "Arestas (Func Contar): " << SG->Contar(ARESTAS) << endl;
        cout << fixed << "Area: " << SG->AreaModelo(obj) << endl;
        cout << "Memória " << obj << ": " << SG->Memoria(obj) << endl;
        cout << "Memória Total: " << SG->Memoria() << endl;
        cout << "Modelo Mais Memoria: " << SG->ModeloMaisMemoria()->ReturnNome() << endl;
        cout << fixed << "Face Maior Área: " << SG->FaceMaiorArea(obj)->ReturnfID() << " com " << SG->FaceMaiorArea(obj)->ReturnArea() << endl;
        cout << fixed << setprecision(2) << "Face Maior Curvatura: " << SG->FaceMaiorCurvatura(obj)->ReturnfID() << " com " << SG->FaceMaiorCurvatura(obj)->ReturnCurvatura() << "°" << endl;
        cout.precision(ss);

        Vertice Pmin = Vertice(0, 0, 0), Pmax = Vertice(0, 0, 0);
        SG->Envolvente(obj, Pmin, Pmax);
        cout << fixed << "Envolvente: " << "[(" << Pmin.ReturnVX() << ", " << Pmin.ReturnVY() << ", " << Pmin.ReturnVZ() << ") , (" << Pmax.ReturnVX() << ", " << Pmax.ReturnVY() << ", " << Pmax.ReturnVZ() << ")]" << endl;

        SG->EscreverXML(obj, string(obj) + ".xml");

        cout << endl;

        SG->DisplayModelos();

        cout << endl;

        cout << "NumInterseções: " << SG->NumInterseccoes(Vertice(112, 209, 319), Vertice(121, 219, 311)) << endl;

        cout << endl;

        if(!SG->RemoverModelo(obj))
            cout << "Remoção Falhada!" << endl;

        SG->DisplayModelos();

        cout << endl;

        delete SG;
        cout << "--------------------------------------" << endl;
    }
#else
    //Modo de compilação Release
    clock_t begin = clock(); //Iniciar o contador

    //Verificar se existem argumentos
    if(argc == 1){
        string path = argv[0];
        size_t i = path.rfind('\\', path.length());
        if (i != string::npos)
            cout << "Exemplo de uso: " << path.substr(i+1, path.length() - i) << " 1.obj 2.obj ..." << endl;
        else
            cout << "Exemplo de uso: " << path << " 1.obj 2.obj ..." << endl;

        return 0;
    }

    auto *SG = new SGestao();
    for (int i = 1; i < argc; ++i) {
        cout << "--------------------------------------" << endl;
        cout << endl;
        cout << argv[i] << "\n" << endl;
        if (!SG->Load(argv[i]))
            continue;
        cout << "Vértices (Func Contar): " << SG->Contar(VERTICES) << endl;
        cout << "Faces (Func Contar): " << SG->Contar(FACES) << endl;
        cout << "Arestas (Func Contar): " << SG->Contar(ARESTAS) << endl;
        cout << fixed << "Area: " << SG->AreaModelo(argv[i]) << endl;
        cout << "Memória " << argv[i] << ": " << SG->Memoria(argv[i]) << endl;
        cout << "Memória Total: " << SG->Memoria() << endl;
        cout << "Modelo Mais Memoria: " << SG->ModeloMaisMemoria()->ReturnNome() << endl;
        cout << fixed << "Face Maior Área: " << SG->FaceMaiorArea(argv[i])->ReturnfID() << " com "
             << SG->FaceMaiorArea(argv[i])->ReturnArea() << endl;
        cout << fixed << setprecision(2) << "Face Maior Curvatura: " << SG->FaceMaiorCurvatura(argv[i])->ReturnfID()
             << " com " << SG->FaceMaiorCurvatura(argv[i])->ReturnCurvatura() << "°" << endl;
        cout.precision(ss);

        Vertice Pmin = Vertice(0, 0, 0), Pmax = Vertice(0, 0, 0);
        SG->Envolvente(argv[i], Pmin, Pmax);
        cout << fixed << "Envolvente: " << "[(" << Pmin.ReturnVX() << ", " << Pmin.ReturnVY() << ", " << Pmin.ReturnVZ()
             << ") , (" << Pmax.ReturnVX() << ", " << Pmax.ReturnVY() << ", " << Pmax.ReturnVZ() << ")]" << endl;

        SG->EscreverXML(argv[i], string(argv[i]) + ".xml");

        cout << endl;

        SG->DisplayModelos();

        cout << endl;

        cout << "NumInterseções: " << SG->NumInterseccoes(Vertice(112, 209, 319), Vertice(121, 219, 311)) << endl;

        cout << endl;

        if (!SG->RemoverModelo(argv[i]))
            cout << "Remoção Falhada!" << endl;

        SG->DisplayModelos();

        cout << endl;

        delete SG;
        cout << "--------------------------------------" << endl;
    }

    clock_t end = clock(); //Parar o contador
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC; //Calcular, em segundos, quanto tempo passou desde o início do contador até à sua paragem

    cout << endl;

    cout << "Operation took " << elapsed_secs << " seconds to complete" << endl;
#endif

    return 1;
}