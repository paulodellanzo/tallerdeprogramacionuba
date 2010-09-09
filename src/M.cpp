#include "M.h"

M::M() {
	// TODO Auto-generated constructor stub

}
list<char*>* M::realizarOpearacion(list<char*>* operandos){
	list<char*>* respuesta = new list<char*>();
	list<char*>::iterator it=operandos->begin();
	double multiplicacion=1;
	char* multiplicacionChar=new char[100];
	char* multiplicandoChar;
	double multiplicandoDouble;
	while(operandos->size()>0){
		if(operandos->front()=="multiplicando"){
			operandos->pop_front();
			multiplicandoChar=operandos->front();
			operandos->pop_front();
			if((!esUnNumero(multiplicandoChar))){//Corroborar que no hayan puesto por ej 4.3.2
				it=respuesta->begin();
				respuesta->insert(it,"Error");
				it++;
				respuesta->insert(it,"V");
				it++;
				respuesta->insert(it,"Alguno de los operandos de la multiplicacion no es un número");
				return respuesta;
			}
			multiplicandoDouble=atof(multiplicandoChar);
			multiplicacion=multiplicandoDouble * multiplicacion;
		}else{
			it=respuesta->begin();
			respuesta->insert(it,"Error");
			it++;
			respuesta->insert(it,"V");
			it++;
			respuesta->insert(it,"No se pasaron multiplicandos como operandos");
			return respuesta;
		}
	}
	sprintf(multiplicacionChar,"%d",multiplicacion);
	it=respuesta->begin();
	respuesta->insert(it,"Correcto");
	it++;
	respuesta->insert(it,multiplicacionChar);
	return respuesta;
}

M::~M() {
	// TODO Auto-generated destructor stub
}
