#ifndef R_H_
#define R_H_

using namespace std;
#include "Operacion.h"
#include <string>
#include <list>
#include "Conexion.h"
#include <stdio.h>

class R : public Operacion {
public:
	R();
	list<string>* realizarOpearacion(list<char*>* operandos);
	~R();
};

#endif /* R_H_ */
