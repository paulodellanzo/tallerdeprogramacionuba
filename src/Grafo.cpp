#include "Grafo.h"

Grafo::Grafo() {
	this->nodos = new list<Nodo*>;
}

void Grafo::agregarNodo(Nodo* unNodo){
	this->nodos->push_back(unNodo);
}

Nodo* Grafo::getNodoPorClave(int clave){
	list<Nodo*>::iterator iterador=this->nodos->begin();
	while(iterador!=this->nodos->end()){
		if((*iterador)->getClave()==clave){
			return *iterador;
		}
		iterador++;
	}
	return NULL;
}

bool Grafo::agregarArista(int claveDesde, int claveHasta){
	Nodo* nodoDesde = this->getNodoPorClave(claveDesde);
	Nodo* nodoHasta = this->getNodoPorClave(claveHasta);
	if((nodoDesde==NULL) or (nodoHasta==NULL)){
		return false;
	}
	nodoDesde->agregarHijo(nodoHasta);
	return true;
}

Grafo::~Grafo() {
	delete this->nodos;
}
