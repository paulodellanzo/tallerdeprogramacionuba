#ifndef OPERACION_H_
#define OPERACION_H_

using namespace std;
#include <string>
#include <list>

class Operacion {
public:
	Operacion();
	virtual list<char*>* realizarOpearacion(list<char*>* operandos)=0;
	virtual ~Operacion();
};

#endif /* OPERACION_H_ */
