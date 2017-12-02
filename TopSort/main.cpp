#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;



int N;
int M;


struct nodo
{
    int nome;
    vector <int> vic;
    bool visitato=false;
};

vector <nodo> grafo;
stack <nodo> S;


void topSort();
void tfdfs(nodo& n,bool visitato[]);

int main()
{

    ifstream in("input.txt");
    ofstream out("output.txt");
    in>>N>>M;

    grafo.resize(N);

    for(int i = 0; i < M; i++)
    {


        int from,to;
        in>>from>>to;

        grafo[from].vic.push_back(to);
    }
    for (int i = 0; i < N; i++)
    {
        grafo[i].nome = i;
    }

    topSort();

    //cout <<"stack size = " << S.size()<<endl;
    for(int i=0; i < N;i++){
       out << S.top().nome<<" ";
        S.pop();
    }




    return 0;
}


void tfdfs(nodo& n,bool visitato[]){

    visitato[n.nome]=true;
    for(int i=0; i < n.vic.size(); i++){
        if(!visitato[n.vic[i]]){
                //cout << "Il nodo "<<n.vic[i]<<" non è stato visitato"<<endl;
            tfdfs(grafo[(n.vic[i])],visitato);
        }

    }
    //cout << "pusho nodo "<<n.nome<<endl;
    S.push(n);
}

void topSort(){
    bool visitato[N];
    for(int i=0; i < N; i++){
        visitato[i]=false;
    }
    for(int i=0; i < N; i++){

    //cout <<"Visito nodo "<<i<<endl;
        if(!visitato[i]){
          //  cout<<"Applico ricerca sul nodo "<<i<<endl;
            tfdfs(grafo[i],visitato);
        }
    }
}


