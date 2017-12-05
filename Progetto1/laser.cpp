
using namespace std;

#include <iostream>
#include <fstream>
#include <vector>

struct nodo{

	int nome;
	vector <int> archiUscenti;

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

int calcolaTempo(int indiceArco);


int main(){
	ifstream in ("input.txt");
	ofstream out ("output.txt");

	int N;
	int M;
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

	for(int i=0; i <N-1; i++){
		if(grafo[i].archiUscenti.size()==1){

			listaArchi[grafo[i].archiUscenti[0]].attraversabile = false;

		}
	}




	/*for(int i=0; i<M;i++){

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
	}*/


	int posizioneAttuale=0;
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
		
		//posizioneAttuale = N-1;
		posizioneAttuale = nodoMinimo;
		tempo = tempo + tempoMinimo;
	}

	//cout << "tempo: " << tempo << endl;

	out << tempo;
	return 0;

}


int calcolaTempo(int indiceArco){

	int tempoFiltrato = tempo-listaArchi[indiceArco].primoSpegnimento;

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

