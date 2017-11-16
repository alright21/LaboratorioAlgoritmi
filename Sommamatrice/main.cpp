#include <iostream>
#include <fstream>
using namespace std;

int matrice[2000][2000];
int appoggio[2000];


int main()
{

    ifstream in ("input.txt");
    ofstream out ("output.txt");

    int R;
    int C;

    in>>R>>C;

    for(int i=0; i<R; i++){
        for (int j = 0; j < C; j++){

            in>>matrice[i][j];

        }
    }




    int sommaMax=0;



    for(int i= 0; i < R; i++){


       for(int i = 0; i < 2000; i++){
                appoggio[i]= 0;
            }


        for (int k=i ; k < R; k++){


     int sommaCorrente =0;

            for(int j=0; j < C ; j++ ){



                appoggio[j]+=matrice[k][j];





                sommaCorrente+=appoggio[j];


                if(sommaCorrente<0){
                    sommaCorrente=0;

                }
                if(sommaCorrente>sommaMax){
                    sommaMax=sommaCorrente;
                }


            }
        }
    }


    out<<sommaMax;






    return 0;
}
