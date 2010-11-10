#include "B.h"

B::B() {}

list<string>* B::realizarOpearacion(list<char*>* operandos,	list<Jugador*>* jugadores){
	list<string>* respuesta = new list<string>();
	list<string>::iterator it=respuesta->begin();
	list<Jugador*>::iterator it_jugador=jugadores->begin();
	string usuario;

	if(strcmp(operandos->front(),"usuario")==0){
		operandos->pop_front();
		usuario=operandos->front();
		operandos->pop_front();
	}else{
		it=respuesta->begin();
		it=respuesta->insert(it,"Error");
		it++;
		it=respuesta->insert(it,"V");
		it++;
		it=respuesta->insert(it,"Falta ingresar usuario o password");
		return respuesta;
	}
	while(it_jugador!=jugadores->end()){
		if((*it_jugador)->getNombre()==usuario){
			respuesta->push_back("Correcto");
			list<Carta*>::iterator it2;
			list<Carta*> * cartas=(*it_jugador)->getCartas();
			it2 = cartas->begin();
			for (unsigned int i = 0; i < cartas->size(); i++) {
				respuesta->push_back((*it2)->getPalo());
				respuesta->push_back((*it2)->getNumero());
				it2++;
			}
			return respuesta;
		}
		it_jugador++;
	}
	it=respuesta->begin();
	it=respuesta->insert(it,"Error");
	it++;
	it=respuesta->insert(it,"V");
	it++;
	it=respuesta->insert(it,"No existe el jugador");
	return respuesta;
}

B::~B() {}
