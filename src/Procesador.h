#ifndef PROCESADOR_H_
#define PROCESADOR_H_

#define PORT 54340
#define MAXBYTES 60000
#define MAXBYTESRECIBIDOS 60000

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
#include <ctype.h>

class Procesador {
private:
	ParserServidor* parser;
public:
	Procesador();
	char* getRespuesta(char* xml);
	virtual ~Procesador();
};

#endif /* PROCESADOR_H_ */
