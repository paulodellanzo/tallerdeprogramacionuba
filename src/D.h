#ifndef D_H_
#define D_H_

using namespace std;
#include <string>
#include "Operacion.h"
#include "Jugador.h"
#include <list>

class D {
public:
	D();
	virtual list<string>* realizarOperacion(list<char*>* operandos, Jugador * jugador);
	virtual ~D();
};

#endif /* D_H_ */

