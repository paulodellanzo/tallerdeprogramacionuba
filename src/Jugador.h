#ifndef JUGADOR_H_
#define JUGADOR_H_

using namespace std;
#include <string>
#include <string.h>

class Jugador {
private:
	string nombre,pathImagen,password;
	long int plata;
	bool jugando; //Por si queremos hacer que solo esta mirando
public:
	Jugador();
	long int plataRestante();
	bool setNombre(string nombre, string password); //QUE DE EL NOMBRE DEL USUARIO Y LA PASSWORD Y LA CORROBORE Y LEVANTE LA PLATA
	bool participando();
	string getNombre();
	bool aumentarPlata(long int plata); //Este metodo despues va a ser mas importante
	virtual ~Jugador();
};

#endif /* JUGADOR_H_ */
