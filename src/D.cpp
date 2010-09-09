#include "D.h"

D::D() {
	// TODO Auto-generated constructor stub

}
list<char*>* D::realizarOpearacion(list<char*>* operandos){
	list<char*>* respuesta = new list<char*>();
	list<char*>::iterator it=operandos->begin();
	char* dividendoChar;
	char* divisorChar;
	if(operandos->size()>4){
		it=respuesta->begin();
		respuesta->insert(it,"Error");
		it++;
		respuesta->insert(it,"V");
		it++;
		respuesta->insert(it,"La division solo acepta dos operandos");
		return respuesta;
	}
	if(operandos->front()=="dividendo"){// para saber si el primero es divisor o dividendo
		operandos->pop_front();
		dividendoChar=operandos->front();
		operandos->pop_front();
		if(operandos->front()=="divisor"){
			divisorChar=operandos->front();
		}else{
			it=respuesta->begin();
			respuesta->insert(it,"Error");
			it++;
			respuesta->insert(it,"V");
			it++;
			respuesta->insert(it,"No se paso como operando un divisor");
			return respuesta;
		}
	}else{
		if(operandos->front()=="divisor"){
			operandos->pop_front();
			divisorChar=operandos->front();
			operandos->pop_front();
			if(operandos->front()=="divisor"){
				dividendoChar=operandos->front();
			}else{
				it=respuesta->begin();
				respuesta->insert(it,"Error");
				it++;
				respuesta->insert(it,"V");
				it++;
				respuesta->insert(it,"No se paso como operando un dividendo");
				return respuesta;
			}
			dividendoChar=operandos->front();
		}else{
			it=respuesta->begin();
			respuesta->insert(it,"Error");
			it++;
			respuesta->insert(it,"V");
			it++;
			respuesta->insert(it,"No se paso como operando un divisor o dividendo");
			return respuesta;
		}
	}

	if((!esUnNumero(dividendoChar))or(!esUnNumero(divisorChar))){//Corroborar que no hayan puesto por ej 4.3.2
		it=respuesta->begin();
		respuesta->insert(it,"Error");
		it++;
		respuesta->insert(it,"V");
		it++;
		respuesta->insert(it,"No se ingreso un numero en el divisor o dividendo");
		return respuesta;
	}
	//	veamos si en realidad es un entero, lo que es pedido
	double dividendoDouble=atof(dividendoChar);
	double divisorDouble=atof(divisorChar);
	int dividendoInt=(int)dividendoDouble;
	int divisorInt=(int)divisorDouble;
	if(((dividendoDouble - dividendoInt)!=0.0)or(divisorDouble - divisorInt)!=0.0){
		it=respuesta->begin();
		respuesta->insert(it,"Error");
		it++;
		respuesta->insert(it,"V");
		it++;
		respuesta->insert(it,"El divisor/dividendo debe ser un numero entero");
		return respuesta;
	}
	if(divisorInt==0){
		it=respuesta->begin();
		respuesta->insert(it,"Error");
		it++;
		respuesta->insert(it,"V");
		it++;
		respuesta->insert(it,"El divisor no puede ser 0");
		return respuesta;
	}
	it=respuesta->begin();
	respuesta->insert(it,"Correcto");

	it++;
	int cociente=(int)(dividendoInt/divisorInt);
	char* cocienteChar= new char[50];
	sprintf(cocienteChar,"%d",cociente);
	respuesta->insert(it,"Cociente");
	it++;
	respuesta->insert(it,cocienteChar);

	it++;
	int resto=(dividendoInt%divisorInt);
	char* restoChar=new char[50];
	sprintf(restoChar,"%d",resto);
	respuesta->insert(it,"Resto");
	it++;
	respuesta->insert(it,restoChar);

	return respuesta;
}

D::~D() {
	// TODO Auto-generated destructor stub
}
