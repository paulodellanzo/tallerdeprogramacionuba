#ifndef POKER_H_
#define POKER_H_

using namespace std;
#include <iostream>
#include <string>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <list>
#include "Carta.h"
#include <math.h>

class Poker{
private:
	float puntaje;
	list<Carta>* mejoresCartas;
	list<Carta>* crearLista(list<Carta>*,int,int,int,int,int);
	float esEscaleraReal(list<Carta> cartas);
	float esEscaleraDeColor(list<Carta> cartas);
	float esPoker(list<Carta> cartas);
	float esFull(list<Carta> cartas);
	float esColor(list<Carta> cartas);
	float esEscalera(list<Carta> cartas);
	float esTrio(list<Carta> cartas);
	float esDoblePar(list<Carta> cartas);
	float esPar(list<Carta> cartas);
	float mayorCarta(list<Carta> cartas);
	float getPuntajeMano(list<Carta>* cartas);
public:
	Poker(list<Carta>*);
	list<Carta>* getMejoresCartas();
	float getPuntaje();
	~Poker();
};

#endif
