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

class Poker{
private:
	int puntaje;
	list<Carta>* mejoresCartas;
public:
	Poker(list<Carta>,list<Carta>);
	list<Carta>* getMejoresCartas();
	int getPuntaje();
	~Poker();
};

#endif
