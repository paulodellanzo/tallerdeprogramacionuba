#include "Procesador.h"
using namespace std;
#include <stdlib.h>
#include <iostream>
#include <stdio.h>

Procesador::Procesador() {
	this->parser=new ParserServidor();

}

const char* Procesador::getRespuesta(char* xml){
	char xmlAux[MAXBYTES];
	for(int i=0;i<MAXBYTES;i++){xmlAux[i]=xml[i];}
	string idOperacionString= this->parser->getOperacionId(xmlAux);
	const char* respuesta;
	string res;
	char xmlAux2[MAXBYTES];
	for(int i=0;i<MAXBYTES;i++){xmlAux2[i]=xml[i];}
	list<char*>* operandos=this->parser->getOperandos(xmlAux2);
	idOperacionString=toupper(idOperacionString[0]);
	char idOperacionChar=idOperacionString[0];
	Operacion* operacion;
	switch(idOperacionChar){
		case('S'):{res="S";operacion=new S();break;}
		case('D'):{res="S";operacion=new D();break;}
		case('M'):{res="S";operacion=new M();break;}
		case('R'):{res="S";operacion=new R();break;}
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
			list<string>* respuestaDeOperacion=operacion->realizarOpearacion(operandos);
			respuesta=this->parser->getXml(respuestaDeOperacion,idOperacionString);
			return respuesta;
	}
	return"";

}

Procesador::~Procesador() {
}
