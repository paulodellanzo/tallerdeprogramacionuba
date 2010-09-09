#ifndef R_H_
#define R_H_

using namespace std;
#include <string>
#include "Operacion.h"
#include <list>

class R : public Operacion {
public:
	R();
	virtual list<char*>* realizarOpearacion(list<char*>* operandos);
	virtual ~R();
};

#endif /* R_H_ */
