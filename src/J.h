#ifndef J_H_
#define J_H_

using namespace std;
#include <string>
#include <list>
#include "Jugador.h"
#include <sstream>

class J {
public:
	J();
	list<string>* realizarOperacion(list<Jugador*>* jugadores);
	~J();
};

#endif /* J_H_ */
