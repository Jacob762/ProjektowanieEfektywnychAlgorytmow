//
// Created by jakub on 12/1/2023.
//

#include <cstdlib>
#include "SATesty.h"


SATesty::SATesty(int wielkoscZestawu,int iloscOperacji,int iloscWynikow,double wspolczynnik) {
    string n = "";
    testCzas(wielkoscZestawu,iloscOperacji,iloscWynikow,wspolczynnik,false,n);
}

SATesty::SATesty(string &plik, double wspolczynnik, int bestcost) {
    testOptymalne(plik,wspolczynnik,bestcost);
}

SATesty::SATesty(string &plik, int iloscOperacji,int iloscWynikow,double wspolczynnik){
    testCzas(0,iloscOperacji,iloscWynikow,wspolczynnik, true,plik);
}

void SATesty::testCzas(int wielkoscZestawu,int iloscOperacji,int iloscWynikow, double wspolczynnik, bool los, string &nazwa){
    chrono::high_resolution_clock::time_point t1;
    chrono::high_resolution_clock::time_point t2;
    string name;

    if(!los){
        name = "wynikiPomiarowSA.txt";
    }else{
        name = "wynikiPomiarowSAdoOptymalnych.txt";
    }

    ofstream tablicaFile (name,ios::out|ios::app);
    double tablicaSrednich1[iloscWynikow];

    SimulatedAnnealing SA = SimulatedAnnealing(5);



    int rozmiar = SA.getSize();
    double tstart = SA.getTO();

    for(int j=0;j<iloscWynikow;j++){
        double srednia = 0;
        for(int i=0;i<10;i++){
            if(!los){
                SA = SimulatedAnnealing(wielkoscZestawu);
            } else{
                SA = SimulatedAnnealing(nazwa,1,wspolczynnik,0.001);
                rozmiar = SA.getSize();
            }
            tstart = SA.getTO();
            t1 = chrono::high_resolution_clock::now();
            SA.simulation(tstart,wspolczynnik,0.001);
            t2 = chrono::high_resolution_clock::now();
            chrono::duration<double> time_span = std::chrono::duration_cast<chrono::duration<double>>(t2 - t1);
            srednia += std::chrono::duration<double>(time_span).count();
        }
        tablicaSrednich1[j] = srednia/10;
    }
    double srednia2 = 0;
    for(int i=0;i<iloscWynikow;i++) srednia2 += tablicaSrednich1[i];
    srednia2 /= iloscWynikow;
    if(tablicaFile.is_open()){
        tablicaFile<<"SA: "<<wspolczynnik<<endl;
        for(int i=0;i<iloscWynikow;i++) tablicaFile<<tablicaSrednich1[i]*pow(10,9)<<" ";
        tablicaFile<<endl;
        tablicaFile<<srednia2 * pow(10,9)<<endl;
        tablicaFile<<rozmiar;
        tablicaFile<<endl<<endl;
    }
    cout<<"Czasy zakonczone"<<endl;
    tablicaFile.close();
}

void SATesty::testOptymalne(string &plik, double wspolczynnik, int bestcost){
    chrono::high_resolution_clock::time_point t1;
    chrono::high_resolution_clock::time_point t2;
    ofstream File ("wynikiPomiarowOptymalnosciSA.txt",ios::out|ios::app);

    double tablicaSrednich1[5];
    int wynik;
    SimulatedAnnealing sa = SimulatedAnnealing(plik,1,wspolczynnik,0.001);

    for(int i=0;i<5;i++){
        double srednia = 0;
        for(int j=0;j<3;j++){
            sa = SimulatedAnnealing(plik,1,wspolczynnik,0.001);
            wynik = sa.getWynik();

            srednia+=obliczBlad(bestcost,wynik);

        }
        tablicaSrednich1[i] = srednia/3;
    }

    double srednia2 = 0;
    for(int i=0;i<5;i++) srednia2 += tablicaSrednich1[i];
    srednia2 /= 5;

    if(File.is_open()){
        File<<"SA: "<<wspolczynnik<<endl;
        for(int i=0;i<5;i++) File<<tablicaSrednich1[i]<<" ";
        File<<endl;
        File<<srednia2<<endl;
        File<<plik<<endl;
        File<<sa.getSize();
        File<<endl<<endl;
    }

}

double SATesty::obliczBlad(int bestcost, int wynik){
    return (((double)(wynik - bestcost))/(double) bestcost)*100.0;
}