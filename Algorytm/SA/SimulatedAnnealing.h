//
// Created by jakub on 11/19/2023.
//

#ifndef PEAPROJEKT1_SIMULATEDANNEALING_H
#define PEAPROJEKT1_SIMULATEDANNEALING_H

#include "../../Struktury/Graf/Graf.h"
#include <string>
#include <cmath>
#include "../../Struktury/Lista/lista.h"

class SimulatedAnnealing {
private:

    int wynik;
    Graf graf;

    int* sciezka;
    lista trasa;

    int rozGraf;
    int st;

    int obliczKoszt();
    void nowaSciezka();

public:
    SimulatedAnnealing(string nazwa, int start,double tempPocz,double wspolczynnikChlodzenia);
    int getWynik();
    void getTrasa();
    int getSize();
    SimulatedAnnealing(int size);
    void simulation(int start,double tempPocz,double wspolczynnikChlodzenia);
};


#endif //PEAPROJEKT1_SIMULATEDANNEALING_H
