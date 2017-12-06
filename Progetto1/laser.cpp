
using namespace std;

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <climits>

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

int tempo = 0;
int N;
int M;
const int INFINITO = 1000000; 


int calcolaTempo(int indiceArco, int tempoAttuale);
int trovaArco(int a,int b);
bool baseRaggiungibile();


int main(){
	ifstream in ("input0.txt");
	ofstream out ("output.txt");

	
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
	cout<<"L'arrivo è raggiungibile?"<<raggiungibile<<endl;

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


	/*int posizioneAttuale=0;
	while(posizioneAttuale < N-1){
		int tempoMinimo = 100000;
		int nodoMinimo;
		//cout << "Posizione attuale " << posizioneAttuale << endl;
		for(int i : grafo[posizioneAttuale].archiUscenti){
			//cout << "Controllo arco: " << listaArchi[i].partenza << " " << listaArchi[i].arrivo << endl;
			if(listaArchi[i].attraversabile && !listaArchi[i].attraversato){
				//cout << "Controllo arco: " << listaArchi[i].partenza << " " << listaArchi[i].arrivo << " con id " << i << endl;
				listaArchi[i].attraversato=true;
				int tempoTmp = calcolaTempo(i);
				//cout << "Tempo minimo: " << tempoTmp << endl;
				if(tempoTmp < tempoMinimo){
					tempoMinimo = tempoTmp;
					if(listaArchi[i].arrivo!= posizioneAttuale){
						nodoMinimo = listaArchi[i].arrivo;
					}
					else{
						nodoMinimo = listaArchi[i].partenza;
					}
					
				}
			}
		}
		
		posizioneAttuale = N-1;
		posizioneAttuale = nodoMinimo;
		tempo = tempo + tempoMinimo;
	}*/



	bool *inCoda= new bool[N];
	queue <int> Q;
	vector <int> tempi;
	tempi.resize(N);

	for(int i=0; i < N; i++){
		inCoda[i]=false;
	}
	for(int i = 0; i < N; i++){
		tempi[i] = INFINITO;
	}

	Q.push(0);
	tempi[0] = 0;
	inCoda[0]=true;
	while(!Q.empty()){

		int nodoAttuale = Q.front();
		Q.pop();
		//cout <<"Nodo Attuale = "<<nodoAttuale<<" con tempi = "<<tempi[nodoAttuale]<<endl;
		inCoda[nodoAttuale]=false;
		for(int tmpVicino : grafo[nodoAttuale].vicini){
			int indiceArcoTmp = trovaArco(nodoAttuale, tmpVicino);
			if(listaArchi[indiceArcoTmp].attraversabile){
				//cout <<"indiceArco = "<<indiceArcoTmp<<endl;
				if((tempi[nodoAttuale] + calcolaTempo(indiceArcoTmp, tempi[nodoAttuale])) < tempi[tmpVicino]){
					tempi[tmpVicino]= tempi[nodoAttuale] + calcolaTempo(indiceArcoTmp, tempi[nodoAttuale]);
					if(!inCoda[tmpVicino]){
						//cout <<"pusho in coda = "<<tmpVicino<<endl;
						Q.push(tmpVicino);
						inCoda[tmpVicino]=true;
					}
				}
			}

			/*for(int i=0;i<N;i++){
				cout <<"tempo "<<i<<" "<<tempi[i]<<" ";
			}cout<<endl;*/
			//cout <<"tempo max = "<<tempi[N-1]<<endl;
			//usleep(500);
		}
	}

	delete[] inCoda;

	//cout << "tempo: " << tempi[N-1] << endl;
	if(tempi[N-1] == INFINITO){
		out << -1;
	}
	else
		out << tempi[N-1];

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