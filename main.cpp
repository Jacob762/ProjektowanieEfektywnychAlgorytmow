#include <iostream>
#include "Struktury/Graf/Graf.h"
#include "Algorytm/BruteForce/BruteForce.h"
#include "Algorytm/DP/DP.h"
#include "Algorytm/BruteForce/BruteForceTesty.h"
#include "Algorytm/DP/DPTesty.h"

using namespace std;

int main() {
    //BruteForce bruteForce = BruteForce("br17.atsp",2);
    //cout<<bruteForce.getSciezka()<<endl<<bruteForce.getTrasa()<<endl;

    
    //DP dp = DP("br17.atsp",1);
    //cout<<endl;
    //cout<<dp.getWynik()<<endl;
    //dp.getTrasa();

    //DPTesty dot = DPTesty(4,10,10);
    //BruteForceTesty bfg = BruteForceTesty(4,10,10);

    //DPTesty dot1 = DPTesty(4,10,10);
    //DPTesty dot2 = DPTesty(5,10,10);
    //DPTesty dot3 = DPTesty(6,10,10);
    DPTesty dot4 = DPTesty(7,10,10);


    //BruteForceTesty bfg = BruteForceTesty(4,10,10);
    //BruteForceTesty bfg = BruteForceTesty(4,10,10);
    //BruteForceTesty bfg = BruteForceTesty(4,10,10);
    //BruteForceTesty bfg = BruteForceTesty(7,10,10);


    return 0;
}
