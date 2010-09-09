#ifndef PROCESADOR_H_
#define PROCESADOR_H_

#define PORT 5434
#define MAXBYTES 300

using namespace std;
#include <string>
#include "Operacion.h"
#include "ParserServidor.h"
#include "S.h"
#include "D.h"
#include "R.h"
#include "M.h"
#include <map>
#include <list>

class Procesador {
private:
	map<char,Operacion>* operaciones;
	ParserServidor* parser;
public:
	Procesador();
	char* getRespuesta(char* xml);
	virtual ~Procesador();
};

#endif /* PROCESADOR_H_ */
