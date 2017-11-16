#include <iostream>

using namespace std;

void add(int a[],int k);

int main()
{

    long long volte;
    int a[64];

    for (int i = 0; i < 64; i++){
        a[i] = 0;
        cout << a[i];
    }
    cout << endl;

    cout << "interisci k" << endl;
    cin>> volte;

    cout << volte << endl;


    for (long long i = 0; i <= volte; i++){

        add(a,64);
    }





  for (int i = 63; i >=0; i--){
        cout << a[i];
    }
    cout << endl;


    return 0;


}

void add(int a[],int k){

        long long i=0;
        while ((i < k) && (a[i] == 1)){
            a[i] = 0;
            i++;
        }

        if(i < k){
            a[i]=1;
        }
       // cout << ++i<<endl;

    }
