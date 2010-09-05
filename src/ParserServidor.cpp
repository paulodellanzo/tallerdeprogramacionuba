#include "ParserServidor.h"

ParserServidor::ParserServidor() {
	// TODO Auto-generated constructor stub

}
void ParserServidor::getRespuesta(char* Xml,char* resultado){

		char strOperacion[255];
		sscanf(Xml,"<%[^>]",resultado); //Leo el primer tag.
	    if (strcmp(resultado,"pedido") != 0) //Debe ser <pedido>.
	    {
	    	printf("Error - El primer tag no es <pedido>"); //TODO Cambiar
	    	return;
	    }
	    strtok(Xml,"<");
	    Xml=strtok(NULL,"<"); //Elimino de la cadena Xml los caracteres hasta el segundo tag.
	    if (Xml==NULL)
	    {
	    	printf("Error - Archivo incompleto"); //TODO Cambiar
	    	return;
	    }

	    if(sscanf(Xml,"operacion id=\"%[^\"]",strOperacion)==0)
	    {
	    	printf("Error - El tag de operación no tiene el formato esperado"); //TODO Cambiar
	    	return;
	    }

	    Xml=strtok(NULL,"<");
	    if (Xml==NULL)
	    {
	       	printf("Error - Archivo incompleto 2"); //TODO Cambiar
	    	return;
	    }

	    sscanf(Xml,"<%[^>]",resultado); 			//Leo el tercer tag.
	    if (strcmp(resultado,"parametros") != 0) 	//Debe ser <parametros>.
	    {
	    	printf("Error - El tercer tag no es <parametros>"); //TODO Cambiar
	    	return;
	    }

	    //printf("%s \n",Xml);


	return;
}

ParserServidor::~ParserServidor() {
	// TODO Auto-generated destructor stub
}
