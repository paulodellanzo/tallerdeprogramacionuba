#include "Jugador.h"

Jugador::Jugador() {
	this->carta1=NULL;
	this->carta2=NULL;
}

Jugador::Jugador(string nombre,string password){
	this->nombre=nombre;
	this->password=password;
	this->plata=0;
	this->carta1=NULL;
	this->carta2=NULL;
}

bool Jugador::setNombre(string nombre, string password){
	this->nombre = nombre;
	this->password = password;
	this->jugando = true;
	this->plata = 0;
}

long int Jugador::plataRestante(){
	return this->plata;
}

string Jugador::getNombre(){
	return this->nombre;
}

bool Jugador::participando(){
	return this->jugando;
}

bool Jugador::modificarPlataEn(long int plata){
	this->plata += plata;
	return true;
}

void Jugador::setCartas(Carta * carta1, Carta * carta2){
	if(this->carta1!=NULL) delete carta1;
	if (this->carta2!=NULL) delete carta2;

	this->carta1=carta1;
	this->carta2=carta2;
}

list<Carta*> * Jugador::getCartas(){
	if(carta1==NULL or carta2==NULL){
		return NULL;
	}
	list<Carta*> * cartas=new list<Carta*>();
	cartas->push_front(this->carta1);
	cartas->push_front(this->carta2);
	return cartas;
}

Jugador::~Jugador() {
	// TODO Auto-generated destructor stub
}
