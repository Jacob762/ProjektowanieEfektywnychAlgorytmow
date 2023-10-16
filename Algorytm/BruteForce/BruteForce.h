//
// Created by jakub on 10/12/2023.
//

#ifndef PEAPROJEKT1_BRUTEFORCE_H
#define PEAPROJEKT1_BRUTEFORCE_H

#include "../../Struktury/Graf/Graf.h"
#include <string>

class BruteForce {
private:
    Graf graf;
    int sciezka;
    string trasa;
    tablica permutacje;
    void zbrutuj(int start);
    int rozGraf;
    void permute(string a, int l, int r, char k);
public:
    BruteForce(string nazwa, int start);
    string getTrasa();
    int getSciezka();


};


#endif //PEAPROJEKT1_BRUTEFORCE_H
