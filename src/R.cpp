#include "R.h"

R::R() {
	// TODO Auto-generated constructor stub

}

list<char*>* R::realizarOpearacion(list<char*>* operandos){
	list<char*>* respuesta = new list<char*>();
	list<char*>::iterator it=operandos->begin();
	double resta=0;
	char* restaChar=new char[100];
	char* restandoChar;
	double restandoDouble;
	while(operandos->size()>0){
		if(operandos->front()=="sumando"){
			operandos->pop_front();
			restandoChar=operandos->front();
			operandos->pop_front();
			if((!esUnNumero(restandoChar))){//Corroborar que no hayan puesto por ej 4.3.2
				it=respuesta->begin();
				respuesta->insert(it,"Error");
				it++;
				respuesta->insert(it,"Alguno de los operandos de la resta no es un número");
				return respuesta;
			}
			restandoDouble=atof(restandoChar);
			resta-=restandoDouble;
		}
	}
	sprintf(restaChar,"%d",resta);
	it=respuesta->begin();
	respuesta->insert(it,"Correcto");
	it++;
	respuesta->insert(it,restandoChar);
	return respuesta;;
}

R::~R() {
	// TODO Auto-generated destructor stub
}
