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

    int obliczKoszt();
    void nowaSciezka();

    double tempStart();

    void nowyTemp(lista &tempTrasa);
    void nowaTrasa(lista &tempTrasa);
public:
    SimulatedAnnealing(string nazwa, int start,double wspolczynnikChlodzenia, double tempKonc);
    int getWynik();
    void getTrasa();
    int getSize();
    double getTO();
    SimulatedAnnealing(int size);
    void simulation(double tempPocz,double wspolczynnikChlodzenia, double tempKonc);
};


#endif //PEAPROJEKT1_SIMULATEDANNEALING_H
