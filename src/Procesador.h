#ifndef PROCESADOR_H_
#define PROCESADOR_H_

#include <string>

class Procesador {
public:
	Procesador();
	string trabajarXml(string Xml);
	virtual ~Procesador();
};

#endif /* PROCESADOR_H_ */
