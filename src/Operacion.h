/*
 * Operacion.h
 *
 *  Created on: 28/08/2010
 *      Author: gaston
 */

#ifndef OPERACION_H_
#define OPERACION_H_
#include <string>

class Operacion {
public:
	Operacion();
	virtual string realizarOpearacion(string* vector)=0;
	virtual ~Operacion();
};

#endif /* OPERACION_H_ */
