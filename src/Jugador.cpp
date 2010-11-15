#include "Jugador.h"

Jugador::Jugador() {
	this->carta1=NULL;
	this->carta2=NULL;
}

Jugador::Jugador(string nombre,string password){
	this->nombre=nombre;
	this->password=password;
	//hay que hacer que lo levante de la base da datos
	Conexion* conexion = Conexion::instancia();
	MYSQL_RES *res;
	MYSQL_ROW row;
	string query = "select plata from usuarios where usuario='"+this->nombre+"'";
	res = conexion->ejecutarQuery(query.c_str());
	row = mysql_fetch_row(res);
	this->plata=atoi(*row);
	conexion->liberarConexion(res);
	this->carta1=NULL;
	this->carta2=NULL;
}

bool Jugador::setNombre(string nombre, string password){
	this->nombre = nombre;
	this->password = password;
	//hay que hacer que lo levante de la base da datos
	Conexion* conexion = Conexion::instancia();
	string query = "select plata from usuarios where usuario='"+this->nombre+"' and password='"+this->password+"'";
	MYSQL_RES *res;
	MYSQL_ROW row;
	res = conexion->ejecutarQuery(query.c_str());
	row = mysql_fetch_row(res);
	this->plata=atoi(*row);
	conexion->liberarConexion(res);
	return true;
}

long int Jugador::plataRestante(){
	return this->plata;
}

string Jugador::getNombre(){
	return this->nombre;
}

bool Jugador::participando(){
	return this->jugando_en_partida;
}

bool Jugador::modificarPlataEn(long int plata){
	this->plata += plata;
	return true;
}

void Jugador::setCartas(Carta * carta1, Carta * carta2){
//	if(this->carta1!=NULL) delete carta1;
//	if (this->carta2!=NULL) delete carta2;

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
