#include "S.h"

S::S() {
	// TODO Auto-generated constructor stub

}

list<char*>* S::realizarOpearacion(list<char*>* operandos){
	list<char*>* respuesta = new list<char*>();
	list<char*>::iterator it=operandos->begin();
	double suma=0;
	char* sumaChar=new char[100];
	char* sumandoChar;
	double sumandoDouble;
	while(operandos->size()>0){
		if(operandos->front()=="sum"){
			operandos->pop_front();
			sumandoChar=operandos->front();
			operandos->pop_front();
			if((!esUnNumero(sumandoChar))){//Corroborar que no hayan puesto por ej 4.3.2
				it=respuesta->begin();
				respuesta->insert(it,"Error");
				it++;
				respuesta->insert(it,"V");
				it++;
				respuesta->insert(it,"Alguno de los operandos de la suma no es un número");
				return respuesta;
			}
			sumandoDouble=atof(sumandoChar);
			suma+=sumandoDouble;
		}else{
			it=respuesta->begin();
			respuesta->insert(it,"Error");
			it++;
			respuesta->insert(it,"V");
			it++;
			respuesta->insert(it,"No se pasaron sumandos como operandos");
			return respuesta;
		}
	}
	sprintf(sumaChar,"%d",suma);
	it=respuesta->begin();
	respuesta->insert(it,"Correcto");
	it++;
	respuesta->insert(it,"sum");
	it++;
	respuesta->insert(it,sumandoChar);
	return respuesta;
}

S::~S() {
	// TODO Auto-generated destructor stub
}
