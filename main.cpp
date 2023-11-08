#include <iostream>
#include "Struktury/Graf/Graf.h"
#include "Algorytm/BruteForce/BruteForce.h"
#include "Algorytm/DP/DP.h"

using namespace std;

int main() {

    string input;
    int start;
    cout<<"Podaj nazwe pliku:"<<endl;
    cin>>input;
    cout<<"Podaj miasto startowe:"<<endl;
    cin>>start;
    string s = input;
    BruteForce bf = BruteForce(s,start);
    cout<<"-----------------"<<endl;
    cout<<"Przeglad zupelny"<<endl;
    cout<<"-----------------"<<endl;
    cout<<"Wynik: "<< bf.getSciezka()<<endl;
    cout<<"Trasa: ";
    bf.getTrasa();
    cout<<endl;
    DP dp = DP(s,start);
    cout<<"-------------------------"<<endl;
    cout<<"Programowanie dynamiczne"<<endl;
    cout<<"-------------------------"<<endl;
    cout<<"Wynik: "<<dp.getWynik()<<endl;
    cout<<"Trasa: ";
    dp.getTrasa();
    cout<<"-------------------------"<<endl;
    return 0;
}
