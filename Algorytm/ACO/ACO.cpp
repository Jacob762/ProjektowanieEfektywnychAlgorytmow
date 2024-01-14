//
// Created by Jakub Klawon on 26/12/2023.
//

#include "ACO.h"

//
// Created by jakub on 11/19/2023.
//

#include <random>

ACO::ACO(string nazwa) {
    graf = Graf(nazwa);

    wynik = INT_MAX;
    rozGraf = graf.getRozmiar();

    sciezkaFinal = new int[rozGraf];
    trasa = lista();

    sciezkaFinal[0] = 0;

    for(int i=1;i<rozGraf;i++){
        sciezkaFinal[i] = i;
    }

    greedy(0,sciezkaFinal);
    simulation(3.6,14.0,0.5,100.0);


}

int ACO::getWynik() {
    return wynik;
}

void ACO::getTrasa() {
    for(int i=0;i<rozGraf;i++) cout<<sciezkaFinal[i]+1<<" ";
    cout<<sciezkaFinal[0]+1<<endl;
}

int ACO::getSize() {
    return rozGraf;
}

ACO::ACO(int size) {
    graf = Graf(size);

    wynik = INT_MAX;
    rozGraf = graf.getRozmiar();

    sciezkaFinal = new int[rozGraf];
    trasa = lista();

    sciezkaFinal[0] = 1;

    for(int i=1;i<rozGraf;i++){
        sciezkaFinal[i] = i;
    }

}

double ACO::cal_start() {
    tablicaI tab = tablicaI();
    double delta = 0;
    for(int i=0;i<rozGraf;i++) tab.dodajNaKoniec(i);
    int a;
    int b;

    for(int i=0;i<10000;i++){
        nowaSciezka(tab);
        a = obliczKoszt(tab);
        nowaSciezka(tab);
        b = obliczKoszt(tab);
        delta += ::abs(a-b);
    }

    delta /= 10000;

    return delta;
}

double ACO::getTO() {
    return 80.0;
}

void ACO::simulation(double alphaIN, double betaIN, double evaporationIN, double feromonIN) { ///todo przebudowanie kodu pod latwiejsze dostosowywanie paramtrow, zabawa paramterami, sprobowac uzyc greedy do poczatkowej trasy?
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> los(0.0, 1.0);

    double feromon_start = cal_start();
    feromon_start = (double) rozGraf/ feromon_start;

    double *prawdopodobienstwo;
    double *aktualneMiasta;
    tablicaI path = tablicaI();
    int *sciezka = new int[rozGraf];
    double **feromony;
    double **desire;
    double **dodaj_feromony;
    dodaj_feromony = new double * [rozGraf];
    desire = new double * [rozGraf];
    feromony = new double * [rozGraf];
    double alpha = alphaIN;
    double beta = betaIN;   //a=3.5,b=5.9 dla >=12
    double evaporation = evaporationIN;
    double feromon = feromonIN;

    double mianownik;

    for(int i=0;i<rozGraf;i++){
        sciezka[i] = i;
        feromony[i] = new double [rozGraf];
        desire[i]= new double [rozGraf];
        dodaj_feromony[i] = new double [rozGraf];
        for(int j=0;j<rozGraf;j++) {
            feromony[i][j] = feromon_start;
            dodaj_feromony[i][j] = 0.0;
            if(graf.grafMacierz[i][j]!=0){
                desire[i][j] = (feromony[i][j]*1000) * (1/(double)graf.grafMacierz[i][j]);
            } else desire[i][j] = 0;
        }
    }

//    int *greed = new int [rozGraf];
//    for(int i=0;i<rozGraf;i++) greed[i] = i;
//    greedy(0,greed);
//    tablicaI tab = tablicaI();
//    for(int i=0;i<rozGraf;i++) {
//        tab.dodajNaKoniec(greed[i]);
//        cout<<greed[i]<<" ";
//    }
//    cout<<obliczKoszt(tab)<<endl;

//    for(int i=0;i<rozGraf-1;i++){
//        feromony[greed[i]][greed[i+1]] += 0.1;
//        desire[greed[i]][greed[i+1]] = (feromony[greed[i]][greed[i+1]]*1000) * (1/(double)graf.grafMacierz[greed[i]][greed[i+1]]);
//    }
//    feromony[greed[rozGraf-1]][greed[0]] += 0.1;
//    desire[greed[rozGraf-1]][greed[0]] = (feromony[greed[rozGraf-1]][greed[0]]*1000) * (1/(double)graf.grafMacierz[greed[rozGraf-1]][greed[0]]);
 //   greedy(0,sciezka);
//    cout<<obliczKoszt(sciezka)<<" GREEDY"<<endl;
  //  for(int i=0;i<rozGraf;i++) cout<<sciezka[i]+1<<" ";
 //   cout<<sciezka[0]+1<<endl;

    //int najWynik = wynik;
    int najWynik = INT_MAX;
    int staraOdleglosc = INT_MAX;
    int aktualnaOdleglosc = najWynik;
    int powtorka=0;
    int iteracje = 10;

    while(powtorka<iteracje){

        for(int k=0;k<rozGraf;k++){

            double licznik;
            bool odwiedzone[rozGraf];
            for(int initOd=0;initOd<rozGraf;initOd++) odwiedzone[initOd] = false;
            int miasto = k;
            odwiedzone[k] = true;
            path.dodajNaKoniec(miasto);
            for(int i=0;i<rozGraf-1;i++){ //petla do znalezienia sciezki startujacej od kazdego wierzcholka k

                //tworzenie dostepnych wierzcholkow i edytowanie tablicy
                //na biezaco obliczanie mianownika do prawdopodobienstwa
                //przeliczanie prawdopdoobienstwa i tworzenie sciezki

                mianownik = 0.0;

                int liczbaMiast = 0;

                for(int ite=0;ite<rozGraf;ite++){
                    if(!odwiedzone[ite]) {
                        mianownik += (pow(feromony[miasto][ite],alpha) * pow(desire[miasto][ite],beta));
                        liczbaMiast++;
                    }
                }

                int pamietaj_miasto[liczbaMiast];
                int buff = 0;
                prawdopodobienstwo = new double [rozGraf];

                    for(int ite=0;ite<rozGraf;ite++){
                        if(!odwiedzone[ite]){
                            licznik = (pow(feromony[miasto][ite],alpha) * pow(desire[miasto][ite],beta));
                            prawdopodobienstwo[ite] = licznik/mianownik;
                            pamietaj_miasto[buff++] = ite;
                        }else prawdopodobienstwo[ite] = -1.0;
                    }
                    aktualneMiasta = new double [liczbaMiast];
                    double rng = los(gen);

                    int save = 0;
                    for(int ite=0;ite<rozGraf;ite++){
                        if(prawdopodobienstwo[ite]!=-1.0){
                            aktualneMiasta[save] = prawdopodobienstwo[ite];
                            save++;
                        }
                    }

                    ruletka(liczbaMiast,aktualneMiasta);

                    for(int ite=0;ite<liczbaMiast;ite++){
                        if(rng < aktualneMiasta[ite]){ //bug, nie zawsze wchodzi, byc moze partial_sum sie zle wykonuje
                            path.dodajNaKoniec(pamietaj_miasto[ite]);
                            odwiedzone[pamietaj_miasto[ite]] = true;
                            //trzeba zweryfikowac ktory to wierzcholek i dodac go do aktualnej sciezki
                            //odwiedzone[wybrany_wierzcholek] = true
                            // i lecim dalej wybierac
                            miasto = pamietaj_miasto[ite];
                            break;
                        }
                    }

                    delete [] aktualneMiasta;
                    delete [] prawdopodobienstwo;

            }

            // tu liczymy koszt znalezionej sciezki
            // dodajemy feromony na sciezke dodaj_feromony[i][j], gdzoe i,j okreslaja wierzcholek na sciezce
            //if(path.rozmiar!=rozGraf) continue;
            int koszt = obliczKoszt(path);

            if(koszt < najWynik){
                najWynik = koszt;
                for(int r=0;r<rozGraf;r++) sciezka[r] = path.table[r];
            }

            for(int r=0;r<rozGraf-1;r++){
                dodaj_feromony[path.table[r]][path.table[r+1]] += feromon/ (double) koszt;
                if(r==rozGraf-2){
                    dodaj_feromony[path.table[r+1]][path.table[0]] += feromon/ (double) koszt;
                }
            }
            for(int r=0;r>rozGraf;r++) path.usunZKonca();
        }

        for(int i=0;i<rozGraf;i++){
            for(int j=0;j<rozGraf;j++){
                feromony[i][j] = (feromony[i][j] * evaporation) + dodaj_feromony[i][j];
                dodaj_feromony[i][j] = 0.0;
            }
        }

        aktualnaOdleglosc = najWynik;
        if(aktualnaOdleglosc==staraOdleglosc){
            powtorka++;
        } else powtorka=0;
        staraOdleglosc = aktualnaOdleglosc;
    }
    wynik = najWynik;
    for(int i=0;i<rozGraf;i++) sciezkaFinal[i] = sciezka[i];
}

int ACO::obliczKoszt(tablicaI sciezka) {
    int res = 0;
    for(int i=0;i<rozGraf-1;i++){
        res += graf.grafMacierz[sciezka.table[i]][sciezka.table[i+1]];
    }
    res += graf.grafMacierz[sciezka.table[rozGraf-1]][sciezka.table[0]];
    return res;
}

void ACO::nowaSciezka(tablicaI sciezka) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1, rozGraf-1);
    int indeks1 = distrib(gen);
    int indeks2 = distrib(gen);
    while(indeks1==indeks2) indeks2 = distrib(gen);
    int temp = sciezka.table[indeks1];
    sciezka.table[indeks1] = sciezka.table[indeks2];
    sciezka.table[indeks2] = temp;
}

double ACO::propability_cal(){ //TO-DO:obliczanie prawdopodobienstwa przejscia do miasta
    double sol = 0;

    return sol;
}

void ACO::greedy(int start, int *&sciezka){
    int tempTab[rozGraf];
    bool odwiedzone[rozGraf];

    for(int i=0;i<rozGraf;i++) odwiedzone[i] = false;

    int k = 0;
    int i = start;
    tempTab[0] = start;
    while(k < rozGraf){
        int max = INT_MAX;
        int tempJ = -1;
        odwiedzone[i] = true;
        for(int j=0;j<rozGraf;j++){
            if(graf.grafMacierz[i][j]<max && !odwiedzone[j]){
                max = graf.grafMacierz[i][j];
                tempJ = j;
            }
        }
        i = tempJ;
        k++;
        tempTab[k] = tempJ;
    }

    for(int n=0;n<rozGraf;n++) sciezka[n] = tempTab[n];
}

void ACO::ruletka( int n, double *&aktualneMiasta){
    for(int i=0;i<n-1;i++){
        aktualneMiasta[i+1] += aktualneMiasta[i];
    }
}