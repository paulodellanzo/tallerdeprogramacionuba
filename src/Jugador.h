#ifndef JUGADOR_H_
#define JUGADOR_H_

using namespace std;
#include <string>
#include <string.h>
#include "Carta.h"
#include <list>

class Jugador {
private:
	string nombre,pathImagen,password;
	long int plata;
	Carta* carta1, *carta2;
	bool jugando; //Por si queremos hacer que solo esta mirando
	long int ultimaApuesta;
public:
	Jugador();
	Jugador(string nombre, string password);
	void setUltimaApuesta(long int apuesta){this->ultimaApuesta=apuesta;}
	long int getUltimaApuesta(){return ultimaApuesta;}
	void setCartas(Carta * carta1, Carta * carta2);
	list<Carta*>* getCartas();
	long int plataRestante();
	bool setNombre(string nombre, string password); //QUE DE EL NOMBRE DEL USUARIO Y LA PASSWORD Y LA CORROBORE Y LEVANTE LA PLATA
	bool participando();
	void empezarAJugar(){this->jugando=true;}
	void dejarDeJugar(){this->jugando=false;}
	string getNombre();
	bool modificarPlataEn(long int plata); //Este metodo despues va a ser mas importante
	virtual ~Jugador();
};

#endif /* JUGADOR_H_ */
