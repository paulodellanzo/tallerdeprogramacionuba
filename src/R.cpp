#include "R.h"

R::R() {
	// TODO Auto-generated constructor stub

}

list<string>* R::realizarOpearacion(list<char*>* operandos){
	list<string>* respuesta = new list<string>();
	list<string>::iterator it=respuesta->begin();
	bool esElPrimero=true;
	double resta=0;
	char* restandoChar;
	double restandoDouble;
	if(operandos->size()<4){
		it=respuesta->begin();
		it=respuesta->insert(it,"Error");
		it++;
		it=respuesta->insert(it,"V");
		it++;
		it=respuesta->insert(it,"Para la resta debe haber como mínimo dos operandos");
		return respuesta;
	}
	while(operandos->size()>0){
		if(strcmp(operandos->front(),"res")==0){
			operandos->pop_front();
			restandoChar=operandos->front();
			operandos->pop_front();
			if((!esUnNumero(restandoChar))){//Corroborar que no hayan puesto por ej 4.3.2
				it=respuesta->begin();
				it=respuesta->insert(it,"Error");
				it++;
				it=respuesta->insert(it,"V");
				it++;
				it=respuesta->insert(it,"Alguno de los operandos de la resta no es un número");
				return respuesta;
			}
			restandoDouble=atof(restandoChar);
			if(esElPrimero){
				resta=restandoDouble;
				esElPrimero=false;
			}else{
				resta-=restandoDouble;}
		}else{
			it=respuesta->begin();
			it=respuesta->insert(it,"Error");
			it++;
			it=respuesta->insert(it,"V");
			it++;
			it=respuesta->insert(it,"No se pasaron restandos como operandos");
			return respuesta;
		}
	}
	ostringstream sstream;
	sstream << resta;
	string restaString = sstream.str();
	it=respuesta->begin();
	it=respuesta->insert(it,"Correcto");
	it++;
	it=respuesta->insert(it,"res");
	it++;
	it=respuesta->insert(it,restaString);
	return respuesta;;
}

R::~R() {
	// TODO Auto-generated destructor stub
}
