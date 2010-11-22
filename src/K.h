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
using namespace std;
#include <iostream>
#include <fstream>

#ifndef K_H_
#define K_H_

class K {
private:
	ofstream* archivoEstadistica;
public:
	K();
	list<string>* realizarOpearacion(list<char*>* operandos, ofstream* archivo);
	list<string>* getRespuestaEstadistica(string query);
	void escribirArchivoEstadisticas(string titulo,string op, list<string>* respuesta);
	list<string>* getTituloEstadistica(string op);
   ~K();
};

#endif /* K_H_ */
