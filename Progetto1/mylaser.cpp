
using namespace std;

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <climits>
#include <ctime>
#include <cstdlib>

struct nodo{

	int nome;
	vector <int> archiUscenti;
	vector <int> vicini;

};


struct arco{

	int partenza;
	int arrivo;
	int peso;
	int primoSpegnimento;
	int tempoAcceso;
	int tempoSpento;
	bool attraversabile;
	bool attraversato;

};

vector <nodo> grafo;
vector <arco> listaArchi;
int * erdosNum;

int tempo = 0;
int N;
int M;
const int INFINITO = 1000000; 


int calcolaTempo(int indiceArco, int tempoAttuale);
int trovaArco(int a,int b);
bool baseRaggiungibile();
int calcolaSuccessivo(vector <int> tempi, bool inCoda[]);

void erdos(vector <nodo> grafo, nodo& r);


int main(){
	ifstream in ("input6.txt");
	ofstream out ("output.txt");
	//srand(time(0));


	
	in>>N>>M;

	grafo.resize(N);
	listaArchi.resize(M);

	for(int i=0; i< M; i++){

		int a,b,c,d,e,f;

		in>>a>>b>>c>>d>>e>>f;

		if(c>e){
			listaArchi[i].attraversabile = false;

		}
		else{
			listaArchi[i].attraversabile = true;
			grafo[a].vicini.push_back(b);
			grafo[b].vicini.push_back(a);
		}

		grafo[a].archiUscenti.push_back(i);
		grafo[b].archiUscenti.push_back(i);
		listaArchi[i].partenza = a;
		listaArchi[i].arrivo = b;
		listaArchi[i].peso = c;
		listaArchi[i].primoSpegnimento = d;
		listaArchi[i].tempoSpento = e;
		listaArchi[i].tempoAcceso = f;
		listaArchi[i].attraversato = false;


	}
	bool raggiungibile = baseRaggiungibile();
	//cout<<"L'arrivo è raggiungibile?"<<raggiungibile<<endl;
/*
	for(int i=0; i<M;i++){

		cout <<listaArchi[i].partenza <<" "<<
		listaArchi[i].arrivo<<" "<<
		listaArchi[i].peso <<" "<<
		listaArchi[i].primoSpegnimento<< " "<<
		listaArchi[i].tempoSpento <<" "<<
		listaArchi[i].tempoAcceso <<" "<<
		listaArchi[i].attraversabile<<endl;
	}

	for(int i=0; i <N; i++){

		cout <<"Nodo "<<i<<" ha questi archi: "<<endl;
		for(int j=0; j < grafo[i].archiUscenti.size(); j++){
			cout <<grafo[i].archiUscenti[j]<<" ";
		}cout <<endl;
	}
*/





	


bool *inCoda= new bool[N];

	vector <int> tempi;
	tempi.resize(N);




	//cout << "tempo: " << tempi[N-1] << endl;
	//
	//
	erdos(grafo,grafo[0]);

		/*for(int i=0; i < N; i++){
			cout << erdosNum[i]<<" ";
		}
		cout <<endl;
*/

	if(erdosNum[N-1] == -1){
		out << -1;
	}
	else{

			//INIZIA LA MODIFICA

	//cout <<"N = "<<N<<endl;
	//cout<<"M = "<<M<<endl;
	for(int i=0; i < N; i++){
		inCoda[i]=false;
	}
	for(int i = 0; i < N; i++){
		tempi[i] = INFINITO;
	}
	tempi[0] = 0;
	int nodoAttuale = 0;
	inCoda[0] = true;
	while(nodoAttuale!=N-1){

		//int tmpTempo = INFINITO;
		//int nodoSuccessivo=N-1;
		//int arcoAttraversato;
		//for(int i=0; i < grafo[nodoAttuale].vicini.size();i++){
	
/*

		for(int tmpVicino:grafo[nodoAttuale].vicini){
			//cout<<"Controllo i vicini di "<<nodoAttuale<<": "<<tmpVicino<<endl;
			int indiceArcoTmp = trovaArco(nodoAttuale, tmpVicino);
			//cout<<"Calcolato indiceArcoTmp"<<endl;

			if(listaArchi[indiceArcoTmp].attraversabile){
				if((tempi[nodoAttuale] + calcolaTempo(indiceArcoTmp, tempi[nodoAttuale])) < tempi[tmpVicino]){

					tempi[tmpVicino]=tempi[nodoAttuale] + calcolaTempo(indiceArcoTmp, tempi[nodoAttuale]);
					//cout<<"La distanza tra nodo "<<nodoAttuale<<" e "<<tmpVicino<< " = "<<tempi[tmpVicino]<<endl;

				}

			}

		}*/

		int nodoSuccessivo;

		for(int arcoUscente:grafo[nodoAttuale].archiUscenti){

			if(listaArchi[arcoUscente].attraversabile){

				int tmpVicino;

				if(listaArchi[arcoUscente].partenza==nodoAttuale){
					tmpVicino = listaArchi[arcoUscente].arrivo;
					if(tempi[nodoAttuale]+calcolaTempo(arcoUscente,tempi[nodoAttuale]) < tempi[tmpVicino]){
						tempi[tmpVicino]=tempi[nodoAttuale] + calcolaTempo(arcoUscente, tempi[nodoAttuale]);
					}
				}
				else {
					tmpVicino = listaArchi[arcoUscente].partenza;
					if(tempi[nodoAttuale]+calcolaTempo(arcoUscente,tempi[nodoAttuale]) < tempi[tmpVicino]){

						tempi[tmpVicino]=tempi[nodoAttuale] + calcolaTempo(arcoUscente, tempi[nodoAttuale]);
					}
				}
			}
		}

		nodoAttuale = calcolaSuccessivo(tempi,inCoda);

		
		//cout <<"nodoSuccessivo = "<<nodoAttuale<<endl;
		//listaArchi[arcoAttraversato].attraversato = true;
		//cout <<"Tempo nodo Max = " <<tempi[N-1];
	}






	//FINISCE LA MODIFICA




		out << tempi[N-1];
}
		delete[] inCoda;
	return 0;


}


int calcolaTempo(int indiceArco, int tempoAttuale){

	int tempoFiltrato = tempoAttuale-listaArchi[indiceArco].primoSpegnimento;

	int i=0;



	while (tempoFiltrato>0){
		if(i%2==0){
			tempoFiltrato-=listaArchi[indiceArco].tempoSpento;

		}
		else{
			tempoFiltrato-=listaArchi[indiceArco].tempoAcceso;
		}
		i++;
	}
	if(i%2==0){
		return (-1)*tempoFiltrato+listaArchi[indiceArco].peso;
	}
	else{
		if(((-1)*tempoFiltrato)>=listaArchi[indiceArco].peso)
		{
			return listaArchi[indiceArco].peso;
		}
		else{
			return listaArchi[indiceArco].peso+ (-1)*tempoFiltrato+listaArchi[indiceArco].tempoAcceso;
		}
	}
}


int trovaArco(int a,int b){

	for(int i=0; i < M; i++){
		if((listaArchi[i].partenza==a && listaArchi[i].arrivo==b)||(listaArchi[i].partenza==b && listaArchi[i].arrivo==a)){
			return i;
		}
	}
	return -1;
}


bool baseRaggiungibile(){


	for(int i=0; i<M;i++){
		if((listaArchi[i].partenza==N-1) || (listaArchi[i].arrivo==N-1)){
			return true;
		}
	}
	return false;
}


void erdos(vector <nodo> grafo, nodo& r)
{


	erdosNum = new int[N];
	

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

        for(int vicino: a.vicini)
        {
            if (erdosNum[vicino]==-1)
            {

                erdosNum[vicino]=erdosNum[a.nome]+1;


                S.push(grafo[vicino]);

            }
        }
    }


}



int calcolaSuccessivo(vector <int> tempi, bool inCoda[]){

	//vector <int> minimi;
	int res = N-1;

	for(int i=0; i < N;i++){

		if(!inCoda[i]){

			if(tempi[i]<tempi[res]){

				res = i;
				
			}
		}
	}
	
	

	inCoda[res] = true;
	return res;
	

}