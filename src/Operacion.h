#ifndef OPERACION_H_
#define OPERACION_H_

using namespace std;
#include <string>
#include <string.h>
#include <list>
#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>
#include <sstream>
#define TAMANOVECTOROPERANDOS 20 //Para cuando haya que pasar la lista de char,el tamaño de los char
class Operacion {
public:
	Operacion();
	virtual list<string>* realizarOpearacion(list<char*>* operandos);
	bool esUnNumero(char* numero);
	virtual ~Operacion();
};

#endif /* OPERACION_H_ */
