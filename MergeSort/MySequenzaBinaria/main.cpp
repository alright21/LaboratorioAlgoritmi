#include <iostream>

using namespace std;

int main()





{

cout << "Prova" << endl;
    int a[6] = {0,1,1,1,0,0};
    int lv = 0;
    int lm =0;
    int k = 0;
    int prec;
    int vet = 0;

    for(int i=0; i < 6; i++){



    cout << "Giro numero = "<< i << endl;

    cout << "prec = " << prec << endl;


        if(i == 0){
            prec = a[i];
            lv+=1;




            cout << "Primo giro" << endl;
            cout << "lv = " << lv << endl;
            cout << "lm = " << lm << endl;




        }
        else{


            if(prec == a[i]){
                     lv+=1;
            cout << "prec è uguale a i" << endl;
            cout << "lv = " << lv << endl;
            cout << "lm = " << lm << endl;




            }
            else{
                    vet = lv;
                lm+=1;
                lv = lm;
                prec = a[i];

            cout << "prec è diverso a i" << endl;
            cout << "lv = " << lv << endl;
            cout << "lm = " << lm << endl;


            }

        }

        if((lv == vet) || ((lm < lv )&& (lm > k)))
        {

            k = lv;
            lv = lm;
            lm = 0;



        }

        cout << "k = " << k<< endl;
            cout << endl;


    }


    cout << k << endl;



    return 0;
}
