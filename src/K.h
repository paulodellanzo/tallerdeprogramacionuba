/*
 * K.h
 *
 *  Created on: 14/11/2010
 *      Author: javier
 */
using namespace std;
#include "Operacion.h"
#include <string>
#include <list>
#include "Conexion.h"
#include <stdio.h>

#ifndef K_H_
#define K_H_

class K {
private:

public:
	K();
	list<string>* realizarOpearacion(list<char*>* operandos);
   ~K();
};

#endif /* K_H_ */
