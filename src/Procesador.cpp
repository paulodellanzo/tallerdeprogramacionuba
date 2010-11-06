#include "Procesador.h"
using namespace std;
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <cstdlib>


//metodo de ejemplo para poner algo en la mesa
void Procesador::setMesa(){
	list<string>::iterator it;
	it = this->infoconfig->jugadores->begin();
	for (unsigned int i = 0; i < this->infoconfig->jugadores->size()/2; i++) {
		Jugador* player = new Jugador();
		string nombre = *it;
		it++;
		string dinero = *it;
		const char* plata = dinero.c_str();
		it++;
		player->setNombre(nombre, "123456");
		player->modificarPlataEn(atoi(plata));

		if (!this->agregarJugador(player))
			break;
	}

	list<string>::iterator it2;
	it2 = this->infoconfig->cartas->begin();
	for (unsigned int i = 0; i < this->infoconfig->cartas->size() / 2; i++) {
		string palo = *it2;
		it2++;
		string numero = *it2;
		const char* numerocarta = numero.c_str();
		it2++;
		Carta* carta = new Carta(palo, numerocarta);

		if (!this->agregarCarta(carta))
			break;
	}
}


Procesador::Procesador(int i) {
	ParserServidor *parserAux = new ParserServidor(PATHARCHIVOCONF);
	if (parserAux->comprobarSintaxis()) {
		this->infoconfig = parserAux->getInformacionConfig();
	} else {
		cout << "Sintaxis de archivo de configuración incorrecta" << endl;
		cout<<"Se cerrara la aplicacion..."<<endl;
		sleep(1);
		exit(0);
	}

	this->parser=new ParserServidor();
	this->cartas = new list<Carta*>();
	this->jugadores = new list<Jugador*>();
	this->bote = 500;
	this->apuestaMayorEnRonda = 0;
	this->setMesa();
	delete parserAux;
	this->estaJugando=false;

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
	U* operadorU;
	switch(idOperacionChar){
		case('P'):{res="P";break;}//EL poso
		case('J'):{res="J";operadorJ = new J();break;}//los jugadores jugando
		case('C'):{res="C";operadorC = new C();break;}//las cartas de la mesa
		case('U'):{res="U";operadorU = new U();break;}//NO SE QUE HACE JAJAJA
		case('A'):{res="A";break;}//De quien es el turno
		case('B'):{res="B";break;}//Pide las cartas de un jugador, le pasa el nombre
		case('D'):{res="D";break;}//Pide la apuesta en esa partida
		case('F'):{res="F";break;}//Empezar a jugar cuando termino con el login y eso
		case('G'):{res="G";break;}//Para saber si se esta jugando sino empieza a jugar
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
	if(res=="P"){
		ostringstream sstream;
		sstream << this->bote;
		string boteString = sstream.str();
		list<string>* respuestaDeOperacion = new list<string>();
		list<string>::iterator it;
		it = respuestaDeOperacion->begin();
		it = respuestaDeOperacion->insert(it, "Correcto");
		it++;
		it = respuestaDeOperacion->insert(it, "bote");
		it++;
		it = respuestaDeOperacion->insert(it, boteString);
		it++;
		respuesta=this->parser->getXml(respuestaDeOperacion,idOperacionString);
		delete operandos;
		return respuesta;

	}else if(res=="J"){
		list<string>* respuestaDeOperacion = operadorJ->realizarOperacion(this->jugadores);
		respuesta=this->parser->getXml(respuestaDeOperacion,idOperacionString);
		delete operandos;
		return respuesta;

	}else if(res=="C"){
		list<string>* respuestaDeOperacion = operadorC->realizarOperacion(this->cartas);
		respuesta=this->parser->getXml(respuestaDeOperacion,idOperacionString);
		delete operandos;
		return respuesta;

	}else if(res=="U"){
		list<string>* respuestaDeOperacion=operadorU->realizarOpearacion(operandos);
		respuesta=this->parser->getXml(respuestaDeOperacion,idOperacionString);
		delete operandos;
		return respuesta;

	}else if(res=="A"){
		list<string>* respuestaDeOperacion = new list<string>();
		list<string>::iterator it;
		it = respuestaDeOperacion->begin();
		it = respuestaDeOperacion->insert(it, "Correcto");
		it++;
		it = respuestaDeOperacion->insert(it, "jugador");
		it++;
		it = respuestaDeOperacion->insert(it, this->nombreJugadorJugando);
		it++;
		respuesta=this->parser->getXml(respuestaDeOperacion,idOperacionString);
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

		case('E'):{this->path=this->infoconfig->pathEscenario;return true;}
		case('I'):{this->path=this->parser->getNombreJugador(xml) + ".bmp"; return true;}
	}
	return (false);
}

bool Procesador::empezarPartida(char* xml){
	ostringstream sstream;
	sstream << xml;
	string paraVerCuantoPesa = sstream.str();
	char xmlAux[paraVerCuantoPesa.size()];
	for(unsigned int i=0;i<paraVerCuantoPesa.size();i++){xmlAux[i]=xml[i];}
	string idOperacionString= this->parser->getOperacionId(xmlAux);
	idOperacionString=toupper(idOperacionString[0]);
	char idOperacionChar=idOperacionString[0];
	return idOperacionChar=='F';
}

list<string>* Procesador::seConectoJugador(char* xml){
	ostringstream sstream;
	sstream << xml;
	string paraVerCuantoPesa = sstream.str();
	char xmlAux[paraVerCuantoPesa.size()];
	char xmlAux2[paraVerCuantoPesa.size()];
	for(unsigned int i=0;i<paraVerCuantoPesa.size();i++){xmlAux[i]=xml[i];xmlAux2[i]=xml[i];}
	string idOperacionString= this->parser->getOperacionId(xmlAux);
	idOperacionString=toupper(idOperacionString[0]);
	char idOperacionChar=idOperacionString[0];
	U* operadorU=new U();
	list<char*>* operandos=this->parser->getOperandos(xmlAux2);
	if(idOperacionChar=='U'){
		return operadorU->realizarOpearacion(operandos);
	}else{
		return NULL;
	}
}

bool Procesador::agregarJugador(Jugador* jugadorNuevo){
	//IMPORTANTE CUANDO SE AGREGUE EL JUGADOR HAY QUE BUSCA EN MYSQL LA TABLA Y SACAR EL DINERO QUE TIENE
	if(this->jugadores->size() < MAXIMODEJUGADORES){
		this->jugadores->push_back(jugadorNuevo);
		return true;
	}
	else{
		cout << "Maximo numero de jugadores en la mesa" << endl;
		return false;
	}
}

bool Procesador::quitarJugador(Jugador* jugador){
	list<Jugador*>* lista_aux=new list<Jugador*>();
	while(this->jugadores->size()>0){
		Jugador* juga=this->jugadores->front();
		this->jugadores->pop_front();
		if(juga->getNombre()!=jugador->getNombre()){
			lista_aux->push_front(juga);
		}
	}
	this->jugadores=lista_aux;
}

bool Procesador::agregarCarta(Carta* cartaNueva){
	if(this->cartas->size() < MAXIMODECARTAS){
		this->cartas->push_back(cartaNueva);
		return true;
	}
	else{
		cout << "Maximo numero de cartas en la mesa" << endl;
		return false;
	}
}

void Procesador::terminoMiTurno(){
	Jugador * jugadorEnTurno=this->jugadores->front();
	this->jugadores->pop_front();
	this->jugadores->push_back(jugadorEnTurno);
	jugadorEnTurno=this->jugadores->front();
	this->nombreJugadorJugando=jugadorEnTurno->getNombre();
}

bool Procesador::esMiTurno(Jugador *  jugador){
	return this->jugadores->front()->getNombre()==jugador->getNombre();
}

Procesador::~Procesador() {
	delete this->parser;
}
