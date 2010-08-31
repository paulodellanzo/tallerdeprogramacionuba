#ifndef PARSERCLIENTE_H_
#define PARSERCLIENTE_H_

using namespace std;
#include <string>
#include <list>

class ParserCliente {
public:
	ParserCliente();
	ParserCliente(string Xml);
	string getXmlDeOperacion(string idOperacion, list<string>* operandos);
	virtual ~ParserCliente();
};

#endif /* PARSERCLIENTE_H_ */
