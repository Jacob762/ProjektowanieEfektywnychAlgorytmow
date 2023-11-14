//
// Created by jakub on 10/12/2023.
//

#include <cmath>
#include <algorithm>
#include "BruteForce.h"

using namespace std;

BruteForce::BruteForce(string nazwa, int start){
    graf = Graf(nazwa);
    rozGraf = graf.getRozmiar();
    sciezka = INT_MAX;
    zbrutuj(start);
}

BruteForce::BruteForce(int size) {
    graf = Graf(size);
    rozGraf = graf.getRozmiar();
}

void BruteForce::zbrutuj(int start) {

    wie = tablicaI();

    ite = 0;
    int tab[rozGraf];

    for(int i=0;i<rozGraf;i++) {
        tab[i] = i;
    }

    int a,b; //a,b - zmienne do iterowania po permutacjach

    findPermutations(tab,rozGraf,start-1);


    while(ite != rozmiar){
        int tempSciezka = 0;
        for(int i=0;i<rozGraf-1;i++){
            a = (int) wyniki[ite][i];
            b = (int) wyniki[ite][i+1];
            tempSciezka+=graf.grafMacierz[a][b];
        }
        tempSciezka += graf.grafMacierz[b][start-1];
        if(tempSciezka<sciezka) {
            for(int i=0;i<rozGraf;i++) wie.usunZPoczatku();
            wie.usunZPoczatku();
            sciezka = tempSciezka;
            for(int i=0;i<rozGraf;i++) wie.dodajNaKoniec(wyniki[ite][i]+1);
            wie.dodajNaKoniec(start);
        }
        ite++;
    }
}

int silnia(int n){
    int result = 1;
    for(int i=1;i<=n;i++) result*=i;
    return result;
}

void BruteForce::findPermutations(int a[], int n,int start)
{
    rozmiar = silnia(rozGraf-1);
    wyniki = new int*[rozmiar];
    for(int i=0;i<rozmiar;i++) {
        wyniki[i] = new int[rozGraf];
        for(int j=0;j<rozGraf;j++) wyniki[i][j] = -1;
    }


    int iterator = 0;

    do {
        if(a[0]!=start) continue;

        for(int i=0;i<rozGraf;i++){
            wyniki[iterator][i] = a[i];
        }
        iterator++;
    } while (next_permutation(a, a + n));
}

void BruteForce::permute(string a, int l, int r, int k)
{
    if(wie.table[0]!=k) return;
    if (l == r){
        //wyniki.push_back(wie);
        //permutacje.dodajNaKoniec(a);
    } else {
        for (int i = l; i <= r; i++) {
            swap(wie.table[l], wie.table[i]);

            permute(a, l + 1, r,k);

            swap(wie.table[l], wie.table[i]);
        }
    }
}

void BruteForce::getTrasa() {
    wie.pokaz();
}

int BruteForce::getSciezka() {
    return sciezka;
}