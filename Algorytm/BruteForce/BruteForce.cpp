//
// Created by jakub on 10/12/2023.
//

#include <cmath>
#include "BruteForce.h"

using namespace std;

BruteForce::BruteForce(string nazwa, int start){
    graf = Graf(nazwa);
    graf.pokaz();
    rozGraf = graf.getRozmiar();
    sciezka = INT_MAX;
    zbrutuj(start);
}

BruteForce::BruteForce(int size) {
    graf = Graf(size);
    rozGraf = graf.getRozmiar();
}

void BruteForce::zbrutuj(int start) {
    string wierz = "";
    for(int i=1;i<rozGraf+1;i++) wierz+= to_string(i);

    int a,b; //a,b - zmienne do iterowania po permutacjach

    char go =  start + 48;
    permute(wierz,0,rozGraf-1,go);

    while(permutacje.rozmiar!=0){
        int tempSciezka = 0;
        for(int i=0;i<rozGraf-1;i++){
            a = (int) permutacje.table[0][i] - 49;
            b = (int) permutacje.table[0][i+1] - 49;
            tempSciezka+=graf.grafMacierz[a][b];
        }
        tempSciezka += graf.grafMacierz[b][start-1];
        if(tempSciezka<sciezka) {
            sciezka = tempSciezka;
            trasa = permutacje.table[0];
            trasa += to_string(start);
        }
        permutacje.usunZPoczatku();
    }
}

void BruteForce::permute(string a, int l, int r, char k)
{
    if (l == r){
        if(a[0]!=k) return;
        permutacje.dodajNaKoniec(a);
    } else {
        for (int i = l; i <= r; i++) {
            swap(a[l], a[i]);

            permute(a, l + 1, r,k);

            swap(a[l], a[i]);
        }
    }
}

string BruteForce::getTrasa() {
    return trasa;
}

int BruteForce::getSciezka() {
    return sciezka;
}