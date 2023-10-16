//
// Created by jakub on 5/5/2023.
//

#include "Graf.h"
#include <iostream>
#include <fstream>


using namespace std;

Graf::Graf() {
    rozmiar = 0;
}

Graf::Graf(string nazwa) {
    rozmiar = 0;
    dodajMacierz(nazwa);
}

int Graf::getRozmiar() {
    return rozmiar;
}

void Graf::dodajMacierz(string nazwa) {
    string line;
    fstream file(nazwa,std::ios_base::in);
    if (!file.is_open()) {
        cout<<"ERROR"<<endl;
        return;
    }
    while(true){
        file >> line;
        if(line.substr(0,9) == "DIMENSION") {
            file >> rozmiar;
            break;
        }
    }

    grafMacierz = new int*[rozmiar];
    for(int i=0;i<rozmiar;i++){
        grafMacierz[i] = new int [rozmiar];
        for(int j=0;j<rozmiar;j++) grafMacierz[i][j] = -1;
    }
    for(int i=0;i<rozmiar;i++){
        for(int j=0;j<rozmiar;j++){
            file >> grafMacierz[i][j];
        }
    }
}

void Graf::pokaz() {
    cout<<endl;
    for(int i=0;i<rozmiar;i++){
        for(int j=0;j<rozmiar;j++) cout<<grafMacierz[i][j]<<"  ";
        cout<<endl;
    }
    cout<<endl;
    cout<<"   ";
    cout<<"\n\n";
}

