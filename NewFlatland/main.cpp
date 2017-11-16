include <iostream>
#include <fstream>
#include <vector>

using namespace std;


struct triangle
{

    char direction;
    int position;
};





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


    for(int i=0; i < lunghezza; i++)
    {

        if((triangoli[i].position%2)==0)
        {

            bool sinistra = elimina(a,0,i-1);
            bool destra = elimina(a,i+1; lunghezza-1);

            if(sinistra && destra)
            {

                inserisciTriangolo(triangoli[i]);
            }
        }
    }



}


bool azzera (triangle arrayIniziale, int inizio; int fine)
{
    bool res =false;


    int h= fine-inizio+1;


    if(inizio>fine)
    {

        res=true;
    }
    else
    {

        triangle *appoggio = new triangle[h];

        for(int i=0; i < h; i++)
        {

            appoggio[i]=arrayIniziale[i];
        }

        if(appoggio[1].direction=='s')
        {

            for(int i=0; i < fine-2; i++)
            {

                appoggio[i]=appoggio[i+2];
            }

            res=azzera(0,fine-2);
        }
        else
        {

            for(int i=1; i < fine-2; i++)
            {

                appoggio[i]=appoggio[i+2];
            }
            res = azzera(0,fine-2);
        }
    }

    return res;




}





}


void inserisciTriangolo(triangle t)
{

    bool presente = false;

    for(int i=0; i <aloneTriangles.size(); i++)
    {

        if(t.position==aloneTriangles[i].position)
        {
            presente=true;
        }

    }
    if(presente==false)
    {
        aloneTriangles.push_back(t);
    }

}
