#include "Procesador.h"

Procesador::Procesador() {
	this->operaciones=new map<char,Operacion>();
	std::pair<char,S>* nodoS=new std::pair<char,S>('S',S());
	this->operaciones->insert(*nodoS);
	std::pair<char,D>* nodoD=new std::pair<char,D>('D',D());
	this->operaciones->insert(*nodoD);
	std::pair<char,R>* nodoR=new std::pair<char,R>('R',R());
	this->operaciones->insert(*nodoR);
	std::pair<char,M>* nodoM=new std::pair<char,M>('M',M());
	this->operaciones->insert(*nodoM);
	this->parser=new ParserServidor();

}

const char* Procesador::getRespuesta(char* xml){
	string idOperacionString= this->parser->getOperacionId(xml);
	const char* respuesta;
	string res;
	list<char*>* operandos=this->parser->getOperandos(xml);
	idOperacionString=toupper(idOperacionString[0]);
	char idOperacionChar=idOperacionString[0];
	switch(idOperacionChar){
		case('S'):{res="S";break;}
		case('D'):{res="S";break;}
		case('M'):{res="S";break;}
		case('R'):{res="S";break;}
		default:{
			list<string>* conError=new list<string>();
			list<string>::iterator it=conError->begin();
			it=conError->insert(it,"Error");
			it++;
			it=conError->insert(it,"V");
			it++;
			it=conError->insert(it,"Mal id de operacion");
			respuesta=this->parser->getXml(conError,"");
			return respuesta;
		}
	}
	if(res=="S"){
			Operacion operacion=this->operaciones->operator [](idOperacionChar);
			list<string>* respuestaDeOperacion=operacion.realizarOpearacion(operandos);
			respuesta=this->parser->getXml(respuestaDeOperacion,idOperacionString);
			return respuesta;
	}
	return"";

}

Procesador::~Procesador() {
	delete this->operaciones;
}
