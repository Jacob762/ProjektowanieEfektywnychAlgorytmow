//
// Created by Jakub Klawon on 08/03/2023.
//

#ifndef SDIZO_LISTAELEMENT_H
#define SDIZO_LISTAELEMENT_H


class listaElement {
public:
    int data;
   // int key;
    listaElement * prevEl;
    listaElement * nextEl;
    listaElement(int liczba);
};


#endif //SDIZO_LISTAELEMENT_H
