#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <list>


using namespace std;

int N;
int M;
int S;
int conta=0;


struct nodo
{
    int nome;
    vector <int> vic;
    bool visitato=false;
};

vector <nodo> grafo;

void bfs(vector <nodo>& grafo, nodo& n);

int main()
{

    ifstream in("input.txt");
    ofstream out("output.txt");

    in>>N>>M>>S;



    grafo.resize(N);

    for(int i = 0; i < M; i++)
    {


        int from,to;
        in>>from>>to;
        grafo[from].nome=from;
        grafo[from].vic.push_back(to);
    }


    bfs(grafo,grafo[S]);




    out << conta;



    return 0;
}


void bfs(vector <nodo>& grafo, nodo& n)
{

    queue<nodo> S;
    n.visitato=true;
    S.push(n);

    while(!(S.empty()))
    {

        nodo a = S.front();


        S.pop();

        conta+=1;


        for(int i=0; i < a.vic.size(); i++)
        {

            int indiceVicino= a.vic[i];

            if(grafo[indiceVicino].visitato==false)
            {

                grafo[indiceVicino].visitato=true;
                S.push(grafo[indiceVicino]);
            }
        }

    }
}
