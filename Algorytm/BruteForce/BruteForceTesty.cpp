//
// Created by Jakub Klawon on 03/11/2023.
//

#include <fstream>
#include "BruteForceTesty.h"
#include <cmath>


BruteForceTesty::BruteForceTesty(int wielkoscZestawu,int iloscOperacji,int iloscWynikow) {
    test(wielkoscZestawu,iloscOperacji,iloscWynikow);
}

void BruteForceTesty::test(int wielkoscZestawu,int iloscOperacji,int iloscWynikow){
    chrono::high_resolution_clock::time_point t1;
    chrono::high_resolution_clock::time_point t2;
    ofstream tablicaFile ("wynikiPomiarowBF.txt",ios::out|ios::app); //zrobic zabezpiczeenie zeby za kazdym razem generowal sie nowy plik

    double tablicaSrednich1[iloscWynikow];
    ::srand(time(NULL));

    BruteForce bf = BruteForce(wielkoscZestawu);
    for(int j=0;j<iloscWynikow;j++){

        double srednia = 0;
        for(int i=0;i<50;i++){
            bf = BruteForce(wielkoscZestawu);
            t1 = chrono::high_resolution_clock::now();
            bf.zbrutuj(0);
            t2 = chrono::high_resolution_clock::now();
            chrono::duration<double> time_span = std::chrono::duration_cast<chrono::duration<double>>(t2 - t1);
            srednia += std::chrono::duration<double>(time_span).count();
        }
        tablicaSrednich1[j] = srednia/50;

    }
    double srednia2 = 0;
    for(int i=0;i<iloscWynikow;i++) srednia2 += tablicaSrednich1[i];
    srednia2 /= iloscWynikow;
    if(tablicaFile.is_open()){
        tablicaFile<<"BF: ";
        for(int i=0;i<iloscWynikow;i++) tablicaFile<<tablicaSrednich1[i]*pow(10,9)<<" ";
        tablicaFile<<endl;
        tablicaFile<<srednia2 * pow(10,9)<<endl;
        tablicaFile<<wielkoscZestawu;
        tablicaFile<<endl<<endl;
    }
    cout<<"TESTY NA bf ZAKONCZONE SUKCESEM"<<endl;
}