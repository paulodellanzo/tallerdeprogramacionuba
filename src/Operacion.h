#ifndef OPERACION_H_
#define OPERACION_H_

using namespace std;
#include <string>

class Operacion {
public:
	Operacion();
	virtual string realizarOpearacion(string* vector)=0;
	virtual ~Operacion();
};

#endif /* OPERACION_H_ */
