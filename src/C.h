#ifndef C_H_
#define C_H_

using namespace std;
#include <string>
#include <list>
#include "Carta.h"

class C {
public:
	C();
	list<string>* realizarOperacion(list<Carta*>* jugadores);
	~C();
};

#endif /* C_H_ */
