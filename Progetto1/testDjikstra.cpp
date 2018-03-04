


{
	
	Q.enque(grafo[0]);

	int nodoInserito = Q.end().nome;
	while(nodoInserito!=(N-1)){
		nodo n = Q.end();
		n.visitato = true;
		for (int i: grafo[n.nome].archiUscenti){
			if(attraversabile && !n.visitato){

			}
		}
	}
}