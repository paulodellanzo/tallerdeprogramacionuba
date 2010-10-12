#ifndef NODO_H_
#define NODO_H_

#include <string>
#include <list>
#include <string.h>

using namespace std;

class Nodo {
private:
	int clave;
	string valor;
	list<Nodo*>* nodos;
public:
	Nodo(int clave,string valor);
	void agregarHijo(Nodo* nodoHijo);
	int getClave();
	string getValor();
	list<Nodo*>* getNodosHijos();
	virtual ~Nodo();
};

#endif /* NODO_H_ */
