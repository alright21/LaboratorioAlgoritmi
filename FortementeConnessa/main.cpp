#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;



int N;
int M;
int risultato = 0;


int *id;


struct nodo
{
    int nome;
    vector <int> vic;
    bool visitato=false;
};

vector <nodo> grafo;
vector <nodo> trasposto;
stack <nodo> S;


void topSort();
void tfdfs(nodo& n,bool visitato[]);
void ccdfs(int conta,int indiceNodo, int id[]);
int cc();

int main()
{

    ifstream in("input.txt");
    ofstream out("output.txt");
    in>>N>>M;

    grafo.resize(N);
    trasposto.resize(N);
    id = new int[N];

    for(int i = 0; i < M; i++)
    {


        int from,to;
        in>>from>>to;

        grafo[from].vic.push_back(to);

        trasposto[to].vic.push_back(from);
    }
    for (int i = 0; i < N; i++)
    {
        grafo[i].nome = i;
    }

    topSort();
    cout << "TopSortFatto"<<endl;

    cout <<"stack size = " << S.size()<<endl;
    int numcomp = cc();

    for(int i=1; i<=numcomp;i++){

        int temporaneo =0;
        for(int z = 0; z < N; z++){
            if(id[z]==i){
                temporaneo++;
            }
            risultato = max(risultato,temporaneo);
        }
    }
    cout << risultato<<endl;


    out <<risultato;




    return 0;
}


void tfdfs(nodo& n,bool visitato[]){

    visitato[n.nome]=true;
    for(int i=0; i < n.vic.size(); i++){
        if(!visitato[n.vic[i]]){
                cout << "Il nodo "<<n.vic[i]<<" non è stato visitato"<<endl;
            tfdfs(grafo[(n.vic[i])],visitato);
        }

    }
    cout << "pusho nodo "<<n.nome<<endl;
    S.push(n);
}

void topSort(){
    bool visitato[N];
    for(int i=0; i < N; i++){
        visitato[i]=false;
    }
    for(int i=0; i < N; i++){

    cout <<"Visito nodo "<<i<<endl;
        if(!visitato[i]){
            cout<<"Applico ricerca sul nodo "<<i<<endl;
            tfdfs(grafo[i],visitato);
        }
    }
}


int  cc(){

    for(int i=0; i < N; i++){
        id[i]=0;

    }
    cout << "id settati a 0"<<endl;
    int conta = 0;
    while(!S.empty()){

        nodo u = S.top();
        cout <<"Nodo in top = " <<u.nome<<endl;
        S.pop();
        if(id[u.nome]==0){

            cout<<"id di " <<u.nome<<" = 0"<<endl;
            conta +=1;
            ccdfs(conta,u.nome,id);
        }
    }
    return conta;
}


void ccdfs(int conta,int indiceNodo, int id[]){

    id[indiceNodo]=conta;
    for(int i=0; i<trasposto[indiceNodo].vic.size();i++){
            cout << "Guardo i vicini del nodo " <<indiceNodo<<endl;
        if(id[trasposto[indiceNodo].vic[i]]==0){
            cout <<"Trovato vicino raggiungibile"<<endl;
                //temporaneo+=1;
            ccdfs(conta,trasposto[indiceNodo].vic[i],id);
        }
    }
    //risultato=max(risultato,temporaneo);
    //cout<<"risultato temporaneo = "<< risultato << endl;
    //temporaneo=1;
}


