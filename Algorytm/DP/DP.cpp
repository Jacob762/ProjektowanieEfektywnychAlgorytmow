//
// Created by jakub on 10/12/2023.
//

#include "DP.h"

using namespace std;

DP::DP(string nazwa, int start) {
    graf = Graf(nazwa);

    wynik = INT_MAX;
    rozGraf = graf.getRozmiar();
    st = start-1;

    path = new int*[1 << rozGraf];
    for(int i=0;i< 1<<rozGraf;i++) {
        path[i] = new int [rozGraf];
        for(int k=0;k<rozGraf;k++) path[i][k]= -1;
    }



    wynik = DPuj(start-1,0);
    sciezka = tablicaI();
    //getPath(1,0);
    //makePath(start);
}


DP::DP(int size){
    graf = Graf(size);
    rozGraf = graf.getRozmiar();
    path = new int*[1 << rozGraf];
    for(int i=0;i< 1<<rozGraf;i++) {
        path[i] = new int [rozGraf];
        for(int k=0;k<rozGraf;k++) path[i][k]= -1;
    }
}

int DP::getSize() {
    return rozGraf;
}


int DP::DPuj(int start, int maska) {

    if(maska == (1 << rozGraf) - 1){
        return graf.grafMacierz[start][st];
    }

    int next = -1;
    int res = INT_MAX;

    for(int i=0;i<rozGraf;i++) {
        if(!(maska & (1 << i))) {
            int nowaMaska = maska | (1<<i);
            int cost = graf.grafMacierz[start][i] + DPuj(i,nowaMaska);
            if(cost<res){
                res = cost;
                next = i;
            }
        }
    }

    path[maska][start] = next;

    return res;

}

void DP::getPath(int mask, int pos) {
    if (mask == (1 << rozGraf) - 1) {
        sciezka.dodajNaKoniec(pos+1);
        return;
    }
    int next = path[mask][pos];
    sciezka.dodajNaKoniec(pos+1);
    getPath(mask | (1 << next), next);
}

void DP::makePath(int start){
    while(true){
        if(sciezka.table[0]==start) {
            sciezka.dodajNaKoniec(start);
            break;
        }
        sciezka.dodajNaKoniec(sciezka.table[0]);
        sciezka.usunZPoczatku();
    }
}

int DP::getWynik() {
    return wynik;
}

void DP::getTrasa() {
    sciezka.pokaz();
}