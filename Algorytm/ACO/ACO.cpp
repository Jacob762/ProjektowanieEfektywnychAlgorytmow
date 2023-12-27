//
// Created by Jakub Klawon on 26/12/2023.
//

#include "ACO.h"

//
// Created by jakub on 11/19/2023.
//

#include <random>

ACO::ACO(string nazwa) {
    graf = Graf(nazwa);

    wynik = INT_MAX;
    rozGraf = graf.getRozmiar();

    sciezkaFinal = new int[rozGraf];
    trasa = lista();

    sciezkaFinal[0] = 0;

    for(int i=1;i<rozGraf;i++){
        sciezkaFinal[i] = i;
    }

    greedy(0,sciezkaFinal);
    simulation();
}

int ACO::getWynik() {
    return wynik;
}

void ACO::getTrasa() {
    for(int i=0;i<rozGraf;i++) cout<<sciezkaFinal[i]+1<<" ";
    cout<<sciezkaFinal[0]+1<<endl;
}

int ACO::getSize() {
    return rozGraf;
}

ACO::ACO(int size) {
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

double ACO::cal_start() {
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

    return delta;
}

double ACO::getTO() {
    return tempStart();
}

void ACO::simulation() {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> los(0.0, 1.0);

    lista tempTrasa = lista();
    int *sciezka = new int[rozGraf];
    double **feromony;
    double **desire;
    desire = new double * [rozGraf];
    feromony = new double * [rozGraf];
    double alpha = 1.0;
    double beta = 1.0;

    for(int i=0;i<rozGraf;i++){
        sciezka[i] = i;
        feromony[i] = new double [rozGraf];
        desire[i]= new double [rozGraf];
        for(int j=0;j<rozGraf;j++) {
            feromony[i][j] = 0.200;
            desire[i][j] = 200 * (1/(double)graf.grafMacierz[i][j]);
        }
    }

    greedy(0,sciezka);
    cout<<obliczKoszt(sciezka)<<" GREEDY"<<endl;
    for(int i=0;i<rozGraf;i++) cout<<sciezka[i]+1<<" ";
    cout<<sciezka[0]+1<<endl;

    int najWynik = wynik;
    double roznica = 0;
    int k=0;
    int staraOdleglosc = 0;
    int aktualnaOdleglosc = najWynik;
    int powtorka=0;
    int iteracje = 100;
    while(powtorka<iteracje){


        for(int i=0;i<rozGraf;i++){ //petla do znalezienia sciezki startujacej od kazego wierzcholka



        }

        aktualnaOdleglosc = najWynik;
        if(aktualnaOdleglosc==staraOdleglosc){
            powtorka++;
        } else powtorka=0;
        staraOdleglosc = aktualnaOdleglosc;
    }
    wynik = najWynik;
}

int ACO::obliczKoszt(int *&sciezka) {
    int res = 0;
    for(int i=0;i<rozGraf-1;i++){
        res += graf.grafMacierz[sciezka[i]][sciezka[i+1]];
    }
    res += graf.grafMacierz[sciezka[rozGraf-1]][sciezka[0]];
    return res;
}

void ACO::nowaSciezka(int *&sciezka) {
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

double ACO::propability_cal(){ //TO-DO:obliczanie prawdopodobienstwa przejscia do miasta
    double sol = 0;

    return sol;
}

void ACO::greedy(int start, int *&sciezka){
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