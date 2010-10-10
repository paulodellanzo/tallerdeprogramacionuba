#include "Procesador.h"
using namespace std;
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <fstream>

//metodo de ejemplo para poner algo en la mesa
void Procesador::setMesa(){
	for(int i = 1; i < 4; i++){
		Jugador* player = new Jugador();
		ostringstream sstream;
		sstream << i;
		string numero = sstream.str();
		player->setNombre("jugador" + numero, "123456");
		player->aumentarPlata(i * 100);
		if (!this->agregarJugador(player))
			break;
	}

	Carta* carta1 = new Carta("corazon", "10");
	cartas->push_front(carta1);
	Carta* carta2 = new Carta("pica", "2");
	cartas->push_front(carta2);
	Carta* carta3 = new Carta("trebol", "5");
//	cartas->push_front(carta3);
//	Carta* carta4 = new Carta("corazon", "7");
//	cartas->push_front(carta4);
//	Carta* carta5 = new Carta("pica", "4");
//	cartas->push_front(carta5);
//	Carta* carta6 = new Carta("rombo", "11");
//	cartas->push_front(carta6);
//	Carta* carta7 = new Carta("corazon", "8");
//	cartas->push_front(carta7);
//	Carta* carta8 = new Carta("pica", "13");
//	cartas->push_front(carta8);
//	Carta* carta9 = new Carta("trebol", "1");
//	cartas->push_front(carta9);
//	Carta* carta10 = new Carta("rombo", "12");
//	cartas->push_front(carta10);
//	Carta* carta11 = new Carta("pica", "6");
//	cartas->push_front(carta11);
}

Procesador::Procesador(int i) {
	this->parser=new ParserServidor();
	this->cartas = new list<Carta*>;
	this->jugadores = new list<Jugador*>;
	this->bote = 0;
	this->apuestaMayorEnRonda = 0;
	this->setMesa();
}

char* Procesador::getRespuesta(char* xml){
	ostringstream sstream;
	sstream << xml;
	string paraVerCuantoPesa = sstream.str();
	char xmlAux[paraVerCuantoPesa.size()];
	char xmlAux2[paraVerCuantoPesa.size()];
	for(unsigned int i=0;i<paraVerCuantoPesa.size();i++){xmlAux[i]=xml[i];xmlAux2[i]=xml[i];}
	string idOperacionString= this->parser->getOperacionId(xmlAux);
	char* respuesta=" ";
	string res;
	list<char*>* operandos=this->parser->getOperandos(xmlAux2);
	idOperacionString=toupper(idOperacionString[0]);
	char idOperacionChar=idOperacionString[0];
	Operacion* operacion;
	J* operadorJ;
	C* operadorC;
	switch(idOperacionChar){
		case('S'):{res="S";operacion=new S();break;}
		case('D'):{res="S";operacion=new D();break;}
		case('M'):{res="S";operacion=new M();break;}
		case('R'):{res="S";operacion=new R();break;}
		case('P'):{res="P";break;}
		case('J'):{res="J";operadorJ = new J();break;}
		case('C'):{res="C";operadorC = new C();break;}
		default:{
			list<string>* conError=new list<string>();
			list<string>::iterator it=conError->begin();
			it=conError->insert(it,"Error");
			it++;
			it=conError->insert(it,"V");
			it++;
			it=conError->insert(it,"Mal id de operacion");
			respuesta=this->parser->getXml(conError,"");
			delete conError;
			delete operandos;
			return respuesta;
		}
	}
	if(res=="S"){
			list<string>* respuestaDeOperacion=operacion->realizarOpearacion(operandos);
			respuesta=this->parser->getXml(respuestaDeOperacion,idOperacionString);
			delete respuestaDeOperacion;
			delete operandos;
			return respuesta;
	}
	if(res=="P"){
		ostringstream sstream;
		sstream << this->bote;
		string boteString = sstream.str();
		list<string>* respuestaDeOperacion = new list<string>();
		list<string>::iterator it;
		it = respuestaDeOperacion->begin();
		it=respuestaDeOperacion->insert(it,"Correcto");
		it++;
		it = respuestaDeOperacion->insert(it, "bote");
		it++;
		it = respuestaDeOperacion->insert(it, boteString);
		it++;
		respuesta=this->parser->getXml(respuestaDeOperacion,idOperacionString);
		delete operandos;
		return respuesta;

	}
	if(res=="J"){
		cout<<"holaaaa"<<endl;
		list<string>* respuestaDeOperacion = operadorJ->realizarOperacion(this->jugadores);
		cout<<"hola111"<<endl;
		respuesta=this->parser->getXml(respuestaDeOperacion,idOperacionString);
		cout<<"chauuuu"<<endl;
		delete operandos;
		return respuesta;

	}
	if(res=="C"){
		cout<<"C"<<endl;
		list<string>* respuestaDeOperacion = operadorC->realizarOperacion(this->cartas);
		cout<<"asldnas"<<endl;
		respuesta=this->parser->getXml(respuestaDeOperacion,idOperacionString);
		cout<<"asldnd"<<endl;
		delete operandos;
		return respuesta;

	}
	return"";

}

Procesador * Procesador::instanciaUnica;

Procesador *Procesador::instancia(){
		    if (!instanciaUnica)
		    	instanciaUnica =new Procesador(1);
		    return instanciaUnica;
}

string Procesador::getPathArchivo(){
	return this->path;
}

bool Procesador::enviarArchivo(char * xml){
	ostringstream sstream;
	sstream << xml;
	string paraVerCuantoPesa = sstream.str();
	char xmlAux[paraVerCuantoPesa.size()];
	for(unsigned int i=0;i<paraVerCuantoPesa.size();i++){xmlAux[i]=xml[i];}
	string idOperacionString= this->parser->getOperacionId(xmlAux);
	idOperacionString=toupper(idOperacionString[0]);
	char idOperacionChar=idOperacionString[0];
	switch(idOperacionChar){
		case('E'):{this->path=PATH;return true;}
		case('I'):{this->path="/home/paulo/workspace/TpTallerDeProgramacionI/" + this->parser->getNombreJugadorYConstrasena(xml)[0] + ".bmp"; return true;}
	}
	return (false);
}

bool Procesador::agregarJugador(Jugador* jugadorNuevo){
	if(this->jugadores->size() < MAXIMODEJUGADORES){
		this->jugadores->push_back(jugadorNuevo);
		return true;
	}
	else{
		cout << "Maximo numero de jugadores en la mesa" << endl;
		return false;
	}
}

Procesador::~Procesador() {
	delete this->parser;
}
