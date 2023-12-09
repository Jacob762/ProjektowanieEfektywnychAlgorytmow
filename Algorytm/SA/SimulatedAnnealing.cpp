//
// Created by jakub on 11/19/2023.
//

#include <random>
#include "SimulatedAnnealing.h"

SimulatedAnnealing::SimulatedAnnealing(string nazwa, int start, double wspolczynnikChlodzenia, double tempKonc) {
    graf = Graf(nazwa);

    wynik = INT_MAX;
    rozGraf = graf.getRozmiar();

    sciezkaFinal = new int[rozGraf];
    trasa = lista();

    sciezkaFinal[0] = start;

    for(int i=1;i<rozGraf;i++){
        if(i==start) continue;
        sciezkaFinal[i] = i;
    }

    double to = tempStart();
    //greedy(start);
    simulation(to,wspolczynnikChlodzenia,tempKonc);
}

int SimulatedAnnealing::getWynik() {
    return wynik;
}

void SimulatedAnnealing::getTrasa() {
    for(int i=0;i<rozGraf;i++) cout<<sciezkaFinal[i]+1<<" ";
    cout<<sciezkaFinal[0]+1<<endl;
}

int SimulatedAnnealing::getSize() {
    return rozGraf;
}

SimulatedAnnealing::SimulatedAnnealing(int size) {
    graf = Graf(size);

    wynik = INT_MAX;
    rozGraf = graf.getRozmiar();

    sciezkaFinal = new int[rozGraf];
    trasa = lista();

    sciezkaFinal[0] = 1;

    for(int i=1;i<rozGraf;i++){
        sciezkaFinal[i] = i;
    }

    double to = tempStart();

}

double SimulatedAnnealing::tempStart() {
    double sol;
    double delta = 0;

    int a;
    int b;

    for(int i=0;i<10000;i++){
        nowaSciezka(sciezkaFinal);
        a = obliczKoszt(sciezkaFinal);
        nowaSciezka(sciezkaFinal);
        b = obliczKoszt(sciezkaFinal);
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
    int *sciezka = new int[rozGraf];
    sciezka[0] = 1;

    for(int i=1;i<rozGraf;i++){
        sciezka[i] = i;
    }

    greedy(0,sciezka);
    cout<<obliczKoszt(sciezka)<<" GREEDY"<<endl;
    for(int i=0;i<rozGraf;i++) cout<<sciezka[i]+1<<" ";
    cout<<sciezka[0]+1<<endl;

    int najWynik = wynik;
    double roznica = 0;
    int k=0;
    double temperatura = tempPocz;
    int nowaOdleglosc = 0;
    int aktualnaOdleglosc = najWynik;

    while(temperatura > tempKonc){

        nowaOdleglosc = obliczKoszt(sciezka);
        roznica = nowaOdleglosc - aktualnaOdleglosc;

        if(roznica < 0 || exp(-roznica/(temperatura)) > los(gen)){
            nowyTemp(tempTrasa,sciezka);
            aktualnaOdleglosc = nowaOdleglosc;

            if(aktualnaOdleglosc-najWynik < najWynik/4){
                int powtorka = 0;
                int staraOdleglosc = aktualnaOdleglosc;
                int *tempSciezka = new int [rozGraf];
                for(int i=0;i<rozGraf;i++) tempSciezka[i] = sciezka[i];
                while(powtorka<50){
                    nowaSciezka(tempSciezka);
                    int wyn = obliczKoszt(tempSciezka);
                    if(wyn < staraOdleglosc) staraOdleglosc = wyn;
                    if(staraOdleglosc==aktualnaOdleglosc){
                        powtorka++;
                    } else {
                        for(int i=0;i<rozGraf;i++) sciezka[i] = tempSciezka[i];
                        aktualnaOdleglosc = staraOdleglosc;
                        powtorka = 0;
                    }
                    for(int i=0;i<rozGraf;i++) tempSciezka[i] = sciezka[i];
                }
            }
        }

        if(aktualnaOdleglosc < najWynik){
            najWynik = aktualnaOdleglosc;
            nowaTrasa(tempTrasa,sciezka);
            for(int i=0;i<rozGraf;i++) sciezkaFinal[i] = sciezka[i];
        }

        for(int i=0;i<rozGraf;i++) sciezka[i] = sciezkaFinal[i];

        k++;
        nowaSciezka(sciezka);
        temperatura *= wspolczynnikChlodzenia;

    }
    wynik = najWynik;
}

int SimulatedAnnealing::obliczKoszt(int *&sciezka) {
    int res = 0;
    for(int i=0;i<rozGraf-1;i++){
        res += graf.grafMacierz[sciezka[i]][sciezka[i+1]];
    }
    res += graf.grafMacierz[sciezka[rozGraf-1]][sciezka[0]];
    return res;
}

void SimulatedAnnealing::nowaSciezka(int *&sciezka) {
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

void SimulatedAnnealing::nowyTemp(lista &tempTrasa, int *&sciezka){
    if(!tempTrasa.isEmpty()){for(int i=0;i<rozGraf+1;i++) tempTrasa.usunZPoczatku();}
    for(int i=0;i<rozGraf;i++) tempTrasa.dodajNaKoniec(new listaElement(sciezka[i]));
    tempTrasa.dodajNaKoniec(new listaElement(sciezka[0]+1));
}

void SimulatedAnnealing::nowaTrasa(lista &tempTrasa, int *&sciezka){
    if(!trasa.isEmpty()){for(int i=0;i<rozGraf+1;i++) trasa.usunZPoczatku();}
    for(int i=0;i<rozGraf;i++) {
        trasa.dodajNaKoniec(new listaElement(tempTrasa.getHead()+1));
        tempTrasa.usunZPoczatku();
    }
    trasa.dodajNaKoniec(new listaElement(sciezka[0]+1));
}

void SimulatedAnnealing::greedy(int start, int *&sciezka){
    int tempTab[rozGraf];
    bool odwiedzone[rozGraf];

    for(int i=0;i<rozGraf;i++) odwiedzone[i] = false;

    int k = 0;
    int i = start;
    tempTab[0] = start;
    while(k < rozGraf){
        int max = INT_MAX;
        int tempJ = -1;
        odwiedzone[i] = true;
        for(int j=0;j<rozGraf;j++){
            if(graf.grafMacierz[i][j]<max && !odwiedzone[j]){
                max = graf.grafMacierz[i][j];
                tempJ = j;
            }
        }
        i = tempJ;
        k++;
        tempTab[k] = tempJ;
    }

    for(int n=0;n<rozGraf;n++) sciezka[n] = tempTab[n];
}