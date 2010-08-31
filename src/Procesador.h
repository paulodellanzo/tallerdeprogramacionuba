#ifndef PROCESADOR_H_
#define PROCESADOR_H_

using namespace std;
#include <string>
#include "Operacion.h"
#include <map>
#include <list>

class Procesador {
private:
	map<string,Operacion>* operaciones;
public:
	Procesador();
	string getResultado(string operacion, list<string>* operandos);
	virtual ~Procesador();
};

#endif /* PROCESADOR_H_ */
