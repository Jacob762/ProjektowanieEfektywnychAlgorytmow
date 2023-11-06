//
// Created by Jakub Klawon on 03/11/2023.
//

#ifndef PEAPROJEKT1_DPTESTY_H
#define PEAPROJEKT1_DPTESTY_H

#include <iostream>
#include <chrono>
#include "DP.h"
#include <fstream>


class DPTesty {
private:
    void test(int wielkoscZestawu,int iloscOperacji,int iloscWynikow);
public:
    DPTesty(int wielkoscZestawu,int iloscOperacji,int iloscWynikow);
};


#endif //PEAPROJEKT1_DPTESTY_H
