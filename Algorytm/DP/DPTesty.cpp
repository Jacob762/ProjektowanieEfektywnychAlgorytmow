//
// Created by Jakub Klawon on 03/11/2023.
//

#include "DPTesty.h"

#include <cmath>

DPTesty::DPTesty(int wielkoscZestawu,int iloscOperacji,int iloscWynikow) {
    test(wielkoscZestawu,iloscOperacji,iloscWynikow);
}

void DPTesty::test(int wielkoscZestawu,int iloscOperacji,int iloscWynikow){
    chrono::high_resolution_clock::time_point t1;
    chrono::high_resolution_clock::time_point t2;
    ofstream tablicaFile ("wynikiPomiarowDP.txt",ios::out|ios::app);

    double tablicaSrednich1[iloscWynikow];
    ::srand(time(NULL));
    double tablicaCzasow[iloscOperacji];


    DP dp = DP(wielkoscZestawu);
    int rozmiar = dp.getSize();

    bool mask[rozmiar];
    for(int i=0;i<rozmiar-1;i++) mask[i] = false;
    mask[rozmiar-1] = true;

    for(int j=0;j<iloscWynikow;j++){
        double srednia = 0;
        for(int i=0;i<50;i++){
            dp = DP(wielkoscZestawu);
            t1 = chrono::high_resolution_clock::now();
            dp.DPuj(0,0);
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
        tablicaFile<<"DP: ";
        for(int i=0;i<iloscWynikow;i++) tablicaFile<<tablicaSrednich1[i]*pow(10,9)<<" ";
        tablicaFile<<endl;
        tablicaFile<<srednia2 * pow(10,9)<<endl;
        tablicaFile<<wielkoscZestawu;
        tablicaFile<<endl<<endl;
    }
    cout<<"TESTY NA dp ZAKONCZONE SUKCESEM"<<endl;
}