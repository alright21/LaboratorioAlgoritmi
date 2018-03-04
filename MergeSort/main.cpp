#include <iostream>
#include <fstream>

using namespace std;

void myMergeSort(int a[],int primo,int ultimo);
void myMerge(int a[],int primo,int ultimo,int mezzo);


int input[1000000];
int size;


int main()


{

    ifstream in("input1.txt");
    ofstream out("output.txt");

    in>>size;

    for(int i=0; i < size; i++){


        in>>input[i];
    }

    //cout <<"Inseriti i valori" << endl;


    myMergeSort(input,0,size-1);


    for(int i=0; i < size; i++){

        out << input[i] << " ";
    }



    return 0;
}


void myMergeSort(int a[],int primo,int ultimo)
{

    if(primo < ultimo)
    {

        //cout <<" Entro in mergeSort con inizio = " << primo << " e fine = " << ultimo << endl;

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

    //cout << "h = " << h << endl;
    int *b = new int[h];
    while ((i<=mezzo) && (j <=ultimo))
    {

        if(a[i]<=a[j])
        {

            b[k]=a[i];

            i+=1;

        }
        else
        {

            b[k]=a[j];
            j+=1;
        }
        k+=1;
    }

    while (i <= mezzo)
    {

        b[k]= a[i];
        i+=1;
        k+=1;
    }
    while(j <= ultimo)
    {
        b[k]=a[j];
        j+=1;
        k+=1;

    }

    for(int i=primo; i <= ultimo; i++)
    {

        a[i]=b[i-primo];
    }


}
