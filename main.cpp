#include <iostream>
#include "Struktury/Graf/Graf.h"
#include "Algorytm/DP/DP.h"
#include "Algorytm/BruteForce/BruteForce.h"
#include "Algorytm/SA/SimulatedAnnealing.h"
#include "Algorytm/SA/SATesty.h"

using namespace std;

int main() {

    double wspolcz;
    string naz;
    int exit;

    string nazwy[19] = {"br17.atsp","ft53.atsp","ft70.atsp","ftv33.atsp","ftv35.atsp","ftv38.atsp"
    ,"ftv44.atsp","ftv47.atsp","ftv55.atsp","ftv64.atsp","ftv70.atsp","ftv170.atsp"
    ,"kro124p.atsp","p43.atsp","rbg323.atsp","rbg358.atsp","rbg403.atsp"
    ,"rbg443.atsp","ry48p.atsp"};
    int best[19] = {39,6905,38673,1286,1473,1530,1613,
                    1776,1608,1839,1950,2755,36230,5620,
                    1326,1163,2465,2720,14422};

    for(;;){
        cout<<"Podaj nazwe pliku"<<endl;
        cin>>naz;
        cout<<"Podaj wspolczynnik chlodzenia"<<endl;
        cin>>wspolcz;
        SimulatedAnnealing sa = SimulatedAnnealing(naz,0,wspolcz,0.001);
        cout<<sa.getWynik()<<endl;
        sa.getTrasa();
        cout<<"Czy chcesz kontynuowac? 1 lub 0"<<endl;
        cin>>exit;
        if(exit==0) return 0;
    }

}
