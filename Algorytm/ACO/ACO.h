//
// Created by Jakub Klawon on 26/12/2023.
//

#ifndef PEAPROJEKT1_ACO_H
#define PEAPROJEKT1_ACO_H


#include "../../Struktury/Graf/Graf.h"
#include "../../Struktury/Lista/lista.h"

class ACO {



    int wynik;
    Graf graf;

    int* sciezkaFinal;
    lista trasa;

    int rozGraf;


    double cal_start();
    double propability_cal();

    void greedy(int start, int *&sciezka);
    void ruletka(int n, double *&aktualneMiasta);
    int obliczKoszt(tablicaI sciezka);
    void nowaSciezka(tablicaI sciezka);
public:


    int getWynik();
    void getTrasa();
    int getSize();
    double getTO();
    void simulation();

    ACO(int size);
    void simulation(double alphaIN, double betaIN, double evaporationIN, double feromonIN);
    ACO(string nazwa, double alpha, double beta, double evaporation, double pheromone);

};


#endif //PEAPROJEKT1_ACO_H
