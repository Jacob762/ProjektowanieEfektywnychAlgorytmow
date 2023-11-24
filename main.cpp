#include <iostream>
#include "Struktury/Graf/Graf.h"
#include "Algorytm/DP/DP.h"
#include "Algorytm/BruteForce/BruteForce.h"
#include "Algorytm/SA/SimulatedAnnealing.h"
#include <cmath>

using namespace std;

int main() {

    int start = 1;
    double wspolcz = 0.999;
    double te = 1e+300;
    string naz = "tsp_17.txt";
    DP dp = DP(naz,1);
    cout<<dp.getWynik()<<endl;
    dp.getTrasa();

    SimulatedAnnealing sa = SimulatedAnnealing("tsp_17.txt",0,te,wspolcz);

    cout<<sa.getWynik()<<endl;
    sa.getTrasa();

    return 0;
}
