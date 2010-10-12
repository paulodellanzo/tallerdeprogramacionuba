#include "Nodo.h"

Nodo::Nodo(int clave,string valor) {
	this->clave = clave;
	this->valor = valor;
	this->nodos = new list<Nodo*>;
}

void Nodo::agregarHijo(Nodo* nodoHijo){
	this->nodos->push_back(nodoHijo);
}

int Nodo::getClave(){
	return this->clave;
}

string Nodo::getValor(){
	return this->valor;
}

list<Nodo*>* Nodo::getNodosHijos(){
	return this->nodos;
}

Nodo::~Nodo() {
	delete this->nodos;
}
