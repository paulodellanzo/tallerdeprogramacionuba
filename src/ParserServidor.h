#ifndef PARSERSERVIDOR_H_
#define PARSERSERVIDOR_H_

using namespace std;
#include <string>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <list>
#include <cstdlib>
#define TAMANOVECTOROPERANDOS 20 //Para cuando haya que pasar la lista de char,el tamaño de los char

class ParserServidor {
	private:
		char* armarXmlDeErrores(list<char*>* base,char idOperacion);
		char* armarXmlDeResultado(list<char*>* base,char idOperacion);
	public:
		ParserServidor();
		void getRespuesta(char* Xml,char* resultado);
		char getOperacionId(char *xml);
		list<char*>* getOperandos(char* xml);
		char* getXml(list<char*>* base,char idOperacion);
		virtual ~ParserServidor();
};

#endif /* PARSERSERVIDOR_H_ */
