#include <iostream>
#include <fstream>
using namespace std;



int array[1000000];
int main()
{


    ifstream in ("input.txt");
    ofstream out ("output.txt");

    int N;

    in >> N;



    int sommaCorrente = 0;
    int sommaMax=0;

    for (int i=0; i < N; i++){
        in>>array[i];

    }
    for(int i=0; i < N; i++){

        sommaCorrente+=array[i];
        if(sommaCorrente<=0){
            sommaCorrente=0;
        }
        if(sommaCorrente>sommaMax){
            sommaMax=sommaCorrente;
        }


    }

    out << sommaMax << endl;




    return 0;
}
