#ifndef M_H_
#define M_H_

using namespace std;
#include <string>
#include "Operacion.h"

class M : public Operacion{
public:
	M();
	virtual string realizarOpearacion(string* vector);
	virtual ~M();
};

#endif /* M_H_ */
