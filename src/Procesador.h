#ifndef PROCESADOR_H_
#define PROCESADOR_H_

#define PORT 54340
#define MAXBYTES 60000
#define MAXBYTESRECIBIDOS 60000
#define MAXIMODEJUGADORES 6
#define PATH "/home/gaston/workspace/TpTallerDeProgramacionI/quilmes.bmp"

using namespace std;
#include <string>
#include "Operacion.h"
#include "ParserServidor.h"
#include "S.h"
#include "D.h"
#include "R.h"
#include "M.h"
#include <map>
#include <list>
#include <ctype.h>
#include "Carta.h"
#include "Jugador.h"

class Procesador {
protected:
	Procesador(int i);
private:
	ParserServidor* parser;
	static Procesador* instanciaUnica;
	list<Carta>* cartas;
	list<Jugador>* jugadores; //Los jugadores que se van agregando
	long int bote; //Poso que se va acumulando
	long int apuestaMayorEnRonda; //sirve para cuando pasan los turnos de todos cuanto se va apostando
	string path; //La que se tiene que mandar cuando se lo pida
public:
	static Procesador* instancia();
	string getPathArchivo();
	bool agregarJugador(Jugador* jugadorNuevo); //FALTA IMPLEMENTAR LA IDEA ES QUE SE FIJE SI TIENE LA CANT DE JUGADORES SINO QUE NO LO AGREGUE Y DEVUELVA FALSE
	bool enviarArchivo(char*xml); //FALTA VER LO DE SI ES UNA IMAGEN DE UN JUGADOR
	char* getRespuesta(char* xml);
	bool esMiTurno(Jugador * jugador); //Dandole un jugador dice si es su turno
	virtual ~Procesador();
};

#endif /* PROCESADOR_H_ */
