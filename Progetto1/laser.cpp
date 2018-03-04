using namespace std;

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

struct nodo{
	int nome;
	int tempo;
	vector <int> vicini;
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

struct compare {  
    bool operator()(const nodo *l, const nodo *r)  
    {  
        return !(l->tempo < r->tempo);  
    }
};

vector <nodo> grafo;
vector <arco> listaArchi;

int N;
int M;
const int INFINITO = 1000000; 

int calcolaTempo(int indiceArco, int tempoAttuale);

int main(){
	ifstream in("input.txt");
	
	in >> N >> M;

	grafo.resize(N);
	listaArchi.resize(M);

	// Inizializzo tutti i nodi con tempo infinito e nome=i
    for(int i = 0; i < N; i++){
		grafo[i].nome=i;
		grafo[i].tempo = INFINITO;
	}
	// Inizializzo gli archi
	for(int i=0; i< M; i++){

		int a,b,c,d,e,f;

		in>>a>>b>>c>>d>>e>>f;

		if(c > e){
			// Se il tempo che ci metto ad attraversare l'arco è maggiore del tempo che il laser sta spento non ha senso attraversarlo
			listaArchi[i].attraversabile = false;
		}
		else{
			listaArchi[i].attraversabile = true;
			grafo[a].vicini.push_back(b);
			grafo[b].vicini.push_back(a);
			grafo[a].archiUscenti.push_back(i);
			grafo[b].archiUscenti.push_back(i);
		}

		listaArchi[i].partenza = a;
		listaArchi[i].arrivo = b;
		listaArchi[i].peso = c;
		listaArchi[i].primoSpegnimento = d;
		listaArchi[i].tempoSpento = e;
		listaArchi[i].tempoAcceso = f;
		listaArchi[i].attraversato = false;
	}

	// Vettore che identfica se devo considerare il nodo i-esimo per trovare il nodo con tempo[i] minore da cui continuare Dijkstra
	vector <bool>inCoda;
	// Vettore che contiene in posizione i-esima il precedente del nodo i-esimo
	vector <int>precedente;
	// Coda a priorità
	priority_queue <nodo*, vector<nodo*>, compare> queue;

	// Inizializzazione dei vector
	inCoda.resize(N);
	precedente.resize(N);
	for(int i = 0; i < N; i++){
		inCoda[i]=false;
		precedente[i] = -1;
	}

	// Parto con Dijkstra da 0
	int nodoAttuale = 0;
	// Per definizione
	grafo[nodoAttuale].tempo=0;
	// Pusho nella coda il nodo 0
	queue.push(&grafo[nodoAttuale]);
	
	// Dijkstra
	while(!queue.empty()){
		// Nodo attuale definito come il primo nodo in coda (quello con il tempo minore)
		nodoAttuale=queue.top()->nome;
		inCoda[nodoAttuale] = false;
		// Il pop lo faccio qua perchè le priority queue aggiornano l'ordine della proprità dei nodi dopo una pop() e non dopo una top()
		queue.pop();
		//cout << "Precedente di nodo attuale: " << precedente[nodoAttuale] << endl;
		//cout << "Nodo attuale: " << nodoAttuale << " con tempo: " << grafo[nodoAttuale].tempo << endl;
		// Per ogni arco uscente, prendo il nodo destinazione e controllo se posso aggiornare il tempo
		for(int arco : grafo[nodoAttuale].archiUscenti){
			int tmpVicino = -1;
			if(listaArchi[arco].partenza == nodoAttuale)
				tmpVicino = listaArchi[arco].arrivo;
			else
				tmpVicino = listaArchi[arco].partenza;

			int distanza_tmp = grafo[nodoAttuale].tempo + calcolaTempo(arco, grafo[nodoAttuale].tempo);
			if(distanza_tmp < grafo[tmpVicino].tempo){
				grafo[tmpVicino].tempo = distanza_tmp;
				precedente[tmpVicino] = nodoAttuale;
				if(!inCoda[tmpVicino]){
					queue.push(&grafo[tmpVicino]);
					inCoda[tmpVicino] = true;
				}	
			}
		}

	}

	ofstream out("output.txt");
	//cout << "tempo: " << tempi[N-1] << endl;
	if(grafo[N-1].tempo == INFINITO){
		out << -1 << endl;
	}
	else{
		int i = 0;
		out << grafo[N-1].tempo << endl;
		vector<int> cammino;
		int posizione_attuale = N-1;
		//cout << "Precedente di N-1: " << precedente[N-1] << endl;
		while(precedente[posizione_attuale] !=0){
			//cout << "Precedente di : " << posizione_attuale << " = " << precedente[posizione_attuale] << endl;
			int tmp = precedente[posizione_attuale];
			cammino.push_back(precedente[posizione_attuale]);
			posizione_attuale = tmp;
			i++;
		}
		out << 0 << endl;
		for(i-=1; i >= 0; i--){
			out << cammino[i] << endl;
		}
		out << N-1 << endl;
	}

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
		//cout << "I%2 Indice arco: " << indiceArco << " peso: " << (-1)*tempoFiltrato+listaArchi[indiceArco].peso << endl;
		return (-1)*tempoFiltrato+listaArchi[indiceArco].peso;
	}
	else{
		if(((-1)*tempoFiltrato)>=listaArchi[indiceArco].peso)
		{
			//cout << "i%1 if Indice arco: " << indiceArco << " peso: " << listaArchi[indiceArco].peso << endl;
			return listaArchi[indiceArco].peso;
		}
		else{
			//cout << "i%1 else Indice arco: " << indiceArco << " peso: " << listaArchi[indiceArco].peso+ (-1)*tempoFiltrato+listaArchi[indiceArco].tempoAcceso << endl;
			return listaArchi[indiceArco].peso+ (-1)*tempoFiltrato+listaArchi[indiceArco].tempoAcceso;
		}
	}
}