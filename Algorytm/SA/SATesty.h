//
// Created by jakub on 12/1/2023.
//

#ifndef PEAPROJEKT1_SATESTY_H
#define PEAPROJEKT1_SATESTY_H

#include <fstream>
#include <iostream>
#include <chrono>
#include "SimulatedAnnealing.h"

class SATesty {

private:

    void testOptymalne(string &plik, double wspolczynnik, int bestcost);
    double obliczBlad(int bestcost, int wynik);
    void testCzas(int wielkoscZestawu, int iloscOperacji, int iloscWynikow,double wspolczynnik,bool los, string &nazwa);
public:
    SATesty(int wielkoscZestawu, int iloscOperacji, int iloscWynikow,double wspolczynnik);
    SATesty(string &plik, double wspolczynnik, int bestcost);
    SATesty(string &plik, int iloscOperacji, int iloscWynikow, double wspolczynnik);

};


#endif //PEAPROJEKT1_SATESTY_H
