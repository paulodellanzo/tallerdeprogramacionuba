#ifndef PROCESADOR_H_
#define PROCESADOR_H_

using namespace std;
#include <string>

class Procesador {
public:
	Procesador();
	string trabajarXml(string Xml);
	virtual ~Procesador();
};

#endif /* PROCESADOR_H_ */
