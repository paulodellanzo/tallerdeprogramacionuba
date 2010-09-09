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
	char idOperacionChar=this->parser->getOperacionId(xml);
	ostringstream sstream;
	sstream << idOperacionChar;
	string idOperacionString= sstream.str();
	list<char*>* operandos=this->parser->getOperandos(xml);
	Operacion operacion=this->operaciones->operator [](idOperacionChar);
	list<string>* respuestaDeOperacion=operacion.realizarOpearacion(operandos);
	const char* respuesta=this->parser->getXml(respuestaDeOperacion,idOperacionString);
	return respuesta;
}

Procesador::~Procesador() {
	delete this->operaciones;
}
