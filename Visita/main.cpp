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

    //cout << "Numero di nodi:" << N<<endl;
    //cout << "Numero di archi: "<<M<<endl;
    //cout<<"Nodo da visitare: " <<S<<endl;

    grafo.resize(N);

    for(int i = 0; i < M; i++)
    {


        int from,to;
        in>>from>>to;
        grafo[from].nome=from;
        grafo[from].vic.push_back(to);
    }
   // cout <<"Grafo creato" << endl;

    bfs(grafo,grafo[S]);

    //cout << "bfs fatta" << endl;

    //cout <<"Conta = " << conta <<endl;


    out << conta;



    return 0;
}


void bfs(vector <nodo>& grafo, nodo& n)
{

    queue<nodo> S;
    n.visitato=true;
    S.push(n);
    //cout << "Inserito nodo " <<endl;



    //cout << "Dimensione coda: " <<S.size() << endl;
    while(!(S.empty()))
    {

        nodo a = S.front();

      // queue<nodo> prova = S;


       /* while (!prova.empty())
        {

            cout << prova.front().nome<<" ";
            prova.pop();
        }
        cout << endl;*/


        S.pop();

        conta+=1;
       // cout << "conta = " <<conta << endl;
       // cout << "Vicini del nodo a" <<endl;

        for(int i=0; i < a.vic.size(); i++)
        {

            int indiceVicino= a.vic[i];
           // cout << "___Indice vicino: " <<indiceVicino <<endl;
            //nodo vicino = grafo[indiceVicino];
            if(grafo[indiceVicino].visitato==false)
            {

                //cout <<"Nodo non visitato!" <<endl;
                grafo[indiceVicino].visitato=true;
                S.push(grafo[indiceVicino]);




            }
        }

    }
}
