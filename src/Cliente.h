#ifndef CLIENTE_H_
#define CLIENTE_H_

#include <SolarSockets/SolarSockets++.h>
#include <string>
//probando

class Cliente : public ssPPClient
{
public:
	Cliente();
	virtual ~Cliente();
};

#endif /* CLIENTE_H_ */
