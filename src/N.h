#ifndef N_H_
#define N_H_

using namespace std;
#include "Operacion.h"
#include <string>
#include <list>
#include "Conexion.h"
#include <stdio.h>

class N : public Operacion {
public:
	N();
	list<string>* realizarOpearacion(list<char*>* operandos);
	~N();
};

#endif /* N_H_ */
