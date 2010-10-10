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
	respuesta->push_back("Correcto");
	list<Carta*>::iterator it2;
	it2 = cartas->begin();
	for (unsigned int i = 0; i < cartas->size(); i++) {
		respuesta->push_back((*it2)->getPalo());
		respuesta->push_back((*it2)->getNumero());
		it2++;
	}
	return respuesta;

}

C::~C() {

}
