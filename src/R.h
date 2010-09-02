#ifndef R_H_
#define R_H_

using namespace std;
#include <string>
#include "Operacion.h"
#include <list>

class R : Operacion {
public:
	R();
	virtual list<string>* realizarOpearacion(list<string>* operandos);
	virtual ~R();
};

#endif /* R_H_ */
