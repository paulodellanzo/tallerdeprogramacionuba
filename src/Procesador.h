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
protected:
	Procesador(int i);
private:
	ParserServidor* parser;
	static Procesador* instanciaUnica;
public:
	static Procesador* instancia();
	string getPathArchivo();
	bool enviarArchivo(char*xml);
	char* getRespuesta(char* xml);
	virtual ~Procesador();
};

#endif /* PROCESADOR_H_ */
