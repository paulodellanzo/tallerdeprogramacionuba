#ifndef SERVIDORCLIENTE_H_
#define SERVIDORCLIENTE_H_

using namespace std;
#include <string>
#include "ParserServidor.h"

class ServidorCliente{
private:
	ParserServidor* parser;
public:
	ServidorCliente();
	virtual ~ServidorCliente();
};

#endif /* SERVIDORCLIENTE_H_ */
