#include "ParserServidor.h"
using namespace std;
#include <stdlib.h>
#include <iostream>
#include <stdio.h>

ParserServidor::ParserServidor() {
	// TODO Auto-generated constructor stub

}
list<char*>* ParserServidor::getOperandos(char xml[]){
//	COmo sabe que esta bien busca los operandos directamente acordarse la estructura de la lista
	list<char*>* aEnviar=new list<char*>();
	list<char*>::iterator it=aEnviar->begin();
	char* buff=strtok(xml," <>=");
	while(strcmp(buff,"/parametros")){
		if(strcmp(buff,"nombre")==0){
			buff=strtok(NULL,"\n\t=\"");
			it=aEnviar->insert(it,buff);
			it++;
			buff=strtok(NULL,"<> \t\n");
			it=aEnviar->insert(it,buff);
			it++;
		}else{
			buff=strtok(NULL," <>=");
		}
	}
	return aEnviar;
}

string ParserServidor::getOperacionId(char xml[]){
//como sabe que esta bien busca la operacion id directamente
	bool encontrado=false;
	char* buff=strtok(xml," <>=");
	while((!encontrado)and(buff!=NULL)){
		if(strcmp(buff,"id")==0){
			buff=strtok(NULL,"\n\t=\"");
			encontrado=true;
			string aDevolver=buff;
			return(aDevolver);
		}else{
			buff=strtok(NULL," <>=");
		}
	}
	return "no encontro id";
}

const char* ParserServidor::getXml(list<string>* base, string idOperacion){
//	Arma el xml se fija si el primer nodo de la lista es CORRECTO o ERROR
	if(base->front()=="Error"){
		base->pop_front();
		return (this->armarXmlDeErrores(base,idOperacion));
	}else{
		base->pop_front();
		return (this->armarXmlDeResultado(base,idOperacion));
	}
}

const char* ParserServidor::armarXmlDeErrores(list<string>* base,string idOperacion){
	string aEnviar;
	(aEnviar)="<respuesta>\n	</operacion id=\""+idOperacion+"\"/>\n	<errores>\n";
	list<string>::const_iterator iterador;
	iterador=base->begin();
	while(iterador!=base->end()){
		(aEnviar)+="		<error tipo=\""+(*iterador)+"\">\n";
		iterador++;
		(aEnviar)+="		"+(*iterador)+"\n		</error>\n";
		iterador++;
	}
	(aEnviar)+="	</errores>\n</respuesta>";
	char* data=new char[aEnviar.size()];
	for(unsigned int i=0;i<aEnviar.size();i++){data[i]=aEnviar[i];}
	return (data);

}

const char* ParserServidor::armarXmlDeResultado(list<string>* base, string idOperacion){
	string aEnviar;
	(aEnviar)="<respuesta>\n	</operacion id=\""+idOperacion+"\"/>\n	<resultados>\n";
	list<string>::const_iterator iterador;
	iterador=base->begin();
	while(iterador!=base->end()){
		(aEnviar)+="		<resultado nombre=\""+(*iterador)+"\">\n";
		iterador++;
		(aEnviar)+="		"+(*iterador)+"\n		</resultado>\n";
		iterador++;
	}
	(aEnviar)+="	</resultados>\n</respuesta>";
	char* data=new char[aEnviar.size()];
	for(unsigned int i=0;i<aEnviar.size();i++){data[i]=aEnviar[i];}
	return (data);
}

ParserServidor::~ParserServidor() {
	// TODO Auto-generated destructor stub
}
