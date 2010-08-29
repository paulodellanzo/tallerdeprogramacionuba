#ifndef SERVIDORCLIENTE_H_
#define SERVIDORCLIENTE_H_

#include <SolarSockets/SolarSockets++.h>
#include <string>

class ServidorCliente : public ssPPServerClient{
public:
	ServidorCliente();
	virtual ~ServidorCliente();
};

#endif /* SERVIDORCLIENTE_H_ */
