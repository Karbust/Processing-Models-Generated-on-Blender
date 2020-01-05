//
// Created by Karbust on 27/11/2019.
//

#include "XMLWriter.h"

XMLWriter::XMLWriter(string _ficheiro) {
    FICHEIRO.open(_ficheiro, ofstream::out);
}
XMLWriter::~XMLWriter() {
    FICHEIRO.close();
}
void XMLWriter::WriteElementString(string el, string valor){
    FICHEIRO << NumeroTABS(LTAG.size()) << "<" << el << ">" << valor << "</" << el << ">" << endl;
}
void XMLWriter::WriteStartElement(string el){
    FICHEIRO << NumeroTABS(LTAG.size()) << "<" << el << ">" << endl;
    LTAG.push_front(el);
}
void XMLWriter::WriteEndElement(){
    if(LTAG.empty()) return;
    FICHEIRO << NumeroTABS(LTAG.size()-1) <<  "</" << LTAG.front() << ">" << endl;
    LTAG.pop_front();
}
