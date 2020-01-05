//
// Created by Karbust on 27/11/2019.
//

#ifndef PROJETOPOO_XMLWRITER_H
#define PROJETOPOO_XMLWRITER_H

#include <iostream>
#include <string>
#include <fstream>
#include <list>

using namespace std;

class XMLWriter {
    ofstream FICHEIRO;
    list<string> LTAG;

    static string NumeroTABS(int N) {
        string s;
        for(int i = 0;i < N; i++)
            s += "\t";
        return s;
    };

public:
    explicit XMLWriter(string _ficheiro);
    ~XMLWriter();
    void WriteElementString(string el, string valor);
    void WriteStartElement(string el);
    void WriteEndElement();
};


#endif //PROJETOPOO_XMLWRITER_H
