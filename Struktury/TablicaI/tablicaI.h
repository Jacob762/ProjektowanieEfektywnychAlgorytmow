//
// Created by Jakub Klawon on 07/03/2023.
//

#ifndef SDIZO_tablicaII_H
#define SDIZO_tablicaI_H
#include <iostream>
#include <cstdio>
#include <ctime>
#include <ratio>
#include <chrono>

namespace std {

    class tablicaI {
    public:
        ~tablicaI();
        int * table = NULL;
        int * temp;
        int rozmiar = 0;
        tablicaI();
        void menu();
        void dodajNaPoczatek(int liczba);
        void dodajNaKoniec(int liczba);
        void dodajNaDowolneMiejsce(int liczba, int index);
        void usunZPoczatku();
        void usunZKonca();
        void usunZDowolnegoMiejsca(int index);
        void pokaz();
        void relocate();
        void wczytaj(string nazwa);
        void zapisz(string nazwa);

        int wyszukaj(int number);
    };

} // std

#endif //SDIZO_tablicaI_H