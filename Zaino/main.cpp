#include <iostream>
#include <fstream>
using namespace std;


int zaino(int nOggetti,int capacita);

int peso[1001];
int valore[1001];

int **pesoDinamico;
//int pesoDinamico[1001][100001];


int main()
{   //cout <<"inizio main"<<endl;
    int capacita;
    int nOggetti;

    ifstream in("input.txt");
    ofstream out("output.txt");

    in>>capacita>>nOggetti;
    //cout <<"preso capacita = "<< capacita <<" e nOggetti = "<<nOggetti<<endl;

    for(int i=1; i <=nOggetti; i++){

        in>>peso[i];
        in>>valore[i];
    }


    //cout <<"presi pesi e valori"<<endl;


    int risultato = zaino(nOggetti,capacita);

    out <<risultato;








    return 0;
}


int zaino(int nOggetti,int capacita){

    //cout << "Entro in zaino"<<endl;


    //cout <<"pesoDinamico creato"<<endl;

    pesoDinamico = new int*[nOggetti+1];
    for(int i=0; i <=nOggetti;i++){

        pesoDinamico[i] = new int[capacita+1];
    }

    for (int i = 0; i <= nOggetti; i++){
        pesoDinamico[i][0] = 0;
    }
    for (int i = 0; i <=capacita;i++){
        pesoDinamico[0][capacita] = 0;
    }
    //cout << "pesoDinamico inizializzato "<<endl;
    for(int i = 1; i <= nOggetti; i++){

        for(int c = 1; c <= capacita; c++){
            //cout <<"Entro nel ciclo"<<endl;
            int nottaken = pesoDinamico[i-1][c];
            //cout <<"nottaken = "<<nottaken;
            int taken = -1;
            if(peso[i]<= c){

                taken = (pesoDinamico[i-1][c-peso[i]]) + valore[i];
            }
            //cout <<"    taken = "<<taken <<endl;

            //cout <<"peso e valore dell'oggetto "<<i<<":     "<<peso[i]<<"   "<<valore[i] << endl;
            pesoDinamico[i][c] = max(taken,nottaken);
        }
    }
    //riga delle capacità
    /*for (int i = 0; i<=capacita; i++){
        cout <<i << "    ";
    }cout <<endl;*/

    //costruiso la matrice pesoDinamico
    /*for (int i = 0; i <=nOggetti; i++){

        for(int j = 0; j <=capacita; j++){

            cout <<pesoDinamico[i][j]<<"    ";
        }
        cout <<endl;
    }*/
    int risultato = pesoDinamico[nOggetti][capacita];
    for (int i = 0; i<= nOggetti; i++){
        delete[] pesoDinamico[i];
    }

    delete[] pesoDinamico;

    return risultato;

}
