#include "Carta.h"

Carta::Carta(string palo, string numero) {
	// TODO Auto-generated constructor stub
	//if((int)numero <=13 || (int)numero >= 1)
	this->numero = numero;
	this->palo = palo;
}

string Carta::getPalo(){
	return this->palo;
}

string Carta::getNumero(){
	return this->numero;
}

Carta::~Carta() {
	// TODO Auto-generated destructor stub
}
