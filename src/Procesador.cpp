#include "Procesador.h"
using namespace std;
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <cstdlib>

void* empiezaJuego(void* procesadorPasado){
	Procesador* procesador=(Procesador*) procesadorPasado;
	procesador->jugar();
	return NULL;
}

void Procesador::jugar(){
	while (true){

		while(jugadores_a_dibujar->size()>=2){ //TODO Hay que reemplazar jugadores_a_dibujar por jugadores
			//Inicializo variables
			list<Jugador*>::iterator itJugadores;
			Carta* cartaAuxiliar;
			Mazo* mazo = new Mazo();
			itJugadores=jugadores->begin();
			list<Carta>* cartasComunitarias=new list<Carta>;
			bool finDeApuestas;

			//Reparto dos cartas a cada jugador
			while(itJugadores!=jugadores->end()){
				(*itJugadores)->setCartas(mazo->getCarta(),mazo->getCarta());
				itJugadores++;
			}

			//TODO Primera ronda de apuestas
			finDeApuestas=false;
			while(finDeApuestas==false){



			}

			//Agrego primeras tres cartas comunitarias
			for(int i=0;i<3;i++){
				cartaAuxiliar=mazo->getCarta();
				this->agregarCarta(cartaAuxiliar);
				cartasComunitarias->push_back(Carta(cartaAuxiliar->getPalo(),cartaAuxiliar->getNumero()));
			}

			//TODO Segunda ronda de apuestas
			finDeApuestas=false;
			while(finDeApuestas==false){

			}

			//Agrego cuarta carta comunitaria
			cartaAuxiliar=mazo->getCarta();
			this->agregarCarta(cartaAuxiliar);
			cartasComunitarias->push_back(Carta(cartaAuxiliar->getPalo(),cartaAuxiliar->getNumero()));

			//TODO Tercera ronda de apuestas
			finDeApuestas=false;
			while(finDeApuestas==false){

			}

			//Agrego quinta carta comunitaria
			cartaAuxiliar=mazo->getCarta();
			this->agregarCarta(cartaAuxiliar);
			cartasComunitarias->push_back(Carta(cartaAuxiliar->getPalo(),cartaAuxiliar->getNumero()));

			//TODO Cuarta ronda de apuestas
			finDeApuestas=false;
			while(finDeApuestas==false){
			}

			//TODO Ver quien ganó

			//Destruyo objetos
			delete mazo;
			delete cartasComunitarias;
		}
		//TODO Agregar jugadores_agregar a jugadores


	}
}

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
	pthread_t hilo;
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
	this->jugadores_a_dibujar = new list<Jugador*>();
	this->jugadores_agregar = new list<Jugador*>();
	this->bote = 500;
	this->apuestaMayorEnRonda = 0;
	this->setMesa();
	delete parserAux;
	this->estaJugando=false;
	pthread_create(&hilo,NULL,empiezaJuego,(void*)this);

}

char* Procesador::getRespuesta(char* xml){
	/* Operaciones Usadas:
	 * A - B - C - E - I - J - P - R - U - Z
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

	}else if(res=="J"){//los jugadores que estan en la mesa
		J* operadorJ= new J();
		list<string>* respuestaDeOperacion = operadorJ->realizarOperacion(this->jugadores_a_dibujar);
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
		list<string>* respuestaDeOperacion=operadorB->realizarOpearacion(operandos,this->jugadores_a_dibujar);
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

char* Procesador::getXml(list<string> *lista,string operacion){
	char* data =this->parser->getXml(lista,operacion);
	delete lista;
	return data;
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
		list<string> * lista=operadorU->realizarOpearacion(operandos);
		delete operadorU;
		return lista;
	}else{
		delete operadorU;
		return NULL;
	}
}

bool Procesador::agregarJugador(Jugador* jugadorNuevo){
	//IMPORTANTE CUANDO SE AGREGUE EL JUGADOR HAY QUE BUSCA EN MYSQL LA TABLA Y SACAR EL DINERO QUE TIENE
	pthread_mutex_lock(&this->mutex);
	if(this->jugadores_a_dibujar->size() < MAXIMODEJUGADORES){
		this->jugadores_a_dibujar->push_back(jugadorNuevo);
		this->jugadores_agregar->push_back(jugadorNuevo);
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
	while(this->jugadores_a_dibujar->size()>0){
		Jugador* juga=this->jugadores_a_dibujar->back();
		this->jugadores_a_dibujar->pop_back();
		if(juga->getNombre()!=jugador->getNombre()){
			lista_aux->push_front(juga);
		}
	}
	delete this->jugadores_a_dibujar;
	this->jugadores_a_dibujar=lista_aux;

	list<Jugador*>* lista_aux2=new list<Jugador*>();
	while(this->jugadores->size()>0){
		Jugador* juga=this->jugadores->back();
		this->jugadores->pop_back();
		if(juga->getNombre()!=jugador->getNombre()){
			lista_aux2->push_front(juga);
		}
	}
	delete this->jugadores;
	this->jugadores=lista_aux2;

	list<Jugador*>* lista_aux3=new list<Jugador*>();
	while(this->jugadores_agregar->size()>0){
		Jugador* juga=this->jugadores_agregar->back();
		this->jugadores_agregar->pop_back();
		if(juga->getNombre()!=jugador->getNombre()){
			lista_aux3->push_front(juga);
		}
	}
	delete this->jugadores_agregar;
	this->jugadores_agregar=lista_aux3;
	return true;
}

bool Procesador::agregarCarta(Carta* cartaNueva){
	if(this->cartas->size() < MAXIMODECARTAS){
		this->cartas->push_back(cartaNueva);
		return true;
	}
	else{
		delete cartaNueva;
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
	list<Jugador*>::iterator iterador=this->jugadores_a_dibujar->begin();
	while(iterador!=this->jugadores_a_dibujar->end()){
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
