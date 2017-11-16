#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;



struct nodo
{

    int nome;
    vector<int> vic;
    bool visitato = false;

};

vector<nodo> grafo;

void erdos(vector <nodo> grafo, nodo& r);

int N;
int M;
int res=0;

int main()

{
   // cout << "Leggo main" <<endl;
    ifstream in("input.txt");
    ofstream out("output.txt");

    in>>N>>M;



    grafo.resize(N);

    for(int i = 0; i < M; i++)
    {


        int from,to;
        in>>from>>to;
        //grafo[from].nome=from;
        grafo[from].vic.push_back(to);
        grafo[to].vic.push_back(from);
    }


    //cout <<"Grafo inserito" << endl;

    for(int i= 0; i <N; i++)
    {
        grafo[i].nome=i;
    }


    //cout << "Inizio il ciclo di erdos " << endl;
    for(int i=0; i < N; i++)
    {

        erdos(grafo,grafo[i]);
    }


    out << res;




    return 0;
}



void erdos(vector <nodo> grafo, nodo& r)
{
    //cout << "Entro in erdos con il nodo: " << r.nome << endl;
    int erdosNum[N];

    for(int i=0; i<N; i++)
    {
        erdosNum[i]=-1;
        //cout<<"Setto erdos "<<i<< " a -1"<<endl;

    }
    erdosNum[r.nome]=0;

    queue<nodo> S;
    S.push(r);

   // cout << "Coda vuota? " <<S.empty()<< endl;

    while(!(S.empty()))


    {

        nodo a = S.front();
        S.pop();

        for(int vicino: a.vic)
        {
            if (erdosNum[vicino]==-1)
            {
                //cout << "erdos ha valore int_max" << endl;
                erdosNum[vicino]=erdosNum[a.nome]+1;
                //cout << "Res = " << res <<endl;
                if((erdosNum[a.nome]+1)>res)
                {
                    res = erdosNum[a.nome]+1;
                }
                S.push(grafo[vicino]);

            }
        }
    }


}
