#include "Procesador.h"

void* empiezaJuego(void* procesadorPasado){
	Procesador* procesador=(Procesador*) procesadorPasado;
	procesador->jugar();
	return NULL;
}

bool Procesador::abandonarMano(){
	if(sizeJugadores==0){
		this->nombreJugadorJugando=" ";
		this->bote=0;
		this->apuestaMayorEnRonda=0;
		this->vaciarCartas();
		return true;
	}else if(sizeJugadores==1){
		this->nombreJugadorJugando=" ";
		this->ganador=jugadores->front()->getNombre();
		cout<<"Gano: "<<this->ganador<<endl;
		jugadores->front()->setCartas(NULL,NULL);
		if(this->jugadores->front()->participando()){
			this->jugadores->front()->modificarPlataEn(this->bote);
			this->jugadores->front()->dejarDeJugar();
		}
		this->bote=0;
		this->apuestaMayorEnRonda=0;
		this->vaciarCartas();
		return true;
	}
	return false;
}

void Procesador::empezarPartida(){
	this->nombreJugadorJugando=this->jugadores->front()->getNombre();
	cout<<"Es el turno de: "<<this->nombreJugadorJugando<<endl;
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
			this->ganador=" ";
			this->sizeJugadores=this->jugadores->size();
			//Inicializo variables
			itJugadores=this->jugadores->begin();
			while(itJugadores!=jugadores->end()){
				(*itJugadores)->setCartas(NULL,NULL);
				itJugadores++;
			}

			Carta* cartaAuxiliar;
			this->mazo = new Mazo();
			bool finDeApuestas;
			this->apuestaMayorEnRonda=0;
			this->bote=0;

			if(this->abandonarMano()){
				break;
			}

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

			sleep(0.5);

			//TODO Primera ronda de apuestas
			finDeApuestas=false;
			while(!finDeApuestas){
				finDeApuestas=true;
				if(this->abandonarMano()){
					break;
				}
				itJugadores=jugadores->begin();
				while (itJugadores!=jugadores->end()){
					if(this->abandonarMano()){
						break;
					}
					if(!(*itJugadores)->igualoApuestaMano(this->apuestaMayorEnRonda))
						if((*itJugadores)->participando()){
							finDeApuestas=false;
						}
					if(this->abandonarMano()){
						break;
					}
					itJugadores++;
				}
			}

			this->apuestaMayorEnRonda=0;

			if(this->abandonarMano()){
				break;
			}

			itJugadores=this->jugadores->begin();
			while(itJugadores!=jugadores->end()){
				(*itJugadores)->setUltimaApuesta(-1);
				itJugadores++;
			}

			if(this->abandonarMano()){
				break;
			}

			//Agrego primeras tres cartas comunitarias
			for(int i=0;i<3;i++){
				cartaAuxiliar=mazo->getCarta();
				this->agregarCarta(cartaAuxiliar);
			}
			sleep(1);
			cout<<"Agregamos las tres primeras cartas"<<endl;


			if(this->abandonarMano()){
				break;
			}

			//TODO Segunda ronda de apuestas
			finDeApuestas=false;
			while(!finDeApuestas){
				finDeApuestas=true;
				if(this->abandonarMano()){
					break;
				}
				itJugadores=jugadores->begin();
				while (itJugadores!=jugadores->end()){
					if(this->abandonarMano()){
						break;
					}
					if(!(*itJugadores)->igualoApuestaMano(this->apuestaMayorEnRonda))
						if((*itJugadores)->participando()){
							finDeApuestas=false;
						}
					if(this->abandonarMano()){
						break;
					}
					itJugadores++;
				}
			}

			this->apuestaMayorEnRonda=0;

			if(this->abandonarMano()){
				break;
			}
			itJugadores=this->jugadores->begin();
			while(itJugadores!=jugadores->end()){
				(*itJugadores)->setUltimaApuesta(-1);
				itJugadores++;
			}

			if(this->abandonarMano()){
				break;
			}


			//Agrego cuarta carta comunitaria
			cartaAuxiliar=mazo->getCarta();
			this->agregarCarta(cartaAuxiliar);


			if(this->abandonarMano()){
				break;
			}
			sleep(1);
			cout<<"Agregamos la cuarta carta"<<endl;
			//TODO Tercera ronda de apuestas
			finDeApuestas=false;
			while(!finDeApuestas){
				finDeApuestas=true;
				if(this->abandonarMano()){
					break;
				}
				itJugadores=jugadores->begin();
				while (itJugadores!=jugadores->end()){
					if(this->abandonarMano()){
						break;
					}
					if(!(*itJugadores)->igualoApuestaMano(this->apuestaMayorEnRonda))
						if((*itJugadores)->participando()){
							finDeApuestas=false;
						}
					if(this->abandonarMano()){
						break;
					}
					itJugadores++;
				}
			}

			this->apuestaMayorEnRonda=0;

			if(this->abandonarMano()){
				break;
			}

			itJugadores=this->jugadores->begin();
			while(itJugadores!=jugadores->end()){
				(*itJugadores)->setUltimaApuesta(-1);
				itJugadores++;
			}

			if(this->abandonarMano()){
				break;
			}

			//Agrego quinta carta comunitaria

			cartaAuxiliar=mazo->getCarta();
			this->agregarCarta(cartaAuxiliar);

			//TODO Cuarta ronda de apuestas
			if(this->abandonarMano()){
				break;
			}
			sleep(1);
			cout<<"Agregamos la quinta carta"<<endl;
			finDeApuestas=false;
			while(!finDeApuestas){
				finDeApuestas=true;
				if(this->abandonarMano()){
					break;
				}
				itJugadores=jugadores->begin();
				while (itJugadores!=jugadores->end()){
					if(this->abandonarMano()){
						break;
					}
					if(!(*itJugadores)->igualoApuestaMano(this->apuestaMayorEnRonda))
						if((*itJugadores)->participando()){
							finDeApuestas=false;
						}
					if(this->abandonarMano()){
						break;
					}
					itJugadores++;
				}
			}

			this->apuestaMayorEnRonda=0;

			if(this->abandonarMano()){
				break;
			}
			this->nombreJugadorJugando=" ";

			sleep(1);
			cout<<"Gano: ";

			if(this->abandonarMano()){
				break;
			}

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

			if(this->abandonarMano()){
				break;
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
				if(this->abandonarMano()){
					break;
				}
			}

			if(this->abandonarMano()){
				break;
			}

			jugadorGanador->modificarPlataEn(this->bote);
			this->ganador=jugadorGanador->getNombre();
			cout<<this->ganador<<" con puntaje: "<<puntajeGanador<<endl;
			this->bote=0;


			//Destruyo objetos
			delete mazo;
			delete lista_aux;
			sleep(5);

			this->vaciarCartas();

			if(this->abandonarMano()){
				break;
			}

			itJugadores=this->jugadores->begin();
			while(itJugadores!=jugadores->end()){
				(*itJugadores)->setCartas(NULL,NULL);
				itJugadores++;
			}

			if(this->abandonarMano()){
				break;
			}

			cout<<"Todo listo para comenzar una nueva partida"<<endl;
			//Paso los jugadores a agregar a la lista de jugadores
			itJugadores=jugadores->end();
			jugadores->splice(itJugadores,*jugadores_agregar);
			sleep(1);
		}
		//Paso los jugadores a agregar a la lista de jugadores
		itJugadores=jugadores->end();
		jugadores->splice(itJugadores,*jugadores_agregar);
		sleep(2);
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
	this->ganador=" ";
	this->jugadores = new list<Jugador*>();
	this->jugadores_a_dibujar = new list<Jugador*>();
	this->jugadores_agregar = new list<Jugador*>();
	this->bote = 0;
	this->apuestaMayorEnRonda = 0;
	delete parserAux;
	this->estaJugando=false;
	this->sizeJugadores=0;
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
			if(respuestaDeOperacion->front()=="Correcto"){
				long int monto=atoi(respuestaDeOperacion->back().c_str());
				jugador->modificarPlataEn(monto);
			}
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
		string nombreJugador=this->nombreJugadorJugando;
		if(nombreJugador=="") nombreJugador="/";
		it = respuestaDeOperacion->insert(it, nombreJugador);
		it++;
		respuesta=this->parser->getXml(respuestaDeOperacion,idOperacionString);
		delete respuestaDeOperacion;
		delete operandos;
		return respuesta;
	}else if(res=="H"){//Pedir el ganador
		list<string>* respuestaDeOperacion = new list<string>();
		list<string>::iterator it;
		it = respuestaDeOperacion->begin();
		it = respuestaDeOperacion->insert(it, "Correcto");
		it++;
		it = respuestaDeOperacion->insert(it, "jugador");
		it++;
		string nombreJugador=this->ganador;
		if(nombreJugador=="") nombreJugador="/";
		it = respuestaDeOperacion->insert(it, nombreJugador);
		it++;
		respuesta=this->parser->getXml(respuestaDeOperacion,idOperacionString);
		delete respuestaDeOperacion;
		delete operandos;
		return respuesta;
	}else if(res=="B"){//Pedir las cartas de un jugador
		B * operadorB=new B();
		list<string>* respuestaDeOperacion=operadorB->realizarOpearacion(operandos,this->jugadores_a_dibujar);
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
		cout<<"Pasa : ";
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
		jugador->setUltimaApuesta(this->apuestaMayorEnRonda);
		cout<<jugador->getNombre()<<endl;
		this->terminoMiTurno();
		return respuesta;

	}else if(res=="Y"){//Igualar
		cout<<"Iguala : ";
		list<string>* respuestaDeOperacion = new list<string>();
		list<string>::iterator it;
		it = respuestaDeOperacion->begin();
		it = respuestaDeOperacion->insert(it, "Correcto");
		it++;
		it = respuestaDeOperacion->insert(it, "igualar");
		it++;
		it = respuestaDeOperacion->insert(it, "0");
		it++;
		respuesta=this->parser->getXml(respuestaDeOperacion,idOperacionString);
		delete respuestaDeOperacion;
		int diferencia;
		if(jugador->getUltimaApuesta()!=(-1)){
			diferencia = (jugador->getUltimaApuesta() - this->apuestaMayorEnRonda);
		}else{
			diferencia = (0 -this->apuestaMayorEnRonda);
		}
		jugador->modificarPlataEn(diferencia);
		jugador->setUltimaApuesta(this->apuestaMayorEnRonda);
		this->bote-=diferencia;
		cout<<jugador->getNombre()<<endl;
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
	this->sizeJugadores--;
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
	if(jugadorEnTurno->participando()){
		this->jugadores->push_back(jugadorEnTurno);
	}else{
		this->jugadores_agregar->push_back(jugadorEnTurno);
		this->sizeJugadores--;
	}
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
	cout<<"Es el turno de: "<<this->nombreJugadorJugando<<endl;
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
