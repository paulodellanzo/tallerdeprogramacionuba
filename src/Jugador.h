#ifndef JUGADOR_H_
#define JUGADOR_H_

using namespace std;
#include <string>
#include <string.h>
#include "Carta.h"
#include <list>
#include "Conexion.h"

class Jugador {
private:
	string nombre,pathImagen,password;
	long int plata;
	Carta* carta1, *carta2;
	bool jugando_en_partida;
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
	bool igualoApuestaMano(long int apuesta){return this->ultimaApuesta==apuesta;}
	void empezarAJugar(){this->jugando_en_partida=true;}
	void dejarDeJugar(){this->jugando_en_partida=false;}
	string getNombre();
	bool modificarPlataEn(long int plata); //Este metodo despues va a ser mas importante
	virtual ~Jugador();
};

#endif /* JUGADOR_H_ */
