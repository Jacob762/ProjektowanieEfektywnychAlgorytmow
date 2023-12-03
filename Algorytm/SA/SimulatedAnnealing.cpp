//
// Created by jakub on 11/19/2023.
//

#include <random>
#include "SimulatedAnnealing.h"

SimulatedAnnealing::SimulatedAnnealing(string nazwa, int start, double wspolczynnikChlodzenia, double tempKonc) {
    graf = Graf(nazwa);

    wynik = INT_MAX;
    rozGraf = graf.getRozmiar();

    sciezka = new int[rozGraf];
    trasa = lista();

    sciezka[0] = start;

    for(int i=1;i<rozGraf;i++){
        if(i==start) continue;
        sciezka[i] = i;
    }

    double to = tempStart();
    simulation(to,wspolczynnikChlodzenia,tempKonc);
}

int SimulatedAnnealing::getWynik() {
    return wynik;
}

void SimulatedAnnealing::getTrasa() {
    trasa.pokaz();
}

int SimulatedAnnealing::getSize() {
    return rozGraf;
}

SimulatedAnnealing::SimulatedAnnealing(int size) {
    graf = Graf(size);

    wynik = INT_MAX;
    rozGraf = graf.getRozmiar();

    sciezka = new int[rozGraf];
    trasa = lista();

    sciezka[0] = 1;

    for(int i=1;i<rozGraf;i++){
        sciezka[i] = i;
    }

    double to = tempStart();

}

double SimulatedAnnealing::tempStart() {
    double sol;
    double delta = 0;

    int a;
    int b;

    for(int i=0;i<10000;i++){
        nowaSciezka();
        a = obliczKoszt();
        nowaSciezka();
        b = obliczKoszt();
        delta += ::abs(a-b);
    }

    delta /= 10000;

    sol = ((-delta)/ ::log(0.99));
    return sol;
}

double SimulatedAnnealing::getTO() {
    return tempStart();
}

void SimulatedAnnealing::simulation(double tempPocz,double wspolczynnikChlodzenia, double tempKonc) {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> los(0.0, 1.0);

    lista tempTrasa = lista();
    for(int i=0;i<rozGraf;i++) tempTrasa.dodajNaKoniec(new listaElement(sciezka[i]));
    tempTrasa.dodajNaKoniec(new listaElement(sciezka[0]));

    int najWynik = wynik;
    double roznica = 0;
    int k=0;
    double temperatura = tempPocz;

    int nowaOdleglosc = 0;
    int aktualnaOdleglosc = najWynik;

    int staraOdleglosc = -1;
    int powtorka = 0;

    while(temperatura > tempKonc){

        nowaOdleglosc = obliczKoszt();
        roznica = nowaOdleglosc - aktualnaOdleglosc;

        if(roznica < 0 || exp(-roznica/(temperatura)) > los(gen)){
            nowyTemp(tempTrasa);
            aktualnaOdleglosc = nowaOdleglosc;
            staraOdleglosc = aktualnaOdleglosc;
        }

        if(aktualnaOdleglosc < najWynik){
            najWynik = aktualnaOdleglosc;
            nowaTrasa(tempTrasa);
        }

        nowaSciezka();
        k++;

        temperatura *= wspolczynnikChlodzenia;

    }
    wynik = najWynik;
}

int SimulatedAnnealing::obliczKoszt() {
    int res = 0;
    for(int i=0;i<rozGraf-1;i++){
        res += graf.grafMacierz[sciezka[i]][sciezka[i+1]];
    }
    res += graf.grafMacierz[sciezka[rozGraf-1]][sciezka[0]];
    return res;
}

void SimulatedAnnealing::nowaSciezka() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1, rozGraf-1);
    int indeks1 = distrib(gen);
    int indeks2 = distrib(gen);
    while(indeks1==indeks2) indeks2 = distrib(gen);
    int temp = sciezka[indeks1];
    sciezka[indeks1] = sciezka[indeks2];
    sciezka[indeks2] = temp;
}

void SimulatedAnnealing::nowyTemp(lista &tempTrasa){
    if(!tempTrasa.isEmpty()){for(int i=0;i<rozGraf+1;i++) tempTrasa.usunZPoczatku();}
    for(int i=0;i<rozGraf;i++) tempTrasa.dodajNaKoniec(new listaElement(sciezka[i]));
    tempTrasa.dodajNaKoniec(new listaElement(sciezka[0]+1));
}

void SimulatedAnnealing::nowaTrasa(lista &tempTrasa){
    if(!trasa.isEmpty()){for(int i=0;i<rozGraf+1;i++) trasa.usunZPoczatku();}
    for(int i=0;i<rozGraf;i++) {
        trasa.dodajNaKoniec(new listaElement(tempTrasa.getHead()+1));
        tempTrasa.usunZPoczatku();
    }
    trasa.dodajNaKoniec(new listaElement(sciezka[0]+1));
}