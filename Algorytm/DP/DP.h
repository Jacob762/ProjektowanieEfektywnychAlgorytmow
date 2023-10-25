//
// Created by jakub on 10/12/2023.
//

#ifndef PEAPROJEKT1_DP_H
#define PEAPROJEKT1_DP_H

#include "../../Struktury/Graf/Graf.h"
#include "../../Struktury/TablicaI/tablicaI.h"
#include <string>

class DP {
private:
    int count;
    string trasa;
    int wynik;
    Graf graf;
    int rozGraf;
    int st;
    int DPuj(int size,int start, bool maska[]);
    bool *odwiedzone;
    int FindMin(tablicaI data, int start);
    tablica tr;
    tablica tempTr;
    void reconstructRoute();
    string wskazSciezke(string droga);
public:
    DP(string nazwa, int start);
    int getWynik();
    string getTrasa();
};


#endif //PEAPROJEKT1_DP_H
