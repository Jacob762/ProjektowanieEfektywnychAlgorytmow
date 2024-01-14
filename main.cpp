#include <iostream>
#include "Struktury/Graf/Graf.h"
#include "Algorytm/DP/DP.h"
#include "Algorytm/BruteForce/BruteForce.h"
#include "Algorytm/SA/SimulatedAnnealing.h"
#include "Algorytm/SA/SATesty.h"
#include "Algorytm/ACO/ACO.h"

using namespace std;

void menu();


int main() {

    double wspolcz = 0.9999;
    string naz = "ry48p.atsp";
    int exit;

    string nazwy[19] = {"br17.atsp","ftv33.atsp","ftv35.atsp",
                        "ftv38.atsp"
                        ,"p43.atsp","ftv44.atsp","ftv47.atsp",
                        "ry48p.atsp","ft53.atsp","ftv55.atsp",
                        "ftv64.atsp","ft70.atsp"
                        ,"ftv70.atsp","kro124p.atsp","ftv170.atsp"
                        ,"rbg323.atsp","rbg358.atsp","rbg403.atsp"
                        ,"rbg443.atsp"};
    int best[19] = {39,1286,1473,1530,5620,1613,
                    1776,14422,6905,1608,1839,38673,
                    1950,36230,2755,
                    1326,1163,2465,2720};


    ACO aco = ACO(naz);
    cout<<aco.getWynik()<<endl;
    aco.getTrasa();

    cout<<endl;

    //SimulatedAnnealing sa = SimulatedAnnealing(naz,1,0.999,0.001);
    //cout<<sa.getWynik()<<endl;
    //sa.getTrasa();

   // DP dp = DP(naz,1);
    //cout<<dp.getWynik()<<endl;
   // dp.getTrasa();

    //menu();
    return 23;

}

void menu(){
    int wybor;
    double wspolcz;
    string nazwa;
    for(;;){
        cout<<"Podaj nazwe pliku"<<endl;
        cin>>nazwa;
        cout<<"Podaj wspolczynnik chlodzenia"<<endl;
        cin>>wspolcz;
        SimulatedAnnealing sa = SimulatedAnnealing(nazwa,0,wspolcz,0.001);
        cout<<sa.getWynik()<<endl;
        sa.getTrasa();
        cout<<"Czy kontynuowac?"<<endl;
        cin>>wybor;
        if(wybor==0) return;
    }
}