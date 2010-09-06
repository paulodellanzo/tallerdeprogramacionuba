#ifndef S_H_
#define S_H_

using namespace std;
#include <string>
#include "Operacion.h"
#include <list>

class S : public Operacion{
public:
	S();
	virtual list<char*>* realizarOpearacion(list<char*>* operandos);
	virtual ~S();
};

#endif /* S_H_ */
