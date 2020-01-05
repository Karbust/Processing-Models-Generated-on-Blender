#include <iostream>
#include <ctime>
#include <windows.h>
#include <vld.h>
#include "SGestao.h"

int main(int argc, char *argv[]) {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    clock_t begin = clock();

    //auto *SG = new SGestao();

    int j = 0;

    for (int i = 1; i < argc; ++i) {
        while(j != 1000){
        auto *SG = new SGestao();
        cout << "--------------------------------------" << endl;
        cout << argv[i] << "\n" << endl;
        if(!SG->Load(argv[i]))
            continue;
        cout << "Vértices (Func Contar): " << SG->Contar(VERTICES) << endl;
        cout << "Faces (Func Contar): " << SG->Contar(FACES) << endl;
        cout << "Arestas (Func Contar): " << SG->Contar(ARESTAS) << endl;
        cout << fixed << "Area: " << SG->AreaModelo(argv[i]) << endl;
        cout << "Memória: " << SG->Memoria() << endl;
        cout << "Memória2: " << sizeof(SG) << endl;

        cout << fixed << "Face Maior Área: " << SG->FaceMaiorArea(argv[i])->ReturnfID() << " com " << SG->FaceMaiorArea(argv[i])->ReturnArea() << endl;

        Vertice Pmin = Vertice(0, 0, 0), Pmax = Vertice(0, 0, 0);

        SG->Envolvente(argv[i], Pmin, Pmax);

        cout << fixed << "Envolvente: " << "[(" << Pmin.ReturnVX() << ", " << Pmin.ReturnVY() << ", " << Pmin.ReturnVZ() << ") , (" << Pmax.ReturnVX() << ", " << Pmax.ReturnVY() << ", " << Pmax.ReturnVZ() << ")]" << endl;

        //SG->EscreverXML(argv[i], string(argv[i]) + ".xml");

        cout << endl;

        SG->DisplayModelos();

        cout << endl;

        cout << "Face Maior Curvatura: " << SG->FaceMaiorCurvatura(argv[i])->ReturnfID() + 1 << endl;

        cout << endl;

        //cout << "NumInterseções: " << SG->NumInterseccoes(new Vertice(112, 209, 319), new Vertice(121, 219, 311)) << endl;

        cout << endl;

        if(!SG->RemoverModelo(argv[i]))
            cout << "Remoção Falhada!" << endl;

        SG->DisplayModelos();

        cout << endl;

        delete SG;
        cout << "--------------------------------------" << endl;
        j++;
        }
    }

    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

    cout << endl;

    cout << "Operation took " << elapsed_secs << " seconds to complete" << endl;

    return 1;
}