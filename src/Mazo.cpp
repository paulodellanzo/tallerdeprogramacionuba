#include "Mazo.h"

Mazo::Mazo() {

}

void Mazo::mezclar(){
	vector<Carta> cartas;
	char aux[1];

	for(int i=0;i<=12;i++){

		sprintf(aux,"%d",i+1);
		cartas.push_back(Carta("C",aux));
		cartas.push_back(Carta("D",aux));
		cartas.push_back(Carta("P",aux));
		cartas.push_back(Carta("T",aux));

	}

	//Acá hay que desordenar el vector

	for (int j=0;j<52;j++){
		pila.push(Carta(cartas[j].getPalo(),cartas[j].getNumero()));
	}

	return;
}

Carta* Mazo::getCarta(){
	Carta* cartaAux = new Carta(pila.top().getPalo(),pila.top().getNumero());
	pila.pop();
	return cartaAux;
}

Mazo::~Mazo() {

}
