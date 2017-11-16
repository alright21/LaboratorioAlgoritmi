#include <iostream>
#include <fstream>
#include <vector>

using namespace std;


struct triangle
{

    char direction;
    int position;
};
void controllaSoli(triangle triangoli[],int length);
void inserisciTriangolo(triangle t);


int length;



vector <triangle> aloneTriangles;
triangle a[200];

int main()
{




    ifstream in("input.txt");
    ofstream out("output.txt");


    in>>length;



    for(int i = 0; i < length; i++)
    {

        in>> a[i].direction;
        a[i].position=i;

        // cout << "direzione = " << a[i].direction << endl;
        //cout<< "posizione = "<< a[i].position << endl;
        // cout << "lunghezza = " << length <<endl;
        //cout<<endl;


    }


        controllaSoli(a,length);





    out<<aloneTriangles.size()<<endl;


    for(int i=0; i < aloneTriangles.size(); i ++)
    {

        out << aloneTriangles[i].position << " ";
    }






    return 0;
}


void controllaSoli(triangle triangoli[],int lunghezza)
{


    //cout << "lunghezza array iniziale = " << length << endl;


    //cout << "lunghezza = " << lunghezza << endl;
   // for(int i =0; i < lunghezza; i++)
   // {
   //     cout << triangoli[i].direction;
   //     cout<<endl;
   // }



    if(lunghezza<2)
    {

        cout << "lunghezza dell'array = 1" << endl;

        inserisciTriangolo(triangoli[0]);

    }
    else
    {

        triangle appoggio[lunghezza-2];

        for(int i=1; i < (lunghezza-1); i++)
        {

        //    cout << " attuale = " << i << endl;

cout <<"Elimino "<< triangoli[i].position<<triangoli[i].direction <<" ";

            if(triangoli[i].direction=='s')
            {

                //cout<<"Triangolo a sinistra" << endl;
                //cout << "Triangolo in posizione = " << triangoli[i].position << endl;


                for(int j=0; j < lunghezza-2; j++)
                {
                    if(j < i-1){
                        appoggio[j]=triangoli[j];
                    }
                    else{
                        appoggio[j]=triangoli[j+2];
                    }

                }

            }
            else
            {
                //cout<<"Triangolo a destra" << endl;
                //cout << "Triangolo in posizione = " << triangoli[i].position << endl;
                for(int j=0; j < lunghezza-2; j++)
                {
                    if(j < i){
                    appoggio[j]=triangoli[j];
                    }
                    else{
                        appoggio[j]=triangoli[j+2];
                    }

                }

            }
            controllaSoli(appoggio,(lunghezza-2));

        }


    }





}


void inserisciTriangolo(triangle t)
{

    bool presente = false;

    for(int i=0; i <aloneTriangles.size(); i++){

       if(t.position==aloneTriangles[i].position){
        presente=true;
       }

    }
    if(presente==false){
        aloneTriangles.push_back(t);
    }

}
