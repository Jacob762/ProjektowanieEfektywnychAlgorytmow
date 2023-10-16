//
// Created by Jakub Klawon on 07/03/2023.
//

#include <fstream>
#include "tablica.h"

namespace std {
    tablica::tablica(){
        table = new string [rozmiar];
    }

    void tablica::pokaz() {
        if(rozmiar==0) return;
        for(int i=0;i<rozmiar;i++) cout<<table[i]<<" ";
        cout<<endl;
    }
    void tablica::dodajNaKoniec(string liczba) {
        temp = new string[++rozmiar];
        for(int i=0;i<rozmiar-1;i++) temp[i] = table[i];
        temp[rozmiar-1] = liczba;
        relocate();
    }
    void tablica::dodajNaPoczatek(string liczba) {
        temp = new string[++rozmiar];
        temp[0] = liczba;
        for(int i=1;i<rozmiar;i++) temp[i] = table[i-1];
        relocate();
    }
    void tablica::dodajNaDowolneMiejsce(int liczba, int index) {
        if(index<0 || index>=rozmiar) {
            cout<<"Nie ma takiego indeksu"<<endl;
            return;
        }
        temp = new string[++rozmiar];
        temp[index] = to_string(liczba);
        for(int i=0;i<index;i++) temp[i] = table[i];
        for(int i=index+1;i<rozmiar;i++) temp[i] = table[i-1];
        relocate();
    }
    void tablica::usunZKonca() {
        if(rozmiar==0) {
            cout<<"Lista pusta"<<endl;
            return;
        }
        temp = new string[--rozmiar];
        for(int i=0;i<rozmiar;i++) temp[i] = table[i];
        relocate();
    }
    void tablica::relocate(){
        delete [] table;
        table = temp;
    }
    void tablica::usunZPoczatku() {
        if(rozmiar==0) {
            cout<<"Lista pusta"<<endl;
            return;
        }
        temp = new string[--rozmiar];
        for(int i=0;i<rozmiar;i++) temp[i] = table[i+1];
        relocate();
    }
    void tablica::usunZDowolnegoMiejsca(int index) {
        if(rozmiar==0) {
            cout<<"Lista pusta"<<endl;
            return;
        }
        if(index<0 || index>=rozmiar) {
            cout<<"Nie ma takiego indeksu"<<endl;
            return;
        }
        temp = new string[--rozmiar];
        for(int i=0;i<index;i++) temp[i] = table[i];
        for(int i=index;i<rozmiar;i++) temp[i] = table[i+1];
        relocate();
    }

    void tablica::wczytaj(string nazwa) {
        fstream file (nazwa,std::ios_base::in);
        if (!file.is_open()) {
            cout<<"ERROR"<<endl;
            return;
        }
        int number;
        while (file >> number){
            dodajNaKoniec(to_string(number));
        }
    }

    void tablica::zapisz(string nazwa) {
        if (table==NULL) cout<<"Brak utworzonej tablicy."<<endl;
        else {
            ofstream file (nazwa);
            if (!file.is_open()) {
                cout<<"ERROR"<<endl;
                return;
            }
            for (int i = 0; i < rozmiar; i++) {
                file<<table[i]<<" ";
            }
        }
    }

    int tablica::wyszukaj(string number){
        for(int i=0;i<rozmiar;i++){
            if(table[i]==number){
                return i;
            }
        }
        return -42;
    }

    bool tablica::isEmpty() {
        if(rozmiar==0) return true;
    }
} // std