//
// Created by Jakub Klawon on 08/03/2023.
//

#include "listaElement.h"
#include <iostream>

using namespace std;

listaElement::listaElement(int liczba) {
    nextEl = NULL;
    prevEl = NULL;
    data = liczba;
}