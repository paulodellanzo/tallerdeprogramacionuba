#ifndef D_H_
#define D_H_

using namespace std;
#include <string>
#include "Operacion.h"
#include <list>

class D : public Operacion{
public:
	D();
	virtual list<char*>* realizarOpearacion(list<char*>* operandos);
	virtual ~D();
};

#endif /* D_H_ */

