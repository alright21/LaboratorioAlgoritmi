#include <iostream>


using namespace std;


void fibonacci(int n, int serie[]);

int main()
{
    int input;
    int serieFibonacci[1000];

    for(int i=0; i<1000; i++)
    {

        serieFibonacci[i] = 0;
    }
    serieFibonacci[0] = 1;
    serieFibonacci[1] = 1;
    while(input!=-1)
    {
        cout <<"Inserisci il numero di fibonacci da calcolare(-1 per uscire): "<<endl;
        cin >> input;

        if(input>0)
        {
            fibonacci(input,serieFibonacci);

            cout <<input<<" numero di fibonacci: "<<serieFibonacci[input-1]<<endl;
        }

    }

    return 0;
}


void fibonacci(int n,int serie[])
{

    for(int i=0; i < n; i++)
    {

        if(serie[i]==0)
        {

            serie[i]= serie[i-1]+serie[i-2];
        }
    }

}
