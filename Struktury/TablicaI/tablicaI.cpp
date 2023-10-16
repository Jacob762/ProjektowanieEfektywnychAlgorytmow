//
// Created by Jakub Klawon on 07/03/2023.
//

#include <fstream>
#include "tablicaI.h"

namespace std {
    tablicaI::tablicaI(){
        table = new int[rozmiar];
    }

    tablicaI::~tablicaI(){

    }
    void tablicaI::menu() {
        int n;
        int liczba;
        string name;
        for(;;){
            cout<<"Podaj numer akcji ktora chcesz wykonac:"<<endl;
            cout<<"1. Dodaj na koniec"<<endl;
            cout<<"2. Pokaz"<<endl;
            cout<<"3. Wyjdz"<<endl;
            cout<<"4. Dodaj na poczatek"<<endl;
            cout<<"5. Dodaj w danym miejscu"<<endl;
            cout<<"6. Usum z konca"<<endl;
            cout<<"7. Usun z poczatku"<<endl;
            cout<<"8. Usun z dowolnego miejsca"<<endl;
            cout<<"9. Wyszukaj element"<<endl;
            cout<<"10. Wczytaj dane"<<endl;
            cout<<"11. Zapisz dane"<<endl;
            cin.sync(); cin.clear();
            cin>>n;
            switch (n) {
                case 1:
                    cin.sync(); cin.clear();
                    cout<<"Podaj liczbe"<<endl;
                    cin>>liczba;
                    dodajNaKoniec(liczba);
                    break;
                case 2:
                    pokaz();
                    break;
                case 4:
                    cin.sync(); cin.clear();
                    cout<<"Podaj liczbe"<<endl;
                    cin>>liczba;
                    dodajNaPoczatek(liczba);
                    break;
                case 5:
                    cin.sync(); cin.clear();
                    cout<<"Podaj liczbe"<<endl;
                    cin>>liczba;
                    cout<<"Podaj indeks"<<endl;
                    cin>>n;
                    dodajNaDowolneMiejsce(liczba,n);
                    break;
                case 6:
                    cin.sync(); cin.clear();
                    usunZKonca();
                    break;
                case 7:
                    cin.sync(); cin.clear();
                    usunZPoczatku();
                    break;
                case 8:
                    cin.sync(); cin.clear();
                    cout<<"Podaj indeks"<<endl;
                    cin>>n;
                    usunZDowolnegoMiejsca(n);
                    break;
                case 9:
                    cin.sync(); cin.clear();
                    cout<<"Podaj liczbe"<<endl;
                    cin>>n;
                    liczba = wyszukaj(n);
                    if(liczba!=-42) cout<<liczba<<endl;
                    else cout<<"nie ma takiej liczby"<<endl;
                    break;
                case 3:
                    delete [] table;
                    exit(2137);
                case 10:
                    cin.sync(); cin.clear();
                    cout<<"Podaj nazwe pliku"<<endl;
                    cin>>name;
                    wczytaj(name);
                    break;
                case 11:
                    cin.sync(); cin.clear();
                    cout<<"Podaj nazwe pliku"<<endl;
                    cin>>name;
                    zapisz(name);
                    break;
            }
        }
    }
    void tablicaI::pokaz() {
        if(rozmiar==0) return;
        for(int i=0;i<rozmiar;i++) cout<<table[i]<<" ";
        cout<<endl;
    }
    void tablicaI::dodajNaKoniec(int liczba) {
        temp = new int[++rozmiar];
        for(int i=0;i<rozmiar-1;i++) temp[i] = table[i];
        temp[rozmiar-1] = liczba;
        relocate();
    }
    void tablicaI::dodajNaPoczatek(int liczba) {
        temp = new int[++rozmiar];
        temp[0] = liczba;
        for(int i=1;i<rozmiar;i++) temp[i] = table[i-1];
        relocate();
    }
    void tablicaI::dodajNaDowolneMiejsce(int liczba, int index) {
        if(index<0 || index>=rozmiar) {
            cout<<"Nie ma takiego indeksu"<<endl;
            return;
        }
        temp = new int[++rozmiar];
        temp[index] = liczba;
        for(int i=0;i<index;i++) temp[i] = table[i];
        for(int i=index+1;i<rozmiar;i++) temp[i] = table[i-1];
        relocate();
    }
    void tablicaI::usunZKonca() {
        if(rozmiar==0) {
            cout<<"Lista pusta"<<endl;
            return;
        }
        temp = new int[--rozmiar];
        for(int i=0;i<rozmiar;i++) temp[i] = table[i];
        relocate();
    }
    void tablicaI::relocate(){
        delete [] table;
        table = temp;
    }
    void tablicaI::usunZPoczatku() {
        if(rozmiar==0) {
            cout<<"Lista pusta"<<endl;
            return;
        }
        temp = new int[--rozmiar];
        for(int i=0;i<rozmiar;i++) temp[i] = table[i+1];
        relocate();
    }
    void tablicaI::usunZDowolnegoMiejsca(int index) {
        if(rozmiar==0) {
            cout<<"Lista pusta"<<endl;
            return;
        }
        if(index<0 || index>=rozmiar) {
            cout<<"Nie ma takiego indeksu"<<endl;
            return;
        }
        temp = new int[--rozmiar];
        for(int i=0;i<index;i++) temp[i] = table[i];
        for(int i=index;i<rozmiar;i++) temp[i] = table[i+1];
        relocate();
    }

    void tablicaI::wczytaj(string nazwa) {
        fstream file (nazwa,std::ios_base::in);
        if (!file.is_open()) {
            cout<<"ERROR"<<endl;
            return;
        }
        int number;
        while (file >> number){
            dodajNaKoniec(number);
        }
    }

    void tablicaI::zapisz(string nazwa) {
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

    int tablicaI::wyszukaj(int number){
        for(int i=0;i<rozmiar;i++){
            if(table[i]==number){
                return i;
            }
        }
        return -42;
    }
} // std