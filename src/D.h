#ifndef D_H_
#define D_H_

using namespace std;
#include <string>
#include "Operacion.h"
#include <list>

class D : public Operacion{
public:
	D();
	virtual list<string> realizarOpearacion(list<string>* operandos);
	virtual ~D();
};

#endif /* D_H_ */

