#include "Procesador.h"
using namespace std;
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <cstdlib>


//metodo de ejemplo para poner algo en la mesa
void Procesador::setMesa(){
	Carta* carta= this->mazo->getCarta();
	this->agregarCarta(carta);
	carta=this->mazo->getCarta();
	this->agregarCarta(carta);
	carta=this->mazo->getCarta();
	this->agregarCarta(carta);
	carta=this->mazo->getCarta();
	this->agregarCarta(carta);
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
		string palo="treboles";
		string numerocarta="1";
		player->setCartas(this->mazo->getCarta(),this->mazo->getCarta());
		if (!this->agregarJugador(player))
			break;
	}

}


Procesador::Procesador(int i) {
	ParserServidor *parserAux = new ParserServidor(PATHARCHIVOCONF);
	this->mutex=mutex;
	if (parserAux->comprobarSintaxis()) {
		this->mazo=new Mazo();
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
	/* Operaciones Usadas:
	 * A - B - C - E - F - I - J - P - R - U - Z
	 * */
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
	res=toupper(idOperacionString[0]);
	if(res=="P"){//poso
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
		delete respuestaDeOperacion;
		delete operandos;
		return respuesta;

	}else if(res=="J"){//los jugadores jugando
		J* operadorJ= new J();
		list<string>* respuestaDeOperacion = operadorJ->realizarOperacion(this->jugadores);
		respuesta=this->parser->getXml(respuestaDeOperacion,idOperacionString);
		delete respuestaDeOperacion;
		delete operandos;
		return respuesta;

	}else if(res=="C"){//Cartas de la mesa
		C* operadorC=new C();
		list<string>* respuestaDeOperacion = operadorC->realizarOperacion(this->cartas);
		respuesta=this->parser->getXml(respuestaDeOperacion,idOperacionString);
		delete respuestaDeOperacion;
		delete operandos;
		return respuesta;

	}else if(res=="R"){//Registrarse
		R * operadorR = new R();
		list<string>* respuestaDeOperacion=operadorR->realizarOpearacion(operandos);
		respuesta=this->parser->getXml(respuestaDeOperacion,idOperacionString);
		delete respuestaDeOperacion;
		delete operandos;
		return respuesta;

	}else if(res=="A"){//de quien es el turno
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
		delete respuestaDeOperacion;
		delete operandos;
		return respuesta;
	}else if("B"){//Pedir las cartas de un jugador
		B * operadorB=new B();
		list<string>* respuestaDeOperacion=operadorB->realizarOpearacion(operandos,this->jugadores);
		respuesta=this->parser->getXml(respuestaDeOperacion,idOperacionString);
		delete respuestaDeOperacion;
		delete operandos;
		return respuesta;
	}else{
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
	return"";

}

Procesador * Procesador::instanciaUnica;
pthread_mutex_t Procesador::mutex;

Procesador *Procesador::instancia(){
		    if (!instanciaUnica){
		    	instanciaUnica =new Procesador(1);
		    	pthread_mutex_init(&Procesador::mutex,NULL);
		    }
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

bool Procesador::recibirArchivo(char * xml){
	ostringstream sstream;
	sstream << xml;
	string paraVerCuantoPesa = sstream.str();
	char xmlAux[paraVerCuantoPesa.size()];
	for(unsigned int i=0;i<paraVerCuantoPesa.size();i++){xmlAux[i]=xml[i];}
	string idOperacionString= this->parser->getOperacionId(xmlAux);
	idOperacionString=toupper(idOperacionString[0]);
	char idOperacionChar=idOperacionString[0];
	switch(idOperacionChar){
		case('Z'):{this->path=this->parser->getNombreJugador(xml) + ".bmp"; return true;}//Recibe la imagen del jugador
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

char* Procesador::getXml(list<string> *lista,string operacion){
	return this->parser->getXml(lista,operacion);
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
	pthread_mutex_lock(&this->mutex);
	if(this->jugadores->size() < MAXIMODEJUGADORES){
		this->jugadores->push_back(jugadorNuevo);
		pthread_mutex_unlock(&this->mutex);
		return true;
	}
	else{
		cout << "Maximo numero de jugadores en la mesa" << endl;
		pthread_mutex_unlock(&this->mutex);
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
	delete this->jugadores;
	this->jugadores=lista_aux;
	return true;
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

bool Procesador::estaJugandoJugador(string nombre_jugador){
	pthread_mutex_lock(&this->mutex);
	list<Jugador*>::iterator iterador=this->jugadores->begin();
	while(iterador!=this->jugadores->end()){
		if((*iterador)->getNombre()==nombre_jugador){
			pthread_mutex_unlock(&this->mutex);
			return true;
		}
		iterador++;
	}
	pthread_mutex_unlock(&this->mutex);
	return false;
}
Procesador::~Procesador() {
	delete this->parser;
}
