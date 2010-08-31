#ifndef SERVIDORCLIENTE_H_
#define SERVIDORCLIENTE_H_

#include <SolarSockets/SolarSockets++.h>
using namespace std;
#include <string>
#include "ParserServidor.h"

class ServidorCliente : public ssPPServerClient{
private:
	ParserServidor* parser;
public:
	ServidorCliente();
	virtual void onConnect();
	virtual void onDataArrival(string Data);
	virtual ~ServidorCliente();
};

#endif /* SERVIDORCLIENTE_H_ */
