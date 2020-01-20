#include <iostream>
#include <iomanip>
#include <ctime>
#include <windows.h>
#include "SGestao.h"

int main(int argc, char *argv[]) {
    //Definir a codificação para UTF-8 para mostrar símbols e carateres especiais
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    streamsize ss = cout.precision(); //Guardar a precisão (número de casas decimais) atual

    clock_t begin = clock(); //Iniciar o contador

#ifdef DEBUG_MODE
    //Modo de compilação Debug, testa a memória
    for (int i = 1; i < argc; ++i) {
        while(true){
            cout << "--------------------------------------" << endl;
            auto *SG = new SGestao();
            cout << endl;
            cout << argv[i] << "\n" << endl;
            if(!SG->Load(argv[i]))
                continue;
            cout << "Vértices (Func Contar): " << SG->Contar(VERTICES) << endl;
            cout << "Faces (Func Contar): " << SG->Contar(FACES) << endl;
            cout << "Arestas (Func Contar): " << SG->Contar(ARESTAS) << endl;
            cout << fixed << "Area: " << SG->AreaModelo(argv[i]) << endl;
            cout << "Memória " << argv[i] << ": " << SG->Memoria(argv[i]) << endl;
            cout << "Memória Total: " << SG->Memoria() << endl;
            cout << "Modelo Mais Memoria: " << SG->ModeloMaisMemoria()->ReturnNome() << endl;
            cout << fixed << "Face Maior Área: " << SG->FaceMaiorArea(argv[i])->ReturnfID() << " com " << SG->FaceMaiorArea(argv[i])->ReturnArea() << endl;
            cout << fixed << setprecision(2) << "Face Maior Curvatura: " << SG->FaceMaiorCurvatura(argv[i])->ReturnfID() << " com " << SG->FaceMaiorCurvatura(argv[i])->ReturnCurvatura() << "°" << endl;
            cout.precision(ss);

            Vertice Pmin = Vertice(0, 0, 0), Pmax = Vertice(0, 0, 0);
            SG->Envolvente(argv[i], Pmin, Pmax);
            cout << fixed << "Envolvente: " << "[(" << Pmin.ReturnVX() << ", " << Pmin.ReturnVY() << ", " << Pmin.ReturnVZ() << ") , (" << Pmax.ReturnVX() << ", " << Pmax.ReturnVY() << ", " << Pmax.ReturnVZ() << ")]" << endl;

            SG->EscreverXML(argv[i], string(argv[i]) + ".xml");

            cout << endl;

            SG->DisplayModelos();

            cout << endl;

            cout << "NumInterseções: " << SG->NumInterseccoes(Vertice(112, 209, 319), Vertice(121, 219, 311)) << endl;

            cout << endl;

            if(!SG->RemoverModelo(argv[i]))
                cout << "Remoção Falhada!" << endl;

            SG->DisplayModelos();

            cout << endl;

            delete SG;
            cout << "--------------------------------------" << endl;
        }
    }
#else
    //Modo de compilação Release
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
#endif

    clock_t end = clock(); //Parar o contador
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC; //Calcular, em segundos, quanto tempo passou desde o início do contador até à sua paragem

    cout << endl;

    cout << "Operation took " << elapsed_secs << " seconds to complete" << endl;

    return 1;
}