#ifndef PARSERSERVIDOR_H_
#define PARSERSERVIDOR_H_

using namespace std;
#include <string>
#include <string.h>
#include <stdio.h>

class ParserServidor {
public:
	ParserServidor();
	void getRespuesta(char* Xml,char* resultado);
	virtual ~ParserServidor();
};

#endif /* PARSERSERVIDOR_H_ */
