#include "Procesador.h"
using namespace std;
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <fstream>

Procesador::Procesador(int i) {
	this->parser=new ParserServidor();

}



char* Procesador::getRespuesta(char* xml){
	ostringstream sstream;
	sstream << xml;
	string paraVerCuantoPesa = sstream.str();
	char xmlAux[paraVerCuantoPesa.size()];
	char xmlAux2[paraVerCuantoPesa.size()];
	for(unsigned int i=0;i<paraVerCuantoPesa.size();i++){xmlAux[i]=xml[i];xmlAux2[i]=xml[i];}
	string idOperacionString= this->parser->getOperacionId(xmlAux);
	char* respuesta=" ";
	string res;
	list<char*>* operandos=this->parser->getOperandos(xmlAux2);
	idOperacionString=toupper(idOperacionString[0]);
	char idOperacionChar=idOperacionString[0];
	Operacion* operacion;
	switch(idOperacionChar){
		case('S'):{res="S";operacion=new S();break;}
		case('D'):{res="S";operacion=new D();break;}
		case('M'):{res="S";operacion=new M();break;}
		case('R'):{res="S";operacion=new R();break;}
		case('P'):{/*Devuelvo el POSO ACUMULADO en un xml*/}
		case('J'):{/*Devuelvo todos los jugadores en un xml*/}
		case('C'):{/*Devuelvo las cartas que salieron en un xml*/}
		default:{
			list<string>* conError=new list<string>();
			list<string>::iterator it=conError->begin();
			it=conError->insert(it,"Error");
			it++;
			it=conError->insert(it,"V");
			it++;
			it=conError->insert(it,"Mal id de operacion");
			respuesta=this->parser->getXml(conError,"");
			delete conError;
			delete operandos;
			return respuesta;
		}
	}
	if(res=="S"){
			list<string>* respuestaDeOperacion=operacion->realizarOpearacion(operandos);
			respuesta=this->parser->getXml(respuestaDeOperacion,idOperacionString);
			delete respuestaDeOperacion;
			delete operandos;
			return respuesta;
	}
	return"";

}

Procesador * Procesador::instanciaUnica;

Procesador *Procesador::instancia(){
		    if (!instanciaUnica)
		    	instanciaUnica =new Procesador(1);
		    return instanciaUnica;
}

string Procesador::getPathArchivo(){
	return this->path;
}

bool Procesador::enviarArchivo(char * xml){
	ostringstream sstream;
	sstream << xml;
	string paraVerCuantoPesa = sstream.str();
	char xmlAux[paraVerCuantoPesa.size()];
	for(unsigned int i=0;i<paraVerCuantoPesa.size();i++){xmlAux[i]=xml[i];}
	string idOperacionString= this->parser->getOperacionId(xmlAux);
	idOperacionString=toupper(idOperacionString[0]);
	char idOperacionChar=idOperacionString[0];
	switch(idOperacionChar){
		case('E'):{this->path=PATH;return true;}
		case('I'):{this->path="/home/gaston/workspace/TpTallerDeProgramacionI/" + this->parser->getNombreJugadorYConstrasena(xml)[0] + ".bmp"; return true;}
	}
	return (false);
}

Procesador::~Procesador() {
}
