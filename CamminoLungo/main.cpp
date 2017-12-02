#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>

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
int *distanza;


void topSort();
void tfdfs(nodo& n,bool visitato[]);
int camminoLungo();

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
    int risultato = camminoLungo();

    out << risultato;



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

int camminoLungo(){

    distanza = new int[N];
    for (int i=0; i <N; i++){
        distanza[i] = 0;
    }
    //int distanzaTemporanea = 0;
    while (!S.empty()){
       //cout << "Stack non vuoto"<<endl;
        nodo n = S.top();
       // cout <<"estraggo nodo "<<n.nome<<endl;
        S.pop();
        //distanzaTemporanea+=1;
        for (int i=0; i < n.vic.size(); i++){
            
            if(distanza[n.vic[i]]==0){

                 
                // cout <<"distanza di n ="<<distanza[n.nome]<<endl;
                distanza[n.vic[i]] = distanza[n.nome]+1;
               // cout <<"distanza di "<<n.vic[i]<<" ="<<distanza[n.vic[i]]<<endl;
               // cout << "aggiorno distanza del nodo vicino "<<n.vic[i]<<" = "<<distanza[n.vic[i]]<<endl;

            }
            else{
                // cout << "distanza tra "<<n.nome<< " e "<<i<<" = "<<distanza[i]<<endl;
                distanza[n.vic[i]] = max(distanza[n.vic[i]],(distanza[n.nome]+1));
            }


        }
    }
    for (int i=0; i < N; i++){
        //cout<<"distanza " <<i<<" = " << distanza[i]<<endl;
    }
    return *max_element(distanza,distanza+N);
}