#ifndef MAZO_H_
#define MAZO_H_

using namespace std;
#include <iostream>
#include <string>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stack>
#include <vector>
#include "Carta.h"

class Mazo {
private:
	stack<Carta> pila;
	int semilla;
public:
	Mazo();
	void mezclar();
	Carta* getCarta();
	~Mazo();
};

#endif
