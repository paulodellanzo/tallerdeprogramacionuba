#ifndef S_H_
#define S_H_

using namespace std;
#include <string>
#include "Operacion.h"

class S : public Operacion{
public:
	S();
	virtual string realizarOpearacion(string* vector);
	virtual ~S();
};

#endif /* S_H_ */
