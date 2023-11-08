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

    int wynik;
    Graf graf;

    int **memo;
    int **path;
    tablicaI sciezka;
    void trasa(int mask, int pos);
    void makePath(int start);

    int rozGraf;
    int st;

public:
    DP(string &nazwa, int start);
    int getWynik();
    void getTrasa();
    int getSize();
    DP(int size);
    int DPuj(int start, int maska);
};


#endif //PEAPROJEKT1_DP_H
