#ifndef PROCESADOR_H_
#define PROCESADOR_H_

#define PORT 54340
#define MAXBYTES 60000
#define MAXBYTESRECIBIDOS 60000
#define MAXIMODEJUGADORES 6
#define MAXIMODECARTAS 5
#define PATHARCHIVOCONF "config.ini"

using namespace std;
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <cstdlib>
#include "Poker.h"
#include <string>
#include "Operacion.h"
#include "Mazo.h"
#include "ParserServidor.h"
#include "S.h"
#include "D.h"
#include "R.h"
#include "L.h"
#include "M.h"
#include "J.h"
#include "C.h"
#include "N.h"
#include "U.h"
#include "B.h"
#include "K.h"
#include <map>
#include <list>
#include <ctype.h>
#include "Carta.h"
#include "Jugador.h"
#include "Conexion.h"

class Procesador {
protected:
	Procesador(int i);
private:
	int sizeJugadores;
	static pthread_mutex_t mutex;
	static Procesador* instanciaUnica;
	informacionConfiguracion* infoconfig;
	ParserServidor* parser;
	string path; //La que se tiene que mandar cuando se lo pida
	list<Carta*>* cartas;
	list<Jugador*>* jugadores; //Los jugadores que estan jugando
	list<Jugador*>* jugadores_a_dibujar;
	list<Jugador*>* jugadores_agregar;//Los que se agregan, serias los que se ponen a jugar cuando se termina una mano
	string nombreJugadorJugando;
	long int bote; //Poso que se va acumulando
	long int apuestaMayorEnRonda; //sirve para cuando pasan los turnos de todos cuanto se va apostando
	long int apuestaAnterior;
	bool estaJugando;
	Mazo * mazo;
	string ganador;
public:
	void jugar();
	static Procesador* instancia();
	bool empezarPartida(char* xml);//Devuelve true si la operacion en una F cosa que empieza a jugar
	list<string>* seConectoJugador(char* xml);
	string getPathArchivo();
	bool agregarJugador(Jugador* jugadorNuevo);
	bool quitarJugador(Jugador* jugador);
	bool agregarCarta(Carta* cartaNueva);
	bool enviarArchivo(char*xml); //FALTA VER LO DE SI ES UNA IMAGEN DE UN JUGADOR
	bool recibirArchivo(char*xml);
	char* getRespuesta(char* xml, Jugador * jugador);
	void terminoMiTurno();
	bool seEstaJugando(){return this->estaJugando;}
	bool estaJugandoJugador(string nombre_jugador);
	char * getXml(list<string> * lista,string operacion);
	void vaciarCartas();
	void empezarPartida();
	bool abandonarMano();
	virtual ~Procesador();
};

#endif /* PROCESADOR_H_ */
