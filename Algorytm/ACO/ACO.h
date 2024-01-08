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

    double tempStart();

    int obliczKoszt(int *&sciezka);
    void nowaSciezka(int *&sciezka);
    double cal_start();
    double propability_cal();
    double ruletka(double *&prawdopodobienstwo,int n);
    void greedy(int start, int *&sciezka);
public:


    int getWynik();
    void getTrasa();
    int getSize();
    double getTO();
    void simulation();

    ACO(string nazwa);
    ACO(int size);


    void ruletka(double *&prawdopodobienstwo, int n, double *&aktualneMiasta);
};


#endif //PEAPROJEKT1_ACO_H
