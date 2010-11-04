#ifndef C_H_
#define C_H_

using namespace std;
#include <string>
#include <list>
#include "Carta.h"
#include "Operacion.h"
class C : public Operacion {
public:
	C();
	list<string>* realizarOperacion(list<Carta*>* jugadores);
	~C();
};

#endif /* C_H_ */
