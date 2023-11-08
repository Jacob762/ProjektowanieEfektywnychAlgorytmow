//
// Created by jakub on 10/12/2023.
//

#include "DP.h"

using namespace std;

DP::DP(string &nazwa, int start) { //konstruktor do wywolania
    graf = Graf(nazwa);

    wynik = INT_MAX;
    rozGraf = graf.getRozmiar();
    st = 0;


    memo = new int*[1 << rozGraf];
    path = new int*[1 << rozGraf];
    for(int i=0;i< 1<<rozGraf;i++) {
        path[i] = new int [rozGraf];
        memo[i] = new int [rozGraf];
        for(int k=0;k<rozGraf;k++) {
            path[i][k]= -1;
            memo[i][k]= -1;
        }
    }


    wynik = DPuj(0,0);
    sciezka = tablicaI();
    trasa(1,0);
    makePath(start);

}


DP::DP(int size){ //konstruktor do prowadzenia badan
    st = 0;
    graf = Graf(size);
    rozGraf = graf.getRozmiar();
    path = new int*[1 << rozGraf];
    memo = new int*[1 << rozGraf];
    for(int i=0;i< 1<<rozGraf;i++) {
        path[i] = new int [rozGraf];
        memo[i] = new int [rozGraf];
        for(int k=0;k<rozGraf;k++) {
            path[i][k]= -1;
            memo[i][k]= -1;
        }
    }
}

int DP::getSize() {
    return rozGraf;
}


int DP::DPuj(int start, int maska) {

    if(maska == (1 << rozGraf) - 1){
        return graf.grafMacierz[start][st];
    }
    //zwracanie zapamietywanego wyniku obliczonej juz trasy
    if(memo[maska][start] != -1){
        return memo[maska][start];
    }

    int next = -1;
    int res = INT_MAX;

    for(int i=0;i<rozGraf;i++) {
        if(!(maska & (1 << i))) {
            int nextmask = maska | (1<<i);
            int cost = graf.grafMacierz[start][i] + DPuj(i,nextmask);
            if(cost<res){
                res = cost;
                next = i;
            }
        }
    }

    path[maska][start] = next;

    return memo[maska][start] = res;

}

void DP::trasa(int mask, int pos) {
    if (mask == (1 << rozGraf) - 1) {
        sciezka.dodajNaKoniec(pos+1);
        return;
    }
    int next = path[mask][pos];
    sciezka.dodajNaKoniec(pos+1);
    trasa(mask | (1 << next), next);
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