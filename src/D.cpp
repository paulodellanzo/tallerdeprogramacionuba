#include "D.h"

D::D() {
	// TODO Auto-generated constructor stub

}
list<string>* D::realizarOpearacion(list<char*>* operandos){
	list<string>* respuesta = new list<string>();
	list<string>::iterator itres;
	char* dividendoChar;
	char* divisorChar;
	if(operandos->size()>4){
		itres=respuesta->begin();
		itres=respuesta->insert(itres,"Error");
		itres++;
		itres=respuesta->insert(itres,"V");
		itres++;
		itres=respuesta->insert(itres,"La division solo acepta dos operandos");
		return respuesta;
	}
	if(strcmp(operandos->front(),"dividendo")==0){// para saber si el primero es divisor o dividendo
		operandos->pop_front();
		dividendoChar=operandos->front();
		operandos->pop_front();
		if(strcmp(operandos->front(),"divisor")==0){
			operandos->pop_front();
			divisorChar=operandos->front();
		}else{
			itres=respuesta->begin();
			itres=respuesta->insert(itres,"Error");
			itres++;
			itres=respuesta->insert(itres,"V");
			itres++;
			itres=respuesta->insert(itres,"No se paso como operando un divisor");
			return respuesta;
		}
	}else{
		if(strcmp(operandos->front(),"divisor")==0){
			operandos->pop_front();
			divisorChar=operandos->front();
			operandos->pop_front();
			if(strcmp(operandos->front(),"dividendo")==0){
				dividendoChar=operandos->front();
			}else{
				itres=respuesta->begin();
				itres=respuesta->insert(itres,"Error");
				itres++;
				itres=respuesta->insert(itres,"V");
				itres++;
				itres=respuesta->insert(itres,"No se paso como operando un dividendo");
				return respuesta;
			}
			dividendoChar=operandos->front();
		}else{
			itres=respuesta->begin();
			itres=respuesta->insert(itres,"Error");
			itres++;
			itres=respuesta->insert(itres,"V");
			itres++;
			itres=respuesta->insert(itres,"No se paso como operando un divisor o dividendo");
			return respuesta;
		}
	}

	if((!esUnNumero(dividendoChar))or(!esUnNumero(divisorChar))){//Corroborar que no hayan puesto por ej 4.3.2
		itres=respuesta->begin();
		itres=respuesta->insert(itres,"Error");
		itres++;
		itres=respuesta->insert(itres,"V");
		itres++;
		itres=respuesta->insert(itres,"No se ingreso un numero en el divisor o dividendo");
		return respuesta;
	}
	//	veamos si en realidad es un entero, lo que es pedido
	double dividendoDouble=atof(dividendoChar);
	double divisorDouble=atof(divisorChar);
	int dividendoInt=(int)dividendoDouble;
	int divisorInt=(int)divisorDouble;
	if(((dividendoDouble - dividendoInt)!=0)or(divisorDouble - divisorInt)!=0){
		itres=respuesta->begin();
		itres=respuesta->insert(itres,"Error");
		itres++;
		itres=respuesta->insert(itres,"V");
		itres++;
		itres=respuesta->insert(itres,"El divisor/dividendo debe ser un numero entero");
		return respuesta;
	}
	if(divisorInt==0){
		itres=respuesta->begin();
		itres=respuesta->insert(itres,"Error");
		itres++;
		itres=respuesta->insert(itres,"V");
		itres++;
		itres=respuesta->insert(itres,"El divisor no puede ser 0");
		return respuesta;
	}
	itres=respuesta->begin();
	itres=respuesta->insert(itres,"Correcto");

	itres++;
	int cociente=(int)(dividendoInt/divisorInt);
	ostringstream sstream;
	sstream << cociente;
	string cocienteString = sstream.str();
	itres=respuesta->insert(itres,"coc");
	itres++;
	itres=respuesta->insert(itres,cocienteString);
	itres++;
	int resto=(int)(dividendoInt%divisorInt);
	ostringstream sstream2;
	sstream2 << resto;
	string restoString = sstream.str();
	itres=respuesta->insert(itres,"res");
	itres++;
	respuesta->insert(itres,restoString);

	return respuesta;
}

D::~D() {
	// TODO Auto-generated destructor stub
}
