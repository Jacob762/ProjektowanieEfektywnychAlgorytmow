//
// Created by jakub on 1/15/2024.
//

#ifndef PEAPROJEKT1_ACOTESTY_H
#define PEAPROJEKT1_ACOTESTY_H

#include <iostream>
#include <chrono>
#include "ACO.h"
#include <fstream>

class ACOTesty {
private:
    void testOptymalne(string &plik, double alpha, double beta, double evap, double ph, int bestcost);
    double obliczBlad(int bestcost, int wynik);
    void testCzas(int wielkoscZestawu,  int iloscWynikow, double alpha, double beta, double evap, double ph, bool los, string &nazwa);
public:
    ACOTesty(int wielkoscZestawu, int iloscWynikow, double alpha, double beta, double evap, double ph);
    ACOTesty(int iloscWynikow, string &plik,  double alpha, double beta, double evap, double ph);
    ACOTesty(string &plik, int bestcost, double alpha, double beta, double evap, double ph);




};


#endif //PEAPROJEKT1_ACOTESTY_H
