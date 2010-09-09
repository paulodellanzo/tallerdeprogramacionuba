#include "R.h"

R::R() {
	// TODO Auto-generated constructor stub

}

list<string>* R::realizarOpearacion(list<char*>* operandos){
	list<string>* respuesta = new list<string>();
	list<string>::iterator it=respuesta->begin();
	double resta=0;
	char* restandoChar;
	double restandoDouble;
	while(operandos->size()>0){
		if(operandos->front()=="res"){
			operandos->pop_front();
			restandoChar=operandos->front();
			operandos->pop_front();
			if((!esUnNumero(restandoChar))){//Corroborar que no hayan puesto por ej 4.3.2
				it=respuesta->begin();
				respuesta->insert(it,"Error");
				it++;
				respuesta->insert(it,"V");
				it++;
				respuesta->insert(it,"Alguno de los operandos de la resta no es un número");
				return respuesta;
			}
			restandoDouble=atof(restandoChar);
			resta-=restandoDouble;
		}else{
			it=respuesta->begin();
			respuesta->insert(it,"Error");
			it++;
			respuesta->insert(it,"V");
			it++;
			respuesta->insert(it,"No se pasaron restandos como operandos");
			return respuesta;
		}
	}
	ostringstream sstream;
	sstream << resta;
	string restaString = sstream.str();
	it=respuesta->begin();
	respuesta->insert(it,"Correcto");
	it++;
	respuesta->insert(it,"res");
	it++;
	respuesta->insert(it,restaString);
	return respuesta;;
}

R::~R() {
	// TODO Auto-generated destructor stub
}
