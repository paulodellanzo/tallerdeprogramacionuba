#include "J.h"
#include <iostream>

J::J() {

}

list<string>* J::realizarOperacion(list<Jugador*>* jugadores){
	list<string>* respuesta = new list<string>();
	list<string>::iterator it;
	if(jugadores->size() < 0 || jugadores->size() > 6 ){
		it=respuesta->begin();
		it=respuesta->insert(it,"Error");
		it++;
		it=respuesta->insert(it,"V");
		it++;
		it=respuesta->insert(it,"Cantidad de Jugadores invalida");
		return respuesta;
	}
	list<Jugador*>::iterator it2;
	it2 = jugadores->begin();
	for (unsigned int i = 0; i <jugadores->size(); i++) {
		if ((*it2)->getNombre() != "") {
			respuesta->push_back((*it2)->getNombre());
			ostringstream sstream;
			sstream << (*it2)->plataRestante();
			string plataRestante = sstream.str();
			respuesta->push_back(plataRestante);
			it2++;
		} else {
			it = respuesta->begin();
			it = respuesta->insert(it, "Error");
			it++;
			it = respuesta->insert(it, "V");
			it++;
			it = respuesta->insert(it, "Los jugadores tienen que tener un nombre");
			return respuesta;
		}
	}
	respuesta->push_front("Correcto");

	return respuesta;

}
J::~J() {

}
