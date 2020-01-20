#include <iostream>
#include <iomanip>
#include <ctime>
#include <windows.h>
#include "SGestao.h"

int main(int argc, char *argv[]) {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    streamsize ss = cout.precision();

    clock_t begin = clock();

#ifdef DEBUG_MODE
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

            //cout << "NumInterseções: " << SG->NumInterseccoes(new Vertice(112, 209, 319), new Vertice(121, 219, 311)) << endl;

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

        //cout << "NumInterseções: " << SG->NumInterseccoes(new Vertice(112, 209, 319), new Vertice(121, 219, 311)) << endl;

        cout << endl;

        if (!SG->RemoverModelo(argv[i]))
            cout << "Remoção Falhada!" << endl;

        SG->DisplayModelos();

        cout << endl;

        delete SG;
        cout << "--------------------------------------" << endl;
    }
#endif

    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

    cout << endl;

    cout << "Operation took " << elapsed_secs << " seconds to complete" << endl;

    return 1;
}