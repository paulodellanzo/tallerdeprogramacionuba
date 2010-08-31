#ifndef S_H_
#define S_H_

using namespace std;
#include <string>
#include "Operacion.h"
#include <list>

class S : public Operacion{
public:
	S();
	virtual string realizarOpearacion(list<string>* operandos);
	virtual ~S();
};

#endif /* S_H_ */
