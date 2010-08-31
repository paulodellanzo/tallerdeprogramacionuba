#ifndef SERVIDORCLIENTE_H_
#define SERVIDORCLIENTE_H_

#include <SolarSockets/SolarSockets++.h>
using namespace std;
#include <string>

class ServidorCliente : public ssPPServerClient{
public:
	ServidorCliente();
	virtual void onConnect();
	virtual void onDataArrival(string Data);
	virtual ~ServidorCliente();
};

#endif /* SERVIDORCLIENTE_H_ */
