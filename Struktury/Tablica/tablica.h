//
// Created by Jakub Klawon on 07/03/2023.
//

#ifndef SDIZO_TABLICA_H
#define SDIZO_TABLICA_H
#include <iostream>
#include <cstdio>
#include <ctime>
#include <ratio>
#include <chrono>

namespace std {

    class tablica {
    public:
        string * table = NULL;
        string * temp;
        int rozmiar = 0;
        tablica();
        void menu();
        void dodajNaPoczatek(string liczba);
        void dodajNaKoniec(string liczba);
        void dodajNaDowolneMiejsce(int liczba, int index);
        void usunZPoczatku();
        void usunZKonca();
        void usunZDowolnegoMiejsca(int index);
        void pokaz();
        void relocate();
        void wczytaj(string nazwa);
        void zapisz(string nazwa);
        bool isEmpty();
        int wyszukaj(int number);

        int wyszukaj(string number);
    };

} // std

#endif //SDIZO_TABLICA_H