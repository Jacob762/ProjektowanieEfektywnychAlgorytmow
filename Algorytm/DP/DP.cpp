//
// Created by jakub on 10/12/2023.
//

#include "DP.h"

using namespace std;

DP::DP(string nazwa, int start) {
    count = 0;
    graf = Graf(nazwa);
    //tablica = tablicaI();
    wynik = INT_MAX;
    rozGraf = graf.getRozmiar();
    odwiedzone = new bool[rozGraf];
    odwiedzone[start-1] = true;
    st = start-1;
    tr = tablica();
    tempTr = tablica();
    trasa = "";
    wynik = DPuj(rozGraf,start-1,odwiedzone);
    tr.pokaz();
    tempTr.pokaz();
    reconstructRoute();
}

int DP::DPuj(int size,int start, bool maska[]) {
    int licz = 0;
    bool mask[rozGraf];
    int dane[size-1];
    for(int i=0;i<rozGraf;i++) {
        mask[i] = maska[i];
        if(mask[i]) licz++;
    }
    for(int i=0;i<size-1;i++) dane[i] = INT_MAX;
    tablicaI k = tablicaI();
    mask[start] = true;
    if(size==1){
        trasa+=to_string(start+1);
        return graf.grafMacierz[start][st];
    }

    for(int i=0;i<rozGraf;i++) {
        if(!mask[i]) {
            k.dodajNaKoniec(graf.grafMacierz[start][i] + DPuj(size-1,i,mask));
            trasa+=to_string(start+1);
            tr.dodajNaKoniec(trasa);
            trasa = "";
        }
    }

    return FindMin(k,start+1);

}

void DP::reconstructRoute() {
    string pocz = to_string(st);
    int start = tempTr.table[0][1] - 48;
    int stop = tempTr.table[0][0] - 48;
    int temp = 0;
    int next;
    string te = "";
    string droga = "";

    droga += to_string(stop);
    droga += to_string(start);

    int how = start;
    int n = tempTr.rozmiar-1;
    int save = n;

    for(int i=0;i<how-2;i++){
        int m = start;
        next = stop;
        if(m == 3) {
            for (int k = 0; k < 3; k++) {
                if (k == next) {
                    droga += tempTr.table[n];
                    break;
                }
                n--;
            }
            break;
        }
        while(true){
            for(int j=1;true;j++){
                if(tempTr.table[n][1] - 48 == start-1){
                    te+=tempTr.table[n];
                    n--;
                    break;
                }
                te+=tempTr.table[n];
                n--;
            }
            if(temp==next) {
                n = save;
                break;
            }
            temp++;
            te = "";
        }
        start = te[te.length()-1]-48;
        stop = te[te.length()-2] - 48;
        save = n;
        droga+=std::to_string(te[te.length()-2] - 48);
        droga+=std::to_string(te[te.length()-1]-48);
        temp = 0;
    }
    cout<<droga<<endl;
    string t = wskazSciezke(droga);
    cout<<t<<endl;
}

string DP::wskazSciezke(string droga){
    string res = "";
    string temp = "";

    int wsk = 0;
    int n = 0;
    int start = droga[wsk+1] - 48;
    int m = droga[wsk] - 48;
    int tem = 0;
    int liczba = stoi(tr.table[tr.rozmiar-1],0,10);

    int save = n;


    for(int i=0;i<rozGraf-2;i++){
        if(start==2){
            for (int k = 0; k < 2; k++) {

                if (k == m) {
                    res += tr.table[n][1];
                    res += tr.table[n][0];
                    break;
                }
                n+=2;
            }
            break;
        }
        while(true){
            for(int j=1;true;j++){
                if(tr.table[n]== to_string(liczba)){
                    n++;
                    break;
                }
                temp+=tr.table[n];
                n++;
            }
            if(tem==m) {
                n = save;
                break;
            }
            tem++;
            save = n;
            temp = "";
        }
        res += temp[temp.length()-1];
        liczba = temp[temp.length()-1] - 48;
        wsk += 2;
        m = droga[wsk] - 48;
        start = droga[wsk+1] - 48;
        temp = "";
        tem = 0;
    }

    return res;
}

int DP::getWynik() {
    return wynik;
}

int DP::FindMin(tablicaI data, int start){
    string temp;
    if(data.rozmiar==1) return data.table[0];
    int min = INT_MAX;
    int f;
    for(int i=0;i<data.rozmiar;i++){
        if(data.table[i] < min) {
            min = data.table[i];
            f = i;
        }
    }

    cout<<f<<" "<<data.rozmiar<<endl;
    temp = to_string(f) + to_string(data.rozmiar);
    tempTr.dodajNaPoczatek(temp);
    count++;
    return min;
}

string DP::getTrasa() {
    return trasa;
}