#include "ParserServidor.h"
using namespace std;

ParserServidor::ParserServidor() {
	this->tieneArchivo=false;
	this->tieneArchivoErrores=false;
	this->seCreoPath=false;
	// TODO Auto-generated constructor stub
}

ParserServidor::ParserServidor(const char* archivoXml){
	//Para abrir el archivo de configuracion
	this->seCreoPath=true;
	pathArchivo = new string(archivoXml);
	this->archivo = new ifstream(pathArchivo->c_str());
	if(this->archivo->good()){
		this->fallido=false;
		tieneArchivo=true;
	} else {
		this->fallido=true;
	}
	this->archivoerrores = new ofstream("errores.err", ios::out | ios::app);
	if(this->archivoerrores->good()){
			tieneArchivoErrores=true;
	} else {
		tieneArchivoErrores=false;
	}
}

bool ParserServidor::huboErrorAlAbrirArchivo(){
	return this->fallido;
}

bool ParserServidor::comprobarSintaxis(){
	string* cadenaArchivo = new string;
	//Para el error
	string operacionid("");
	string error;
	list<string>* listaErrores = new list<string>;
	char contador[10];
	int contadorLinea=0;
	string cadenaNodo;
	bool tagCorrecto;
	if(this->fallido){
		error="Hay un error al abrir el archivo";
		listaErrores->push_back("S");
		listaErrores->push_back(error);
		this->registrarError(operacionid,listaErrores);
		delete cadenaArchivo;
		return false;
		}
	this->construirGrafo();
	list<Nodo*>* nodosActuales = (this->grafoTags->getNodoPorClave(0))->getNodosHijos();
	while(true){
		std::getline(*(this->archivo),*cadenaArchivo);
		//Si termino el archivo me fijo si estoy en el eof del grafo
		contadorLinea++;
		list<Nodo*>::iterator iterador;
		iterador = nodosActuales->begin();
		if(this->archivo->eof()==true){
			while(iterador!=nodosActuales->end()){
				cadenaNodo=(*iterador)->getValor();
				if(cadenaNodo.compare("eof")==0){
					//Lo vuelvo al principio
					this->archivo->close();
					this->archivo->open(pathArchivo->c_str());
					delete cadenaArchivo;
					return true;
				}
				iterador++;
			}
			delete cadenaArchivo;
			return false;
		}
		tagCorrecto=false;
		while((iterador!=nodosActuales->end()) and (!tagCorrecto)){
			cadenaNodo=(*iterador)->getValor();
			if(this->comprobarTag(cadenaArchivo,&cadenaNodo)){
				tagCorrecto=true;
			} else {
				iterador++;
			}
		}
		if(!tagCorrecto){
			error+=("La linea ");
			sprintf(contador,"%d",contadorLinea);
			error+=contador;
			error+=" muestra: ";
			error+=*cadenaArchivo;
			error+=" debe mostrar: ";
			error+=cadenaNodo;
			listaErrores->push_back("S");
			listaErrores->push_back(error);
			this->registrarError(operacionid,listaErrores);
			delete cadenaArchivo;
			return false;
		}
		nodosActuales = (*iterador)->getNodosHijos();
		//Si no llegó al final de la lista es porque encontró el tag correcto y el iterador está parado en este
		//Si no tiene nodos hijos es porque se recorrió todo el grafo y la sintaxis está bien
		if(nodosActuales->empty()){
			//Lo vuelvo al principio
			this->archivo->close();
			this->archivo->open(pathArchivo->c_str());
			delete cadenaArchivo;
			return true;
		}
	}
}

bool ParserServidor::comprobarTag(string* cadenaArchivo,string* cadenaNodo){
	if(cadenaNodo->compare("valor")==0){
		return true;
	}
	string bufferCadenaArchivo(*cadenaArchivo);
	string bufferCadenaNodo(*cadenaNodo);
	//saco lo que se encuentra entre los tag
	int ini = (int)bufferCadenaArchivo.find("<");
	int fin = (int)bufferCadenaArchivo.rfind(">");
	bufferCadenaArchivo = bufferCadenaArchivo.substr(ini+1,fin-ini-1);
	ini = (int)bufferCadenaNodo.find("<");
	fin = (int)bufferCadenaNodo.rfind(">");
	bufferCadenaNodo = bufferCadenaNodo.substr(ini+1,fin-ini-1);
	//comparo el nombre del tag
	int espacioArchivo = (int)bufferCadenaArchivo.find(" ");
	int espacioNodo = (int)bufferCadenaNodo.find(" ");
	if(bufferCadenaArchivo.compare(0,espacioArchivo,bufferCadenaNodo,0,espacioNodo)!=0){
		return false;
	}
	//comparo el atributo (funciona para un solo atributo)
	bufferCadenaArchivo = bufferCadenaArchivo.substr(0,bufferCadenaArchivo.find("="));
	bufferCadenaNodo = bufferCadenaNodo.substr(0,bufferCadenaNodo.find("="));
	espacioArchivo = (int)bufferCadenaArchivo.rfind(" ");
	espacioNodo = (int)bufferCadenaNodo.rfind(" ");
	if(bufferCadenaArchivo.compare(espacioArchivo+1,bufferCadenaArchivo.size()-espacioArchivo-1,bufferCadenaNodo,espacioNodo+1,bufferCadenaNodo.size()-espacioNodo-1)!=0){
		return false;
	}
	//Ahora analiza la sintaxis de otra forma, validando otras cuestiones
	const char* charArchivo = cadenaArchivo->c_str();
	const char* charNodo = cadenaNodo->c_str();
	int tamanioArchivo=(int)strlen(charArchivo);
	int tamanioNodo=(int)strlen(charNodo);
	int tamanio;
	if(tamanioArchivo<tamanioNodo){
		tamanio=tamanioNodo;
	} else {
		tamanio=tamanioArchivo;
	}
	char bufferCharArchivo[tamanio];
	char bufferCharNodo[tamanio];
	int posicion=0;
	bool hayComilla=false;
	for(int i=0;i<tamanioArchivo+1;i++){
		if((charArchivo[i]!=' ') and (charArchivo[i]!='	') and (!hayComilla)){
			bufferCharArchivo[posicion]=charArchivo[i];
			posicion++;
		}
		if(charArchivo[i]=='\"'){
			if(hayComilla){
				hayComilla=false;
				bufferCharArchivo[posicion]=charArchivo[i];
				posicion++;
			} else {
				hayComilla=true;
			}
		}
	}
	posicion=0;
	hayComilla=false;
	for(int i=0;i<tamanioNodo+1;i++){
		if((charNodo[i]!=' ') and (charNodo[i]!='	') and (!hayComilla)){
			bufferCharNodo[posicion]=charNodo[i];
			posicion++;
		}
		if(charNodo[i]=='\"'){
			if(hayComilla){
				hayComilla=false;
				bufferCharNodo[posicion]=charNodo[i];
				posicion++;
			} else {
				hayComilla=true;
			}
		}
	}
	return(strcmp(bufferCharArchivo,bufferCharNodo)==0);
}

void ParserServidor::construirGrafo(){
	this->grafoTags = new Grafo();
	this->grafoTags->agregarNodo(new Nodo(0,"raiz"));
	this->grafoTags->agregarNodo(new Nodo(1,"<pedido>"));
	this->grafoTags->agregarNodo(new Nodo(2,"<operacion id=\"\"/>"));
	this->grafoTags->agregarNodo(new Nodo(3,"<parametros>"));
	this->grafoTags->agregarNodo(new Nodo(4,"<parametro nombre=\"\">"));
	this->grafoTags->agregarNodo(new Nodo(5,"valor"));
	this->grafoTags->agregarNodo(new Nodo(6, "</parametro>"));

	this->grafoTags->agregarNodo(new Nodo(7, "<jugador nombre=\"\">"));
	this->grafoTags->agregarNodo(new Nodo(8, "valor"));
	this->grafoTags->agregarNodo(new Nodo(9, "</jugador>"));
	this->grafoTags->agregarNodo(new Nodo(10, "<carta nombre=\"\">"));
	this->grafoTags->agregarNodo(new Nodo(11, "valor"));
	this->grafoTags->agregarNodo(new Nodo(12, "</carta>"));

	this->grafoTags->agregarNodo(new Nodo(13, "</parametros>"));
	this->grafoTags->agregarNodo(new Nodo(14,"</pedido>"));
	this->grafoTags->agregarNodo(new Nodo(15,"eof"));

	this->grafoTags->agregarArista(0, 1);
	this->grafoTags->agregarArista(1, 2);
	this->grafoTags->agregarArista(2, 3);
	this->grafoTags->agregarArista(3, 4);
	this->grafoTags->agregarArista(4, 5);
	this->grafoTags->agregarArista(5, 6);
	this->grafoTags->agregarArista(6, 4);
	this->grafoTags->agregarArista(6, 7);
	this->grafoTags->agregarArista(6, 10);
	this->grafoTags->agregarArista(6, 13);
	this->grafoTags->agregarArista(7, 8);
	this->grafoTags->agregarArista(8, 9);
	this->grafoTags->agregarArista(9, 7);
	this->grafoTags->agregarArista(9, 10);
	this->grafoTags->agregarArista(9, 13);
	this->grafoTags->agregarArista(10, 11);
	this->grafoTags->agregarArista(11, 12);
	this->grafoTags->agregarArista(12, 7);
	this->grafoTags->agregarArista(12, 10);
	this->grafoTags->agregarArista(12, 13);
	this->grafoTags->agregarArista(13, 14);
	this->grafoTags->agregarArista(14, 15);

}

void ParserServidor::registrarError(string idOperacion, list<string>* mensajesError) {
	(*this->archivoerrores) << "<respuesta>" << endl;
	(*this->archivoerrores) << "\t<operacion id=\"" << idOperacion << "\"/>" << endl;
	(*this->archivoerrores) << "\t<errores>" << endl;
	list<string>::const_iterator iterador;
	iterador = mensajesError->begin();
	while(iterador!=mensajesError->end()){
		//La lista tiene primero el tipo de error y luego sigue el mensaje, pueden haber varios
		(*this->archivoerrores) << "\t\t<error tipo=\"" << (*iterador) << "\">" << endl;
		iterador++;
		(*this->archivoerrores) << "\t\t" << (*iterador) << endl;
		iterador++;
		(*this->archivoerrores) << "\t\t</error>" << endl;
	}
	(*this->archivoerrores) << "\t</errores>" << endl;
	(*this->archivoerrores) << "</respuesta>" << endl;
}

informacionConfiguracion* ParserServidor::getInformacionConfig(){
	string* cadenaArchivo = new string;
	string xml = "";
	while (this->archivo->eof() == false) {

		std::getline(*(this->archivo), *cadenaArchivo);
		xml += *cadenaArchivo;
	}
	delete cadenaArchivo;
	char* xmlAux = new char[xml.size()];
	for (unsigned int i = 0; i < xml.size(); i++) {
		xmlAux[i] = xml[i];
	}
	char* buffer = strtok(xmlAux, "\n\t<>");
	buffer = strtok(NULL, "<>");
	buffer = strtok(NULL, "<>");
	informacionConfiguracion* infoconfig = new informacionConfiguracion;
	list<string>* jugadores = new list<string> ();
	list<string>* cartas = new list<string> ();
	while (buffer != NULL) {
		if (strcmp(buffer, "parametro") == 0) {
			buffer = strtok(NULL, "\t <>=\"");
			buffer = strtok(NULL, "\t <>=\"");
			if (strcmp(buffer, "archivoEscenario") == 0) {
				buffer = strtok(NULL, ">\n\t");
				infoconfig->pathEscenario = buffer;
			}
		} else if (strcmp(buffer, "jugador") == 0) {
			buffer = strtok(NULL, "\"<>\t\n ");
			buffer = strtok(NULL, "\"<>\t\n ");
			jugadores->push_back(buffer);
			buffer = strtok(NULL, ">\t\n");
			jugadores->push_back(buffer);

		} else if (strcmp(buffer, "carta") == 0) {
			buffer = strtok(NULL, "\"<>\t\n ");
			buffer = strtok(NULL, "\"<>\t\n ");
			cartas->push_back(buffer);
			buffer = strtok(NULL, ">\t\n");
			cartas->push_back(buffer);
		}
		buffer = strtok(NULL, " \t<>=");
	}

	infoconfig->jugadores = jugadores;
	infoconfig->cartas= cartas;
	this->archivo->close();
	return infoconfig;

}


informacionConexion* ParserServidor::getInformacionConexion(){
	string* cadenaArchivo = new string;
	string xml = "";
	while (this->archivo->eof() == false) {

		std::getline(*(this->archivo), *cadenaArchivo);
		xml += *cadenaArchivo;
	}
	delete cadenaArchivo;
	char* xmlAux = new char[xml.size()];
	for (unsigned int i = 0; i < xml.size(); i++) {
		xmlAux[i] = xml[i];
	}
	char* buffer = strtok(xmlAux, "\n\t<>");
	buffer = strtok(NULL, "<>");
	buffer = strtok(NULL, "<>");
	informacionConexion* infoconfig = new informacionConexion;
	list<string>* jugadores = new list<string> ();
	list<string>* cartas = new list<string> ();
	while (buffer != NULL) {
		if (strcmp(buffer, "parametro") == 0) {
			buffer = strtok(NULL, "\t <>=\"");
			buffer = strtok(NULL, "\t <>=\"");
			if (strcmp(buffer, "server") == 0) {
				buffer = strtok(NULL, ">\n\t");
				infoconfig->server= buffer;
			}else if(strcmp(buffer, "database") == 0) {
				buffer = strtok(NULL, ">\n\t");
				infoconfig->database= buffer;
			}else if(strcmp(buffer, "user") == 0) {
				buffer = strtok(NULL, ">\n\t");
				infoconfig->user= buffer;
			}else if(strcmp(buffer, "password") == 0) {
				buffer = strtok(NULL, ">\n\t");
				infoconfig->password= buffer;
			}
		}

			buffer = strtok(NULL, " \t<>=");
	}

	this->archivo->close();
	return infoconfig;

}


list<char*>* ParserServidor::getOperandos(char xml[]){
	list<char*>* aEnviar=new list<char*>();
	list<char*>::iterator it=aEnviar->begin();
	ostringstream sstream;
	sstream << xml;
	string xmlAux;
	xmlAux = sstream.str();
//	cout << "xml " << xmlAux << endl;
	size_t found;
	size_t found1;
	size_t found2;
	size_t found3;
	string valor;
//	cout << "holaaaa" << endl;
	found = xmlAux.find("nombre=");
	while (found < xmlAux.size()) {
		found1 = xmlAux.find_first_of(">", found);
		valor = xmlAux.substr(found + 8, found1 - found - 9);
		found2 = xmlAux.find_first_of("<", found1);
		char * aux= new char[valor.size()+1];
		memset((void*)aux,'\0',valor.size() + 1);
		for (int i=0;i<valor.size();i++)
			aux[i]=valor[i];
		aux[valor.size()]='\0';
		it = aEnviar->insert(it, aux);
//		cout << "valor " << valor << endl;
		it++;
		valor = xmlAux.substr(found1 + 1, found2 - found1 - 1);
		found3 = valor.find_first_of("\n\t");
		string toma;
		while (found3 != valor.size()) {
			if (valor[found3] != '\n' and valor[found3] != '\t')
				toma += valor[found3];
			found3++;
		}
		char * aux2= new char[toma.size()+1];
		memset((void*)aux2,'\0',toma.size() + 1);
		for (int i=0;i<toma.size();i++)
			aux2[i]=toma[i];
		aux2[toma.size()]='\0';
		it = aEnviar->insert(it, aux2);
//		cout << "toma "<< toma << endl;
		it++;
		found = xmlAux.find("nombre=", found2);
	}
//	cout << "holaaaa" << endl;
	return aEnviar;
}

string ParserServidor::getOperacionId(char xml[]){
	ostringstream sstream;
	sstream << xml;
	string xmlAux;
	xmlAux = sstream.str();
	size_t found;
	found = xmlAux.find("id=");
	string valor;
	valor = xmlAux.substr(found+4,1);
	return valor;
}

char* ParserServidor::getXml(list<string>* base, string idOperacion){
//	Arma el xml se fija si el primer nodo de la lista es CORRECTO o ERROR
	if(base->front()=="Error"){
		base->pop_front();
		return (this->armarXmlDeErrores(base,idOperacion));
	}else{
		base->pop_front();
		return (this->armarXmlDeResultado(base,idOperacion));
	}
}

char* ParserServidor::armarXmlDeErrores(list<string>* base,string idOperacion){
	string aEnviar;
	(aEnviar)="<respuesta>\n	</operacion id=\""+idOperacion+"\"/>\n	<errores>\n";
	list<string>::const_iterator iterador;
	iterador=base->begin();
	while(iterador!=base->end()){
		(aEnviar)+="		<error tipo=\""+(*iterador)+"\">\n";
		iterador++;
		(aEnviar)+="		"+(*iterador)+"\n		</error>\n";
		iterador++;
	}
	(aEnviar)+="	</errores>\n</respuesta>";
	char* data=new char[aEnviar.size() + 1];
	memset((void*)data,'\0',aEnviar.size() + 1);
	for(unsigned int i=0;i<aEnviar.size();i++){data[i]=aEnviar[i];}
	data[aEnviar.size()]='\0';
	return (data);

}

char* ParserServidor::armarXmlDeResultado(list<string>* base, string idOperacion){
	string aEnviar;
	(aEnviar)="<respuesta>\n	</operacion id=\""+idOperacion+"\"/>\n	<resultados>\n";
	list<string>::const_iterator iterador;
	iterador=base->begin();
	while(iterador!=base->end()){
		(aEnviar)+="		<resultado nombre=\""+(*iterador)+"\">\n";
		iterador++;
		(aEnviar)+="		"+(*iterador)+"\n		</resultado>\n";
		iterador++;
	}
	(aEnviar)+="	</resultados>\n</respuesta>";
	char* data=new char[aEnviar.size() + 1];
	memset((void*)data,'\0',aEnviar.size() + 1);
	for(unsigned int i=0;i<aEnviar.size();i++){data[i]=aEnviar[i];}
	data[aEnviar.size()]='\0';
	return (data);
}

string ParserServidor::getNombreJugador(char xml[]){
	ostringstream sstream; 	
	sstream << xml; 	
	string xmlAux; 	
	xmlAux = sstream.str(); 	
	size_t found; 	
	found = xmlAux.find("jugador\">"); 	
	size_t found2; 	
	found2 = xmlAux.find_first_of("<",found); 	
	string valor; 	
	valor = xmlAux.substr(found+9,found2-found-9); 	
	size_t found3; 	
	found3 = valor.find_first_of("\n\t"); 
	string jugador; 	
	while (found3 != valor.size()) { 		
		if (valor[found3] != '\n' and valor[found3] != '\t') 				jugador += valor[found3]; 		
		found3++; 	
	} 
	return jugador;
}

ParserServidor::~ParserServidor() {
	if(this->seCreoPath) delete pathArchivo;
	if(this->tieneArchivo){
		this->archivo->close();
		delete this->archivo;
	}
	if(this->tieneArchivoErrores){
		(*this->archivoerrores).close();
		delete this->archivoerrores;
	}
}
