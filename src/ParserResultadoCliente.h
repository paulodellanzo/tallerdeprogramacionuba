#ifndef PARSERRESULTADOCLIENTE_H_
#define PARSERRESULTADOCLIENTE_H_

using namespace std;
#include <string>

class ParserResultadoCliente {
public:
	ParserResultadoCliente();
	void DecodificaResultado(string xml);
	virtual ~ParserResultadoCliente();
};

#endif /* PARSERRESULTADOCLIENTE_H_ */
