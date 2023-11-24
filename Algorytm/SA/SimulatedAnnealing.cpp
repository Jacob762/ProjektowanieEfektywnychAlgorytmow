//
// Created by jakub on 11/19/2023.
//

#include <random>
#include "SimulatedAnnealing.h"

SimulatedAnnealing::SimulatedAnnealing(string nazwa, int start, double tempPocz,double wspolczynnikChlodzenia) {
    graf = Graf(nazwa);

    wynik = INT_MAX;
    rozGraf = graf.getRozmiar();
    st = 0;

    sciezka = new int[rozGraf];
    trasa = lista();

    sciezka[0] = start;

    for(int i=1;i<rozGraf;i++){
        if(i==start) continue;
        sciezka[i] = i;
    }

    simulation(start,tempPocz,wspolczynnikChlodzenia);
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


}

void SimulatedAnnealing::simulation(int start,double tempPocz,double wspolczynnikChlodzenia) {
    random_device rd;  // Will be used to obtain a seed for the random number engine
    mt19937 gen(rd());
    uniform_real_distribution<double> los(0.0, 1.0);
    lista tempTrasa = lista();
    int najWynik = wynik;
    double roznica = 0;
    int k=0;
    double temp = tempPocz;
    double tempKonc = 0.1;
    int nowaOdleglosc = 0;
    int aktualnaOdleglosc = najWynik;
    while(temp > tempKonc ){
        nowaOdleglosc = obliczKoszt();
        roznica = nowaOdleglosc - aktualnaOdleglosc;
        if(roznica < 0 || exp(-roznica/temp) > los(gen)){
            if(!tempTrasa.isEmpty()){
                for(int i=0;i<rozGraf+1;i++) tempTrasa.usunZPoczatku();
                for(int i=0;i<rozGraf;i++) tempTrasa.dodajNaKoniec(new listaElement(sciezka[i]));
                tempTrasa.dodajNaKoniec(new listaElement(sciezka[0]+1));
            } else{
                for(int i=0;i<rozGraf;i++) tempTrasa.dodajNaKoniec(new listaElement(sciezka[i]));
                tempTrasa.dodajNaKoniec(new listaElement(sciezka[0]+1));
            }
            aktualnaOdleglosc = nowaOdleglosc;
           // cout<<aktualnaOdleglosc<<"  "<<temp<<endl;
        } else{
            nowaOdleglosc = aktualnaOdleglosc;
            //
        }
        if(aktualnaOdleglosc < najWynik){
            najWynik = aktualnaOdleglosc;
            if(!trasa.isEmpty()){
                for(int i=0;i<rozGraf+1;i++) trasa.usunZPoczatku();
                for(int i=0;i<rozGraf;i++) {
                    trasa.dodajNaKoniec(new listaElement(tempTrasa.getHead()));
                    tempTrasa.usunZPoczatku();
                }
                trasa.dodajNaKoniec(new listaElement(sciezka[0]+1));
            } else{
                for(int i=0;i<rozGraf;i++) {
                    trasa.dodajNaKoniec(new listaElement(tempTrasa.getHead()));
                    tempTrasa.usunZPoczatku();
                }
                trasa.dodajNaKoniec(new listaElement(sciezka[0]+1));
            }
        }
        nowaSciezka();
        k++;
        temp *= wspolczynnikChlodzenia;
    }
    wynik = najWynik;
    if(!trasa.isEmpty()){
        for(int i=0;i<rozGraf+1;i++) trasa.usunZPoczatku();
        for(int i=0;i<rozGraf;i++) {
            trasa.dodajNaKoniec(new listaElement(tempTrasa.getHead()+1));
            tempTrasa.usunZPoczatku();
        }
        trasa.dodajNaKoniec(new listaElement(sciezka[0]+1));
    } else{
        for(int i=0;i<rozGraf;i++) {
            trasa.dodajNaKoniec(new listaElement(tempTrasa.getHead()+1));
            tempTrasa.usunZPoczatku();
        }
        trasa.dodajNaKoniec(new listaElement(sciezka[0]+1));
    }
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
    std::random_device rd;  // a seed source for the random number engine
    std::mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> distrib(1, rozGraf-1);
    int indeks1 = distrib(gen);
    int indeks2 = distrib(gen);
    while(indeks1==indeks2) indeks2 = distrib(gen);
    int temp = sciezka[indeks1];
    sciezka[indeks1] = sciezka[indeks2];
    sciezka[indeks2] = temp;

}
