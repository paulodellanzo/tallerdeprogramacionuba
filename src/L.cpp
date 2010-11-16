#include "L.h"

L::L() {
	// TODO Auto-generated constructor stub

}

list<string>* L::realizarOpearacion(list<char*>* operandos,list<Jugador*>* jugadores){
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
		it=respuesta->insert(it,"Falta ingresar usuario");
		return respuesta;
	}

	while(it_jugador!=jugadores->end()){
		if((*it_jugador)->getNombre()==usuario){
			respuesta->push_back("Correcto");
			long int apuesta=(*it_jugador)->getUltimaApuesta();
			ostringstream sstream;
			sstream << apuesta;
			string apuestaString = sstream.str();
			respuesta->push_back(apuestaString);
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

L::~L() {
	// TODO Auto-generated destructor stub
}
