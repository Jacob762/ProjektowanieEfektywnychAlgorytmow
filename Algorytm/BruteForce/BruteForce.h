//
// Created by jakub on 10/12/2023.
//

#ifndef PEAPROJEKT1_BRUTEFORCE_H
#define PEAPROJEKT1_BRUTEFORCE_H


#include "../../Struktury/Graf/Graf.h"
#include <string>

class BruteForce {
private:
    int ite;
    Graf graf;
    int sciezka;

    tablicaI wie;
    int** wyniki;
    int rozmiar;
    int rozGraf;

    void permute(string a, int l, int r, int k);
    void findPermutations(int *a, int n,int start);
public:
    BruteForce(string nazwa, int start);
    void getTrasa();
    int getSciezka();
    void zbrutuj(int start);
    BruteForce(int size);


};


#endif //PEAPROJEKT1_BRUTEFORCE_H
