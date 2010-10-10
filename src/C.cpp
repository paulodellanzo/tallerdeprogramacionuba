#include "C.h"

C::C() {

}

list<string>* C::realizarOperacion(list<Carta*>* cartas){
	list<string>* respuesta = new list<string>();
	list<string>::iterator it;
	if(cartas->size() < 0 || cartas->size() > 17 ){
		it=respuesta->begin();
		it=respuesta->insert(it,"Error");
		it++;
		it=respuesta->insert(it,"V");
		it++;
		it=respuesta->insert(it,"Cantidad de Cartas invalida");
		return respuesta;
	}
	it = respuesta->begin();
	it = respuesta->insert(it, "Correcto");
	it++;
	list<Carta*>::iterator it2;
	it2 = cartas->begin();
	while (cartas->size() > 0) {
		it = respuesta->insert(it, cartas->front()->getPalo());
		it++;
		it = respuesta->insert(it, cartas->front()->getNumero());
		it++;
		it2++;
	}
	return respuesta;

}

C::~C() {

}
