#include "S.h"

S::S() {
	// TODO Auto-generated constructor stub

}

list<string>* S::realizarOpearacion(list<char*>* operandos){
	list<string>* respuesta = new list<string>();
	list<string>::iterator it=respuesta->begin();
	double suma=0;
	char* sumandoChar;
	double sumandoDouble;
	while(operandos->size()>0){
		printf(operandos->front());
		printf("\n");
		if(strcmp(operandos->front(),"sum")){
			operandos->pop_front();
			sumandoChar=operandos->front();
			operandos->pop_front();
			if((!esUnNumero(sumandoChar))){//Corroborar que no hayan puesto por ej 4.3.2
				it=respuesta->begin();
				it=respuesta->insert(it,"Error");
				it++;
				it=respuesta->insert(it,"V");
				it++;
				it=respuesta->insert(it,"Alguno de los operandos de la suma no es un número");
				return respuesta;
			}
			sumandoDouble=atof(sumandoChar);
			suma+=sumandoDouble;
		}else{
			it=respuesta->begin();
			it=respuesta->insert(it,"Error");
			it++;
			it=respuesta->insert(it,"V");
			it++;
			it=respuesta->insert(it,"No se pasaron sumandos como operandos");
			return respuesta;
		}
	}
	ostringstream sstream;
	sstream << suma;
	string sumaString = sstream.str();
	respuesta->push_back("Correcto");
	respuesta->push_back("sum");
	respuesta->push_back(sumaString);
	return respuesta;
}

S::~S() {
	// TODO Auto-generated destructor stub
}
