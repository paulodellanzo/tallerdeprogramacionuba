#ifndef PROCESADOR_H_
#define PROCESADOR_H_

using namespace std;
#include <string>

class Procesador {
public:
	Procesador();
	string getResultado(string operacion, string* operandos);
	virtual ~Procesador();
};

#endif /* PROCESADOR_H_ */
