#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

struct nodo
{

    int nome;
    vector<int> vic;
    bool visitato = false;

};

vector<nodo> grafo;
vector<nodo> trasposto;

void erdos(vector <nodo> grafo, nodo& r);
void numCammini();

int N;
int M;
int S;
int T;
int *erdosNum;
int res =0;


int main()

{
    ifstream in("input.txt");
    ofstream out("output.txt");

    in>>N>>M>>S>>T;



    grafo.resize(N);
    trasposto.resize(N);
    erdosNum = new int[N];



    for(int i = 0; i < M; i++)
    {


        int from,to;
        in>>from>>to;
        grafo[from].vic.push_back(to);

        trasposto[to].vic.push_back(from);


    }

    for(int i= 0; i <N; i++)
    {
        grafo[i].nome=i;
        trasposto[i].nome=i;
    }

 /*   for(int i=0; i < N;i++){
        cout << trasposto[i].nome<<endl;
        for(int j=0; j<trasposto[i].vic.size(); j++){
            cout <<"__"<<trasposto[i].vic[j];
        }
        cout <<endl;
    }*/


    erdos(grafo,grafo[S]);
    numCammini();

   out <<erdosNum[T]<<" "<<res;
    return 0;
}


void erdos(vector <nodo> grafo, nodo& r)
{



    for(int i=0; i<N; i++)
    {
        erdosNum[i]=-1;


    }
    erdosNum[r.nome]=0;

    queue<nodo> S;
    S.push(r);


    while(!(S.empty()))


    {

        nodo a = S.front();
        S.pop();

        for(int vicino: a.vic)
        {
            if (erdosNum[vicino]==-1)
            {

                erdosNum[vicino]=erdosNum[a.nome]+1;


                S.push(grafo[vicino]);

            }
        }
    }


}

void numCammini(){

    queue <nodo> Q;
    //cout <<"Nome di T = " << trasposto[T].nome<<endl;
    Q.push(trasposto[T]);
    //cout <<"Inserisco nodo "<<T<<endl;
    while(!Q.empty()){

        nodo a = Q.front();
        Q.pop();
        for(int vicino: a.vic){

            if(erdosNum[vicino]==(erdosNum[a.nome]-1)){
                    //cout <<"erdosNum del vicino == " << erdosNum[vicino]<<endl;
                if(erdosNum[vicino]==0){
                    res+=1;

                }
                else{
                    Q.push(trasposto[vicino]);
                }
            }
        }

    }
}
