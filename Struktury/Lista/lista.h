//
// Created by Jakub Klawon on 08/03/2023.
//

#ifndef SDIZO_LISTA_H
#define SDIZO_LISTA_H
#include "listaElement.h"
#include <iostream>
#include <cstdio>
#include <ctime>
#include <ratio>
#include <chrono>

using namespace std;

class lista {
private:
    listaElement * head;
    listaElement * tail;
public:
    int rozmiar;
    lista();
    void pokaz();
    void dodajNaKoniec(listaElement * element);
    void dodajNaPoczatek(listaElement *element);
    bool isEmpty();
    bool isEven();
    listaElement* wyszukajElement(int liczba);
    void dodajWDowolnymMiejscu(int index,listaElement * element);
    void usunZPoczatku();
    void usunZKonca();
    void usunZDowolnegoMiejsca(int index);
    bool safetyFirst();
    void test(int wielkoscZestawu,int iloscOperacji,int iloscWynikow);
    void wczytaj(string nazwa);
    void zapisz(string nazwa);

    void menu();

    int wyszukajElementIndex(int liczba);

    int getHead();
};


#endif //SDIZO_LISTA_H
