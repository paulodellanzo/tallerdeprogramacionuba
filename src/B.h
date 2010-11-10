#ifndef B_H_
#define B_H_

using namespace std;
#include <string>
#include <list>
#include <stdio.h>
#include "Jugador.h"
#include "Carta.h"
#include "Operacion.h"

class B : public Operacion {
public:
	B();
	list<string>* realizarOpearacion(list<char*>* operandos,list<Jugador*>* jugadores);
	virtual ~B();
};

#endif /* B_H_ */
