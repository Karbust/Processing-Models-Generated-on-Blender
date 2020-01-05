//
// Created by Karbust on 04/01/2020.
//

#include "ArestasFaces.h"

ArestasFaces::ArestasFaces(){

}

ArestasFaces::~ArestasFaces(){
    for(auto & ArestaFace : A)
        delete ArestaFace;
}