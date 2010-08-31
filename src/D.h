#ifndef D_H_
#define D_H_

using namespace std;
#include <string>
#include "Operacion.h"

class D : public Operacion{
public:
	D();
	virtual string realizarOpearacion(string* vector);
	virtual ~D();
};

#endif /* D_H_ */

