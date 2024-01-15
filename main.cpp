#include <iostream>
#include "Struktury/Graf/Graf.h"
#include "Algorytm/DP/DP.h"
#include "Algorytm/BruteForce/BruteForce.h"
#include "Algorytm/SA/SimulatedAnnealing.h"
#include "Algorytm/SA/SATesty.h"
#include "Algorytm/ACO/ACO.h"
#include "Algorytm/ACO/ACOTesty.h"

using namespace std;

void menu();


int main() {

    double alpha = 5.3;
    double beta = 14.0;
    double evap = 0.5;
    double ph = 150.0;
    string naz = "kro124p.atsp";
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




    menu();
    return 23;

}

void menu(){
    int wybor;
    double alpha;
    double beta;
    double ev;
    double ph;
    string nazwa;
    for(;;){
        cout<<"Podaj nazwe pliku"<<endl;
        cin>>nazwa;
        cout<<"Podaj alfa"<<endl;
        cin>>alpha;
        cout<<"Podaj beta"<<endl;
        cin>>beta;
        cout<<"Podaj evaporation_rate"<<endl;
        cin>>ev;
        cout<<"Podaj feromoy"<<endl;
        cin>>ph;
        ACO aco = ACO(nazwa,alpha,beta,ev,ph);
        cout<<aco.getWynik()<<endl;
        aco.getTrasa();
        cout<<"Czy kontynuowac?"<<endl;
        cin>>wybor;
        if(wybor==0) return;
    }
}