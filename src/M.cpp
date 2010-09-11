#include "M.h"

M::M() {
	// TODO Auto-generated constructor stub

}
list<string>* M::realizarOpearacion(list<char*>* operandos){
	list<string>* respuesta = new list<string>();
	list<string>::iterator itres=respuesta->begin();
	double multiplicacion=1;
	char* multiplicandoChar;
	double multiplicandoDouble;
	while(operandos->size()>0){
		if(strcmp(operandos->front(),"mul")==0){
			operandos->pop_front();
			multiplicandoChar=operandos->front();
			operandos->pop_front();
			if((!esUnNumero(multiplicandoChar))){//Corroborar que no hayan puesto por ej 4.3.2
				itres=respuesta->begin();
				itres=respuesta->insert(itres,"Error");
				itres++;
				itres=respuesta->insert(itres,"V");
				itres++;
				itres=respuesta->insert(itres,"Alguno de los operandos de la multiplicacion no es un número");
				return respuesta;
			}
			multiplicandoDouble=atof(multiplicandoChar);
			multiplicacion=multiplicandoDouble * multiplicacion;
		}else{
			itres=respuesta->begin();
			itres=respuesta->insert(itres,"Error");
			itres++;
			itres=respuesta->insert(itres,"V");
			itres++;
			itres=respuesta->insert(itres,"No se pasaron multiplicandos como operandos");
			return respuesta;
		}
	}
	ostringstream sstream;
	sstream << multiplicacion;
	string multiplicacionString = sstream.str();
	itres=respuesta->begin();
	itres=respuesta->insert(itres,"Correcto");
	itres++;
	itres=respuesta->insert(itres,"mul");
	itres++;
	itres=respuesta->insert(itres,multiplicacionString);
	return respuesta;
}

M::~M() {
	// TODO Auto-generated destructor stub
}
