#ifndef PARSERSERVIDOR_H_
#define PARSERSERVIDOR_H_

using namespace std;
#include <string>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define TAMANOVECTOROPERANDOS 20 //Para cuando haya que pasar la lista de char,el tamaño de los char

class ParserServidor {
public:
	ParserServidor();
	void getRespuesta(char* Xml,char* resultado);
	virtual ~ParserServidor();
};

#endif /* PARSERSERVIDOR_H_ */
