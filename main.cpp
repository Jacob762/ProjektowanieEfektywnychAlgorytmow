#include <iostream>
#include "Struktury/Graf/Graf.h"
#include "Algorytm/BruteForce/BruteForce.h"
#include "Algorytm/DP/DP.h"

using namespace std;

int main() {
    BruteForce bruteForce = BruteForce("br17.atsp",1);
    cout<<bruteForce.getSciezka()<<endl<<bruteForce.getTrasa()<<endl;

    //cout<<(3|(1<<0));
    DP dp = DP("br17.atsp",1);
    cout<<dp.getWynik()<<endl;//<<dp.getTrasa()<<endl;

    return 0;
}
