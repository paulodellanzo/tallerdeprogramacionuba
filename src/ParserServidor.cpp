#include "ParserServidor.h"

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

ParserServidor::~ParserServidor() {
	// TODO Auto-generated destructor stub
}
