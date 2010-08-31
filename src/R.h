#ifndef R_H_
#define R_H_

using namespace std;
#include <string>
#include "Operacion.h"

class R : Operacion {
public:
	R();
	virtual string realizarOpearacion(string* vector);
	virtual ~R();
};

#endif /* R_H_ */
