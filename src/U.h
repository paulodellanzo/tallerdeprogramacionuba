/*
 * U.h
 *
 */

#ifndef U_H_
#define U_H_
using namespace std;
using namespace std;
#include "Operacion.h"
#include <string>
#include <list>
#include "Conexion.h"
#include <stdio.h>


class U : public Operacion{
public:
	U();
	list<string>* realizarOpearacion(list<char*>* operandos);
	~U();
};

#endif /* U_H_ */
