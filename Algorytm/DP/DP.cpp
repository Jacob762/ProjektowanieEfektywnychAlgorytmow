//
// Created by jakub on 10/12/2023.
//

#include "DP.h"

using namespace std;

DP::DP(string nazwa, int start) {
    graf = Graf(nazwa);
    wynik = INT_MAX;
    rozGraf = graf.getRozmiar();
    odwiedzone = new bool[rozGraf];
    for(int i=0;i<rozGraf;i++) odwiedzone[i] = false;
    odwiedzone[start-1] = true;
    st = start-1;
    trasa = "";
    wynik = DPuj(rozGraf,start-1,odwiedzone);
}

int DP::DPuj(int size,int start, bool maska[]) {
    int licz = 0;
    bool mask[rozGraf];
    int dane[size-1];
    for(int i=0;i<rozGraf;i++) {
        mask[i] = maska[i];
        if(mask[i]) licz++;
    }
    for(int i=0;i<size-1;i++) dane[i] = INT_MAX;
    tablica s = tablica();
    tablicaI k = tablicaI();
    mask[start] = true;
    if(size==1){
        return graf.grafMacierz[start][st];
    }

    for(int i=0;i<rozGraf;i++) {
        if(!mask[i]) {
            k.dodajNaKoniec(graf.grafMacierz[start][i] + DPuj(size-1,i,mask));
        }
    }

    return FindMin(k,start+1);

}

int DP::getWynik() {
    return wynik;
}

int DP::FindMin(tablicaI data, int start){
    if(data.rozmiar==1) return data.table[0];
    int min = INT_MAX;
    for(int i=0;i<data.rozmiar;i++){
        if(data.table[i] < min) {
            min = data.table[i];
        }
    }

    return min;
}

string DP::getTrasa() {
    return trasa;
}