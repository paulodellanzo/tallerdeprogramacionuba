#include "D.h"

D::D() {
	// TODO Auto-generated constructor stub

}
list<string>* D::realizarOperacion(list<char*>* operandos, Jugador * jugador){
	list<string>* respuesta = new list<string>();
	list<string>::iterator it=respuesta->begin();
	char * apuesta;

	if(strcmp(operandos->front(),"Poso")==0){
		operandos->pop_front();
		apuesta=operandos->front();
		operandos->pop_front();
	}else{
		it=respuesta->begin();
		it=respuesta->insert(it,"Error");
		it++;
		it=respuesta->insert(it,"V");
		it++;
		it=respuesta->insert(it,"Falta ingresar apuesta");
		return respuesta;
	}

	int apuestaInt=atoi(apuesta);
	if(apuestaInt==0)
		jugador->dejarDeJugar();
	int apuestaAux=0 - apuestaInt;
	jugador->modificarPlataEn(apuestaAux);
	apuestaInt+=jugador->getUltimaApuesta();
	jugador->setUltimaApuesta(apuestaInt);

	ostringstream sstream;
	sstream << apuestaInt;
	string apuestaString = sstream.str();

	it=respuesta->begin();
	it=respuesta->insert(it,"Correcto");
	it++;
	it=respuesta->insert(it,"Poso");
	it++;
	it=respuesta->insert(it,apuestaString);
	return respuesta;
}

D::~D() {
	// TODO Auto-generated destructor stub
}
