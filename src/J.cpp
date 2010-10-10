#include "J.h"

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
	it = respuesta->begin();
	list<Jugador*>::iterator it2;
	it2 = jugadores->begin();
	ostringstream sstream;
	while (jugadores->size() > 0) {
		if (jugadores->front()->getNombre() != "") {
			it = respuesta->insert(it, jugadores->front()->getNombre());
			it++;
			sstream << jugadores->front()->plataRestante();
			string plataRestante = sstream.str();
			it = respuesta->insert(it, plataRestante);
			it++;
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
	it = respuesta->begin();
	it = respuesta->insert(it, "Correcto");
	it++;
	return respuesta;

}
J::~J() {

}
