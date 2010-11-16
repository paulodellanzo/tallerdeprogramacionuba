#ifndef L_H_
#define L_H_
using namespace std;
#include <string>
#include <list>
#include <stdio.h>
#include "Jugador.h"

class L {
public:
	L();
	list<string>* realizarOpearacion(list<char*>* operandos,list<Jugador*>* jugadores);
	virtual ~L();
};

#endif /* L_H_ */
