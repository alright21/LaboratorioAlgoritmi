#include <iostream>
#include <fstream>



using namespace std;


void myMergeSort(int a[],int primo,int ultimo);
void myMerge(int a[],int primo,int ultimo,int mezzo);
void controllaIntervalli(int s, int e);


int s[100000];
int e[100000];
int size;
int lunghezza=0;
int inizio;
int fine;
int risStart;
int risEnd;
int main()
{
    ifstream in ("input.txt");
    ofstream out("output.txt");

    in>>size;

    for(int i=0; i < size; i++)
    {
        in>>s[i] >> e[i];
    }

    myMergeSort(s,0,size-1);


   /* for(int i= 0; i < size; i++)
    {

        cout << s[i] <<" " << e[i] << endl;
    }
*/

    for(int i=0; i < size; i++)
    {

        if (i==0)
        {

            inizio=s[i];
            fine=e[i];

        }
        else
            {

                controllaIntervalli(s[i],e[i]);
            }
    }


   // cout <<"Lunghezza massima = " << lunghezza << endl;
    //out << lunghezza << endl;
    if(lunghezza!=0){

    //cout << risStart << " " << risEnd << endl;

    out << risStart << " " << risEnd;
    }
    else{
        out << "0";
    }

    return 0;
}


void myMergeSort(int a[],int primo,int ultimo)
{

    if(primo < ultimo)
    {



        int mezzo = (ultimo+primo)/2;
        myMergeSort(a,primo,mezzo);
        myMergeSort(a,mezzo+1,ultimo);
        myMerge(a,primo,ultimo,mezzo);
    }

}

void myMerge(int a[],int primo,int ultimo,int mezzo)
{

    int i,j,k;

    i=primo;
    j=mezzo+1;
    k=0;
    int h = ultimo-primo+1;


    int *b = new int[h];
    int *c = new int[h];
    while ((i<=mezzo) && (j <=ultimo))
    {

        if(a[i]<=a[j])
        {

            b[k]=a[i];
            c[k]=e[i];

            i+=1;

        }
        else
        {

            b[k]=a[j];
            c[k]=e[j];
            j+=1;
        }
        k+=1;
    }

    while (i <= mezzo)
    {

        b[k]= a[i];
        c[k]=e[i];
        i+=1;
        k+=1;
    }
    while(j <= ultimo)
    {
        b[k]=a[j];
        c[k]=e[j];
        j+=1;
        k+=1;

    }

    for(int i=primo; i <= ultimo; i++)
    {

        a[i]=b[i-primo];
        e[i]=c[i-primo];
    }


}


void controllaIntervalli(int s, int e)
{

    if(s>fine)
    {

        inizio= s;

        if(lunghezza< (s-fine))
        {
            lunghezza=s-fine;

            risStart= fine;
            risEnd= s;
        }
    }

    if(e>fine)
    {

        fine = e;
    }

}

