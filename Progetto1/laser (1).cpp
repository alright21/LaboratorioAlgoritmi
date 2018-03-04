
using namespace std;

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <climits>

struct nodo{
	int nome;
	int erdos;
	//vector <int> archiUscenti;
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

/*struct priorityInsert{
	bool operator()(const int a, const int b) const{
		return !(a < b);
	}
}*/

vector <nodo> grafo;
vector <arco> listaArchi;

int tempo = 0;
int N;
int M;
const int INFINITO = 1000000; 


int calcolaTempo(int indiceArco, int tempoAttuale);
int trovaArco(int a,int b);
bool baseRaggiungibile();
int findMinNodeTime(vector<int> &tmp_tempi, vector<bool> &tmp_inCoda);
bool codaVuota(vector<bool> &tmp);
void erdos();
bool allOne();

int main(){
	ifstream in ("input.txt");
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

		//grafo[a].archiUscenti.push_back(i);
		//grafo[b].archiUscenti.push_back(i);
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

	/*for(int i=0; i<M;i++){

		cout <<listaArchi[i].partenza <<" "<<
		listaArchi[i].arrivo<<" "<<
		listaArchi[i].peso <<" "<<
		listaArchi[i].primoSpegnimento<< " "<<
		listaArchi[i].tempoSpento <<" "<<
		listaArchi[i].tempoAcceso <<" "<<
		listaArchi[i].attraversabile<<endl;
	}*/

	/*for(int i=0; i <N; i++){

		cout <<"Nodo "<<i<<" ha questi archi: "<<endl;
		for(int j=0; j < grafo[i].archiUscenti.size(); j++){
			cout <<grafo[i].archiUscenti[j]<<" ";
		}cout <<endl;
	}*/

	for(int i = 0; i < N; i++){
		grafo[i].erdos = -1;
	}

	/*if(allOne()){
		erdos();
		cout << "allOne" << endl;
		//cout << "Erdos di n-1: " << grafo[N-1].erdos << endl;
		out << grafo[N-1].erdos;
		return 0;
	}*/
	//erdos();
	//cout << "Erdos di N-1: " << grafo[N-1].erdos << endl;

	//vector <int> coda;
	vector <bool>inCoda;
	//priority_queue <int, vector<int>, priorityInsert> Q;
	vector <int>tempi;
	vector <int>precedente;
	tempi.resize(N);
	inCoda.resize(N);
	precedente.resize(N);
	//coda.resize(N-1);

	for(int i=0; i < N; i++){
		inCoda[i]=true;
	}
	for(int i = 0; i < N; i++){
		tempi[i] = INFINITO;
		precedente[i] = -1;
	}

	tempi[0] = 0;


	for(int tmpVicino : grafo[0].vicini){
		//cout << "tmpVicino: " << tmpVicino << endl;
		int indiceArcoTmp = trovaArco(0, tmpVicino);
		if(listaArchi[indiceArcoTmp].attraversabile /*&& !listaArchi[indiceArcoTmp].attraversato*/){
			//cout <<"indiceArco = "<<indiceArcoTmp<<endl;
			//listaArchi[indiceArcoTmp].attraversato = true;
			int distanza_tmp = tempi[0] + calcolaTempo(indiceArcoTmp, tempi[0]);
			if(distanza_tmp < tempi[tmpVicino]){
				tempi[tmpVicino] = distanza_tmp;
				precedente[tmpVicino] = 0;
			}
		}
	}
	//cout << "Ho finito con i vicini di 0 " << endl;
	//for(int i = 0; i < N; i++)
		//cout << "tempi[i] " << i << " " << tempi[i] << " incoda: " <<inCoda[i]<< endl;

	inCoda[0]=false;
	/*for(int i = 0; i < N; i++){
		cout << "Nodo i: " << i << "\nTempo " << tempi[i] << "\nincoda: " << inCoda[i] <<endl;
		cout << "---" << endl;
	}*/
	bool continua_ciclo=true;
	while(continua_ciclo){
		//cout << "Tempo di N-1: " << tempi[N-1] << endl;
		int nodoAttuale = findMinNodeTime(tempi, inCoda);
		if(nodoAttuale == -1 || nodoAttuale == N-1 || tempi[nodoAttuale] == INFINITO){
			continua_ciclo=false;
			//cout << "Altri nodi non raggiungibili" << endl;
		}
		else{
			inCoda[nodoAttuale]=false;
			
			//cout << "Nodo attuale: " << nodoAttuale << " con tempo: " << tempi[nodoAttuale] << endl;
			//cout << "Precedente di nodo attuale: " << precedente[nodoAttuale] << endl;
			for(int tmpVicino : grafo[nodoAttuale].vicini){
				int indiceArcoTmp = trovaArco(nodoAttuale, tmpVicino);
				if(listaArchi[indiceArcoTmp].attraversabile /*&& !listaArchi[indiceArcoTmp].attraversato*/){
					//cout <<"indiceArco = "<<indiceArcoTmp<<endl;
					//listaArchi[indiceArcoTmp].attraversato = true;
					int distanza_tmp = tempi[nodoAttuale] + calcolaTempo(indiceArcoTmp, tempi[nodoAttuale]);
					if(distanza_tmp < tempi[tmpVicino]){
						//cout << "Aggiorno tempo di tmpVicino " << tmpVicino << " nuovotempo " << distanza_tmp << endl;
						tempi[tmpVicino] = distanza_tmp;
						inCoda[tmpVicino] = true;
						precedente[tmpVicino]= nodoAttuale;
					}
				}
			}
		}
	}


	//cout << "tempo: " << tempi[N-1] << endl;
	if(tempi[N-1] == INFINITO){
		out << -1 << endl;
	}
	else{
		int i = 0;
		out << tempi[N-1] << endl;
		vector<int> cammino;
		int posizione_attuale = N-1;
		//cout << "Precedente di N-1: " << precedente[N-1] << endl;
		while(precedente[posizione_attuale] !=0){
			//cout << "Precedente di : " << posizione_attuale << " = " << precedente[posizione_attuale] << endl;
			int tmp = precedente[posizione_attuale];
			//cammino.resize(cammino.size());
			cammino.push_back(precedente[posizione_attuale]);
			posizione_attuale = tmp;
			i++;
		}
		out << 0 << endl;
		for(i-=1; i >= 0; i-- ){
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

bool codaVuota(vector<bool> &tmp){
	for(int i = 0; i < N; i++){
		if(tmp[i] == true)
			return false;
		}
	return true;
}


int findMinNodeTime(vector<int> &tmp_tempi, vector<bool> &tmp_inCoda){

	int min = INFINITO;
	int min_index = -1;
	for(int i = 0; i < N; i++){
		if((tmp_tempi[i] < min) && tmp_inCoda[i]==true){
			//cout << "Entro nell'if con i=" << i << endl;
			//cout << "E' in coda: " << tmp_inCoda[i] << endl;
			//cout << "Tempo di i: " << tmp_tempi[i] << endl;
			//cout << "Attuale minimo: " << min << endl;
			min = tmp_tempi[i];
			min_index = i;
		}
	}
	if(tmp_tempi[N-1] <= min){
		min_index = N-1;
		//cout << "Ho trovato che N-1 è il nodo minore " << endl;
	}
	
	//cout << "Min_index: " << min_index << endl;
	return min_index;
}

void erdos(){

    queue<int> coda;

    grafo[0].erdos = 0;
    coda.push(0);
    while(!coda.empty()){
        int tmp = coda.front();
        coda.pop();
        //cout << " Tmp.erdos: " << grafo[tmp].erdos << endl;
        for(int vicino : grafo[tmp].vicini){
            if(grafo[vicino].erdos == -1){
                //cout << "Da " << tmp << " vado in " << grafo[vicino].nome << endl;
                grafo[vicino].erdos = grafo[tmp].erdos+1;
                //Sleep(1000);
                //cout << "Erdos di " << grafo[vicino].nome << " ora vale " << grafo[vicino].erdos << endl;
                coda.push(vicino);
            }
        }
    }
}

bool allOne(){
	bool res = true;
	for(int i = 0; i < M; i++){
		if(listaArchi[i].peso != 1 || listaArchi[i].primoSpegnimento!=0 || listaArchi[i].tempoSpento!=INFINITO){
			res = false;
		}
	}
	return res;
}