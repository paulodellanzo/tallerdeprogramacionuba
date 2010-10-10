#include "Jugador.h"

Jugador::Jugador() {
	// TODO Auto-generated constructor stub

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

bool Jugador::aumentarPlata(long int plata){
	this->plata += plata;
	return true;
}

Jugador::~Jugador() {
	// TODO Auto-generated destructor stub
}
