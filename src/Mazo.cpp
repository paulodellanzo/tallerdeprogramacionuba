#include "Mazo.h"

Mazo::Mazo() {
	this->semilla=1;
	this->mezclar();
}

void Mazo::mezclar(){
	while(!pila.empty()){
		pila.pop();
	}

	vector<Carta> cartas;
	char aux[1];
	int random;
	int vectorAleatorio[51];

	for(int i=0;i<=51;i++){
		vectorAleatorio[i]=i;
	}

	for(int k=0;k<5;k++){
		for(int i=0;i<=51;i++){
			srand(i*time(NULL)*(this->semilla));
			random=rand()%52;
			if(random!=i){
				vectorAleatorio[random]=vectorAleatorio[i]+vectorAleatorio[random];
				vectorAleatorio[i]=vectorAleatorio[random]-vectorAleatorio[i];
				vectorAleatorio[random]=vectorAleatorio[random]-vectorAleatorio[i];
			}
		}
	}


	for(int i=0;i<=12;i++){
		sprintf(aux,"%d",i+1);
		cartas.push_back(Carta("corazones",aux));
		cartas.push_back(Carta("diamantes",aux));
		cartas.push_back(Carta("picas",aux));
		cartas.push_back(Carta("treboles",aux));
	}

	for (int j=0;j<52;j++){
		pila.push(Carta(cartas[vectorAleatorio[j]].getPalo(),cartas[vectorAleatorio[j]].getNumero()));
	}

	for(int i=0;i<52;i++){
		cartas.erase(cartas.begin()+i);
	}
	this->semilla=this->semilla+1;
	return;
}

Carta* Mazo::getCarta(){
	Carta* cartaAux = new Carta(pila.top().getPalo(),pila.top().getNumero());
	pila.pop();
	return cartaAux;
}

Mazo::~Mazo() {
	while(!pila.empty()){
		pila.pop();
	}
}
