#ifndef CARTA_H_
#define CARTA_H_

using namespace std;
#include <string>
#include <string.h>

class Carta {
private:
	string palo,numero;
public:
	Carta(string palo, string numero);
	string getPalo();
	string getNumero();
	virtual ~Carta();
};

#endif /* CARTA_H_ */
