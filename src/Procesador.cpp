#include "Procesador.h"

void* empiezaJuego(void* procesadorPasado){
	Procesador* procesador=(Procesador*) procesadorPasado;
	procesador->jugar();
	return NULL;
}

void Procesador::empezarPartida(){
	this->nombreJugadorJugando=this->jugadores->front()->getNombre();
}

bool Procesador::empezarPartida(char * xml){
	ostringstream sstream;
	sstream << xml;
	string paraVerCuantoPesa = sstream.str();
	char xmlAux[paraVerCuantoPesa.size()];
	for(unsigned int i=0;i<paraVerCuantoPesa.size();i++){xmlAux[i]=xml[i];}
	string idOperacionString= this->parser->getOperacionId(xmlAux);
	idOperacionString=toupper(idOperacionString[0]);
	char idOperacionChar=idOperacionString[0];
	return idOperacionChar=='M';

}
void Procesador::jugar(){

	list<Jugador*>::iterator itJugadores;
	while (true){
		while(jugadores->size()>=2){
			//Inicializo variables
			Carta* cartaAuxiliar;
			this->mazo = new Mazo();
			bool finDeApuestas;
			this->apuestaMayorEnRonda=0;
			this->bote=0;

			//Reparto dos cartas a cada jugador y empiezan a jugar
			itJugadores=jugadores->begin();
			while(itJugadores!=jugadores->end()){
				(*itJugadores)->setCartas(mazo->getCarta(),mazo->getCarta());
				(*itJugadores)->empezarAJugar();
				(*itJugadores)->setUltimaApuesta(-1);
				itJugadores++;
			}
			this->empezarPartida();
			cout<<"Empieza la partida"<<endl;
			sleep(2);

			//TODO Primera ronda de apuestas
			finDeApuestas=false;
			while(!finDeApuestas){
				finDeApuestas=true;
				itJugadores=jugadores->begin();
				while (itJugadores!=jugadores->end()){
					if(!(*itJugadores)->igualoApuestaMano(this->apuestaMayorEnRonda) and (*itJugadores)->participando())
						finDeApuestas=false;
					else
						cout<<"Ya aposto: "<<(*itJugadores)->getNombre()<<endl;
					itJugadores++;
				}
			}
			sleep(2);
			this->apuestaMayorEnRonda=0;

			itJugadores=this->jugadores->begin();
			while(itJugadores!=jugadores->end()){
				(*itJugadores)->setUltimaApuesta(-1);
				itJugadores++;
			}

			//Agrego primeras tres cartas comunitarias
			for(int i=0;i<3;i++){
				cartaAuxiliar=mazo->getCarta();
				this->agregarCarta(cartaAuxiliar);
			}
			cout<<"Agregamos las tres primeras cartas"<<endl;
			sleep(2);

			//TODO Segunda ronda de apuestas
			finDeApuestas=false;
			while(!finDeApuestas){
				finDeApuestas=true;
				itJugadores=jugadores->begin();
				while (itJugadores!=jugadores->end()){
					if(!(*itJugadores)->igualoApuestaMano(this->apuestaMayorEnRonda) and (*itJugadores)->participando())
						finDeApuestas=false;
					else
						cout<<"Ya aposto: "<<(*itJugadores)->getNombre()<<endl;
					itJugadores++;
				}
			}

			sleep(2);
			this->apuestaMayorEnRonda=0;

			itJugadores=this->jugadores->begin();
			while(itJugadores!=jugadores->end()){
				(*itJugadores)->setUltimaApuesta(-1);
				itJugadores++;
			}

			//Agrego cuarta carta comunitaria
			cartaAuxiliar=mazo->getCarta();
			this->agregarCarta(cartaAuxiliar);
			cout<<"Agregamos la cuarta carta"<<endl;

			//TODO Tercera ronda de apuestas
			finDeApuestas=false;
			while(!finDeApuestas){
				finDeApuestas=true;
				itJugadores=jugadores->begin();
				while (itJugadores!=jugadores->end()){
					if(!(*itJugadores)->igualoApuestaMano(this->apuestaMayorEnRonda) and (*itJugadores)->participando())
						finDeApuestas=false;
					else
						cout<<"Ya aposto: "<<(*itJugadores)->getNombre()<<endl;
					itJugadores++;
				}
			}

			sleep(2);
			this->apuestaMayorEnRonda=0;

			itJugadores=this->jugadores->begin();
			while(itJugadores!=jugadores->end()){
				(*itJugadores)->setUltimaApuesta(-1);
				itJugadores++;
			}

			//Agrego quinta carta comunitaria
			cout<<"Agregamos la quinta carta"<<endl;
			cartaAuxiliar=mazo->getCarta();
			this->agregarCarta(cartaAuxiliar);

			//TODO Cuarta ronda de apuestas

			finDeApuestas=false;

			while(!finDeApuestas){
				finDeApuestas=true;
				itJugadores=jugadores->begin();
				while (itJugadores!=jugadores->end()){
					if(!(*itJugadores)->igualoApuestaMano(this->apuestaMayorEnRonda) and (*itJugadores)->participando())
						finDeApuestas=false;
					else
						cout<<"Ya aposto: "<<(*itJugadores)->getNombre()<<endl;
					itJugadores++;
				}
			}

			sleep(2);
			this->apuestaMayorEnRonda=0;

			cout<<"Gano: ";

			Jugador* jugadorGanador;
			float puntajeGanador=0;
			itJugadores=this->jugadores->begin();
			list<Carta> * lista_aux=new list<Carta>;
			list<Carta*>::iterator itCartas=this->cartas->begin();

			//Agrego las cartas comunitarias
			while(itCartas!=this->cartas->end()){
				lista_aux->push_front(*(*itCartas));
				itCartas++;
			}

			while(itJugadores!=jugadores->end()){
				list<Carta*> * cartasJugador=(*itJugadores)->getCartas();
				//Agrego las cartas del jugador a la lista
				lista_aux->push_front(*(cartasJugador->front()));
				lista_aux->push_front(*(cartasJugador->back()));

				Poker * poker=new Poker(lista_aux);
				float puntaje=poker->getPuntaje();

				if(puntaje>puntajeGanador){
					puntajeGanador=puntaje;
					jugadorGanador=(*itJugadores);
				}

				itJugadores++;
				delete poker;
				//Saco las cartas del jugador de la lista
				lista_aux->pop_back();
				lista_aux->pop_back();
			}

			jugadorGanador->modificarPlataEn(this->bote);
			cout<<jugadorGanador->getNombre()<<" con puntaje: "<<puntajeGanador<<endl;
			this->bote=0;
			sleep(2);

			//Destruyo objetos
			this->vaciarCartas();
			delete mazo;
			delete lista_aux;

			itJugadores=this->jugadores->begin();
			while(itJugadores!=jugadores->end()){
				(*itJugadores)->setCartas(NULL,NULL);
				itJugadores++;
			}

			//Paso los jugadores a agregar a la lista de jugadores
			itJugadores=jugadores->end();
			jugadores->splice(itJugadores,*jugadores_agregar);
			sleep(5);
		}
		//Paso los jugadores a agregar a la lista de jugadores
		itJugadores=jugadores->end();
		jugadores->splice(itJugadores,*jugadores_agregar);
		sleep(5);
	}
}

void Procesador::vaciarCartas(){
	pthread_mutex_lock(&this->mutex);
	while(this->cartas->size()>0){
		this->cartas->pop_front();
	}
	pthread_mutex_unlock(&this->mutex);
}

Procesador::Procesador(int i) {
	pthread_t hilo;
	ParserServidor *parserAux = new ParserServidor(PATHARCHIVOCONF);
	this->mutex=mutex;
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
	this->jugadores_a_dibujar = new list<Jugador*>();
	this->jugadores_agregar = new list<Jugador*>();
	this->bote = 0;
	this->apuestaMayorEnRonda = 0;
	delete parserAux;
	this->estaJugando=false;
	pthread_create(&hilo,NULL,empiezaJuego,(void*)this);

}

char* Procesador::getRespuesta(char* xml, Jugador * jugador){
	/* Operaciones Usadas:
	 * A - B - C - D - E - F - G - H - I - J - K - L - M - N - P - R - U - Z
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
		delete operadorJ;
		return respuesta;

	}else if(res=="C"){//Cartas de la mesa
		C* operadorC=new C();
		list<string>* respuestaDeOperacion = operadorC->realizarOperacion(this->cartas);
		respuesta=this->parser->getXml(respuestaDeOperacion,idOperacionString);
		delete respuestaDeOperacion;
		delete operandos;
		delete operadorC;
		return respuesta;

	}else if(res=="R"){//Registrarse
		R * operadorR = new R();
		list<string>* respuestaDeOperacion=operadorR->realizarOpearacion(operandos);
		respuesta=this->parser->getXml(respuestaDeOperacion,idOperacionString);
		delete respuestaDeOperacion;
		delete operandos;
		delete operadorR;
		return respuesta;

	}else if(res=="N"){//Registrarse
			N * operadorN = new N();
			list<string>* respuestaDeOperacion=operadorN->realizarOpearacion(operandos);
			respuesta=this->parser->getXml(respuestaDeOperacion,idOperacionString);
			delete respuestaDeOperacion;
			delete operandos;
			delete operadorN;
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
	}else if(res=="B"){//Pedir las cartas de un jugador
		B * operadorB=new B();
		pthread_mutex_lock(&this->mutex);
		list<string>* respuestaDeOperacion=operadorB->realizarOpearacion(operandos,this->jugadores_a_dibujar);
		pthread_mutex_unlock(&this->mutex);
		respuesta=this->parser->getXml(respuestaDeOperacion,idOperacionString);
		delete respuestaDeOperacion;
		delete operandos;
		delete operadorB;
		return respuesta;
	}else if(res=="K"){//ranking de usuarios
		K * operadorK=new K();
		list<string>* respuestaDeOperacion=operadorK->realizarOpearacion(operandos);
		respuesta=this->parser->getXml(respuestaDeOperacion,idOperacionString);
		delete respuestaDeOperacion;
		delete operandos;
		delete operadorK;
		return respuesta;
	}else if(res=="D"){//Apuesta
		cout<<"Aposto jugador: "<<jugador->getNombre()<<endl;
		D* operadorD=new D();
		list<string> * respuestaDeOperacion=operadorD->realizarOperacion(operandos,jugador);
		string aux=respuestaDeOperacion->front();
		if(aux=="Correcto"){
			string apuestaString=respuestaDeOperacion->back();
			int apuesta=atoi(apuestaString.c_str());
			cout<<apuesta<<endl;
			this->bote+=apuesta;
			if(this->apuestaMayorEnRonda<apuesta){
				this->apuestaMayorEnRonda=apuesta;
			}
		}
		respuesta=this->parser->getXml(respuestaDeOperacion,idOperacionString);
		this->terminoMiTurno();
		delete respuestaDeOperacion;
		delete operandos;
		delete operadorD;
		return respuesta;
	}else if(res=="F"){//Pasar
		list<string>* respuestaDeOperacion = new list<string>();
		list<string>::iterator it;
		it = respuestaDeOperacion->begin();
		it = respuestaDeOperacion->insert(it, "Correcto");
		it++;
		it = respuestaDeOperacion->insert(it, "pasar");
		it++;
		it = respuestaDeOperacion->insert(it, "0");
		it++;
		respuesta=this->parser->getXml(respuestaDeOperacion,idOperacionString);
		delete respuestaDeOperacion;
		this->terminoMiTurno();
		return respuesta;

	}else if(res=="G"){//La maxima apuesta en esa mano
		ostringstream sstream;
		sstream << this->apuestaMayorEnRonda;
		string apuestaString = sstream.str();
		list<string>* respuestaDeOperacion = new list<string>();
		list<string>::iterator it;
		it = respuestaDeOperacion->begin();
		it = respuestaDeOperacion->insert(it, "Correcto");
		it++;
		it = respuestaDeOperacion->insert(it, "apuestaMax");
		it++;
		it = respuestaDeOperacion->insert(it, apuestaString);
		it++;
		respuesta=this->parser->getXml(respuestaDeOperacion,idOperacionString);
		delete respuestaDeOperacion;
		delete operandos;
		return respuesta;

	}else if(res=="H"){//Para cargar plata

	}else if(res=="L"){//Pedir apuesta de cierto jugador
		L * operadorL=new L();
		list<string>* respuestaDeOperacion=operadorL->realizarOpearacion(operandos,this->jugadores_a_dibujar);
		respuesta=this->parser->getXml(respuestaDeOperacion,idOperacionString);
		delete respuestaDeOperacion;
		delete operandos;
		delete operadorL;
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
		cout<<"Se agrego Jugador: "<<jugadorNuevo->getNombre()<<endl;
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
	if(jugador->getNombre()==this->nombreJugadorJugando)
		this->terminoMiTurno();
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

	//Aca le persisto la plata del jugador que se fue
	Conexion* conexion = Conexion::instancia();
	ostringstream sstream;
	sstream << jugador->plataRestante();
	string plata = sstream.str();
	string query="update usuarios set plata='"+plata+"' where usuario='"+jugador->getNombre()+"'";
	MYSQL_RES *res;
	MYSQL_ROW row;
	res = conexion->ejecutarQuery(query.c_str());
	conexion->liberarConexion(res);
	return true;
}

bool Procesador::agregarCarta(Carta* cartaNueva){
	pthread_mutex_lock(&this->mutex);
	if(this->cartas->size() < MAXIMODECARTAS){
		this->cartas->push_back(cartaNueva);
		pthread_mutex_unlock(&this->mutex);
		return true;
	}
	else{
		delete cartaNueva;
		cout << "Maximo numero de cartas en la mesa" << endl;
		pthread_mutex_unlock(&this->mutex);
		return false;
	}
}

void Procesador::terminoMiTurno(){
	Jugador * jugadorEnTurno=this->jugadores->front();
	this->jugadores->pop_front();
	if(jugadorEnTurno->participando())
		this->jugadores->push_back(jugadorEnTurno);
	bool seguir=true;
	string nombreJugador;
	while(seguir and this->jugadores->size()>0){
		jugadorEnTurno=this->jugadores->front();
		this->jugadores->pop_front();
		if(jugadorEnTurno->participando()){
			this->nombreJugadorJugando=jugadorEnTurno->getNombre();
			this->jugadores->push_front(jugadorEnTurno);
			seguir=false;
		}
	}
	if(seguir)
		this->nombreJugadorJugando=" ";
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
