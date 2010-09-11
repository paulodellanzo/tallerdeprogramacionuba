#include "ParserServidor.h"
using namespace std;
#include <stdlib.h>
#include <iostream>
#include <stdio.h>

ParserServidor::ParserServidor() {
	// TODO Auto-generated constructor stub

}
void ParserServidor::getRespuesta(char* Xml,char* resultado){

		char strOperacion[255];
		char cadenaAuxiliar[255];
		char operandos[255][255];
		int i=0;
		while(Xml[0]==' ') //Elimino los espacios en blanco iniciales de la cadena
			Xml=Xml+1;

		Xml=strtok(Xml,"<"); //El primer caracter debería ser "<", strtok elimina el caracter
		if (Xml==NULL)
		{
		   	printf("Error - Archivo incompleto"); //TODO Cambiar
		   	return;
		}
		sscanf(Xml,"%[^>]",resultado); //Leo el primer tag.
	    if (strcmp(resultado,"pedido") != 0) //Debe ser <pedido>.
	    {
	    	printf("Error - El primer tag no es <pedido>"); //TODO Cambiar
	    	return;
	    }

	    Xml=strtok(NULL,"<"); //Elimino de la cadena Xml los caracteres hasta el segundo tag.
	    if (Xml==NULL)
	    {
	    	printf("Error - Archivo incompleto 2"); //TODO Cambiar
	    	return;
	    }

	    if(sscanf(Xml,"operacion id=\"%[^\"] %[^>]",strOperacion,cadenaAuxiliar)==0 ||
	    		strcmp(cadenaAuxiliar,"\"/")!=0)
	    {
	    	printf("Error - El tag de operación no tiene el formato esperado"); //TODO Cambiar
	    	return;
	    }

	    Xml=strtok(NULL,"<");
	    if (Xml==NULL)
	    {
	       	printf("Error - Archivo incompleto 3"); //TODO Cambiar
	    	return;
	    }

	    sscanf(Xml,"%[^>]",resultado); 				//Leo el tercer tag.
	    if (strcmp(resultado,"parametros") != 0) 	//Debe ser <parametros>.
	    {
	    	printf("Error - El tercer tag no es <parametros>"); //TODO Cambiar
	    	return;
	    }


	    Xml=strtok(NULL,"<");

	    while (Xml!=NULL)
	    {

	    	if(sscanf(Xml,"parametro nombre=\"%[^\"]\">%[^<]]",operandos[2*i],operandos[2*i+1])
	   			!=2)
	    	{
	    		printf("Error - formato de parametro incorrecto");
	    		return;
	    	}

	    	i=i+1;
		    Xml=strtok(NULL,"<");
		    if (Xml==NULL)
		    {
		       	printf("Error - Archivo incompleto 4"); //TODO Cambiar
		      	return;
		    }
		    sscanf(Xml,"%[^>]",cadenaAuxiliar);
		    if (strcmp(cadenaAuxiliar,"/parametro")!=0)
		    {
		    	printf("Error - formato de parametro incorrecto");
		    	return;
		    }
		    Xml=strtok(NULL,"<");
	    }

	    if (i<2)
	    {
	    	printf("No se puede operar con menos de dos parámetros");
	    	return;
	    }

	    printf("fin");
	   	return;
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
	string* aEnviar = new string;
	(*aEnviar)="<respuesta>\n	</operacion id=\""+idOperacion+"\"/>\n	<errores>\n";
	list<string>::const_iterator iterador;
	iterador=base->begin();
	while(iterador!=base->end()){
		(*aEnviar)+="		<error tipo=\""+(*iterador)+"\">\n";
		iterador++;
		(*aEnviar)+="		"+(*iterador)+"\n		</error>\n";
		iterador++;
	}
	(*aEnviar)+="	</errores>\n</respuesta>";
	return (aEnviar->c_str());

}

const char* ParserServidor::armarXmlDeResultado(list<string>* base, string idOperacion){
	cout<<"Get xml2"<<endl;
	string* aEnviar = new string;
	(*aEnviar)="<respuesta>\n	</operacion id=\""+idOperacion+"\"/>\n	<resultados>\n";
	list<string>::const_iterator iterador;
	iterador=base->begin();
	while(iterador!=base->end()){
		(*aEnviar)+="		<resultado nombre=\""+(*iterador)+"\">\n";
		iterador++;
		(*aEnviar)+="		"+(*iterador)+"\n		</parametro>\n";
		iterador++;
	}
	(*aEnviar)+="	</resultados>\n</respuesta>";
	return (aEnviar->c_str());
}

ParserServidor::~ParserServidor() {
	// TODO Auto-generated destructor stub
}
