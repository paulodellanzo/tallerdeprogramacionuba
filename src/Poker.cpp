#include "Poker.h"

Poker::Poker(list<Carta> cartasMesa,list<Carta> cartasJugador) {

}

list<Carta>* Poker::getMejoresCartas(){
	return mejoresCartas;
}

int Poker::getPuntaje(){
	return puntaje;
}

Poker::~Poker() {

}
