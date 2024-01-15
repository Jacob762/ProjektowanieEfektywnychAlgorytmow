//
// Created by jakub on 1/15/2024.
//

#include <valarray>
#include "ACOTesty.h"

using namespace std;

ACOTesty::ACOTesty(int wielkoscZestawu,int iloscWynikow,double alpha, double beta, double evap, double ph) {
    string n = "";
    testCzas(wielkoscZestawu,iloscWynikow,alpha,beta,evap,ph,false,n);
}

ACOTesty::ACOTesty(string &plik,  int bestcost,double alpha, double beta, double evap, double ph) {
    testOptymalne(plik,alpha,beta,evap,ph,bestcost);
}

ACOTesty::ACOTesty(int iloscWynikow, string &plik, double alpha, double beta, double evap, double ph){
    testCzas(0,iloscWynikow,alpha,beta,evap,ph, true,plik);
}

void ACOTesty::testCzas(int wielkoscZestawu,int iloscWynikow, double alpha,double beta, double evap, double ph, bool los, string &nazwa){
    chrono::high_resolution_clock::time_point t1;
    chrono::high_resolution_clock::time_point t2;
    string name;

    if(!los){
        name = "wynikiPomiarowACO.txt";
    }else{
        name = "wynikiPomiarowACOdoOptymalnych.txt";
    }

    ofstream tablicaFile (name,ios::out|ios::app);
    double tablicaSrednich1[iloscWynikow];

    ACO aco = ACO(5);



    int rozmiar = aco.getSize();
    double tstart = aco.getTO();

    for(int j=0;j<iloscWynikow;j++){
        double srednia = 0;
        for(int i=0;i<3;i++){
            if(!los){
                aco = ACO(wielkoscZestawu);
            } else{
                aco = ACO(nazwa,alpha,beta,evap,ph);
                rozmiar = aco.getSize();
            }
            tstart = aco.getTO();
            t1 = chrono::high_resolution_clock::now();
            aco.simulation(alpha,beta,evap,ph);
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
        tablicaFile<<srednia2 * pow(10,9)<<endl;
    }
    cout<<"Czasy zakonczone"<<endl;
    tablicaFile.close();
}

void ACOTesty::testOptymalne(string &plik, double alpha,double beta, double evap, double ph, int bestcost){
    chrono::high_resolution_clock::time_point t1;
    chrono::high_resolution_clock::time_point t2;
    ofstream File ("wynikiPomiarowOptymalnosciACO.txt",ios::out|ios::app);

    double tablicaSrednich1[5];
    int wynik;
    ACO aco = ACO(plik,alpha,beta,evap,ph);

    for(int i=0;i<5;i++){
        double srednia = 0;
        for(int j=0;j<3;j++){
            aco = ACO(plik,alpha,beta,evap,ph);
            wynik = aco.getWynik();

            srednia+=obliczBlad(bestcost,wynik);

        }
        tablicaSrednich1[i] = srednia/3;
    }

    double srednia2 = 0;
    for(int i=0;i<5;i++) srednia2 += tablicaSrednich1[i];
    srednia2 /= 5;

    if(File.is_open()){
        File<<srednia2<<endl;
    }

    cout<<"OPT zakonczone"<<endl;
    File.close();

}

double ACOTesty::obliczBlad(int bestcost, int wynik){
    return (((double)(wynik - bestcost))/(double) bestcost)*100.0;
}