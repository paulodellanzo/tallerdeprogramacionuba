#include "ServidorCliente.h"
#include <sstream>
#include <fstream>
ServidorCliente::ServidorCliente(paraThreadsRecibidos* cliente) {
	this->cliente=cliente;
	this->procesador=Procesador::instancia();
	this->jugador=NULL;
}

char* ServidorCliente::recibirDeCliente(){
	char* data=new char[MAXBYTESRECIBIDOS];
	memset((void*)data,'\0',MAXBYTESRECIBIDOS);
	bool seguir=true;
	string path="recibidoDeCliente";
	ostringstream sstream;
	sstream << this->cliente->valorAcept;
	string aux = sstream.str();
	path+=aux;
	ofstream* archivoResultado = new ofstream(path.c_str(), ios::out);
	socklen_t leng=sizeof(char[MAXBYTESRECIBIDOS]);
	ssize_t valorRecive;
	while(seguir){
		valorRecive=recv(cliente->valorAcept,data,leng,0);
		if(valorRecive==0){
			delete []data;
			return " ";
		}
		if(valorRecive==-1){
			cout<<"Mal recibido"<<endl;
		}else{
			//corroboro que los ultimos tres formen eof
			if((data[valorRecive-1]=='f')and(data[valorRecive-2]=='o')and(data[valorRecive-3]=='e')){
				seguir=false;
				ostringstream sstream;
				sstream << data;
				string lineaActual = sstream.str();
				memset((void*)data,'\0',MAXBYTESRECIBIDOS);
//				Para sacar el eof del archivo
				string::iterator it=lineaActual.end();
				it--;
				it=lineaActual.erase(it);
				it--;
				it=lineaActual.erase(it);
				it--;
				it=lineaActual.erase(it);
				*archivoResultado<<lineaActual;
			}else{
				ostringstream sstream;
				sstream << data;
				string lineaActual = sstream.str();
				*archivoResultado<<lineaActual;
				delete []data;
				data=new char[MAXBYTESRECIBIDOS];
				memset((void*)data,'\0',MAXBYTESRECIBIDOS);
			}
		}
	}
	delete []data;
	archivoResultado->close();
	delete archivoResultado;
	string recibido;
	string *recibidoAux=new string;
	ifstream* archivo=new ifstream(path.c_str());
	while(!archivo->eof()){
		std::getline(*archivo,*recibidoAux);
		recibido+=*recibidoAux;
		recibido+="\n";
	}
	char* dataAux=new char[recibido.size() + 1];
	memset(dataAux,'\0',recibido.size() + 1);
	for(unsigned int i=0;i<recibido.size();i++) dataAux[i]=recibido[i];
	dataAux[recibido.size()]='\0';
	archivo->close();
	return dataAux;
}

string ServidorCliente::recibirArchivoDeCliente(string path){
        char* data=new char[MAXBYTESRECIBIDOS];
        memset((void*)data,'\0',MAXBYTESRECIBIDOS);
        bool seguir=true;
        ofstream* archivoResultado = new ofstream(path.c_str(), fstream::out | fstream::binary);
        socklen_t leng=sizeof(char[MAXBYTESRECIBIDOS]);
        ssize_t valorRecive;
        while(seguir){
                valorRecive=recv(cliente->valorAcept,data,leng,0);
                if(valorRecive==0){
                cout<<"Se desconecto el servidor.."<<endl;
                cout<<"Se cerrará la aplicación"<<endl;
                sleep(2);
                exit(0);
                }
                if(valorRecive==-1){
                        cout<<"Mal recibido"<<endl;
                }else{
                        //corroboro que los ultimos tres formen eof
                        if((data[valorRecive-1]=='f')and(data[valorRecive-2]=='o')and(data[valorRecive-3]=='e')){
                                seguir=false;
                                int bytes=valorRecive - 3;
                                char* final=new char[bytes];
                                for(int i=0;i<(valorRecive-3);i++) final[i]=data[i];
                                archivoResultado->write(final,bytes);
                                memset((void*)data,'\0',MAXBYTESRECIBIDOS);
                        }else{
                                archivoResultado->write(data,valorRecive);
                                memset((void*)data,'\0',MAXBYTESRECIBIDOS);
                                delete []data;
                                data=new char[MAXBYTESRECIBIDOS];
                                memset((void*)data,'\0',MAXBYTESRECIBIDOS);
                        }
                }
        }
        delete []data;
        archivoResultado->close();
        delete archivoResultado;
        return path;
}

int ServidorCliente::enviarACliente(char* data){
	ostringstream sstream;
	sstream << data;
	string paraVerCuantoPesa = sstream.str();
    unsigned int valorSend;
    valorSend = send(cliente->valorAcept, data, paraVerCuantoPesa.size(), 0);
    if (valorSend == -1) {cout<<"Mal enviado a cliente nº: "<<cliente->valorAcept<<endl; }
	delete []data;
	char* data2=new char[3];
	memset((void*)data2,'\0',3);
	data2[0]='e';
	data2[1]='o';
	data2[2]='f';
	valorSend=send(cliente->valorAcept,data2,3,0);
	if (valorSend == -1) {cout<<"Mal enviado a cliente nº: "<<cliente->valorAcept<<endl; }
	delete []data2;
	return valorSend;
}

int ServidorCliente::enviarArchivoBMP(string path){
    // referencia al archivo
    fstream  archivo;
    //intenta abrir el archivo en modo lectura y binario
    archivo.open(path.c_str(), fstream::in | fstream::binary );
    if(!archivo.good()){
    	cout<<"Mal imagen a enviar con path: " + path<<endl;
    	archivo.open("ArchivoDeError.bmp", fstream::in | fstream::binary);
    	if(!archivo.good()) cout<<"Mal archivo error bmp"<<endl;
    }
    char * data=new char[2];
    archivo.read((char*)data,2);
    int tamano;
    archivo.read((char*)&tamano,4);
    archivo.close();
    archivo.open(path.c_str(), fstream::in | fstream::binary );
	unsigned int valorSend;
	streamsize extraidos;
	delete []data;
	data=new char[tamano];
	extraidos=archivo.readsome(data,tamano);
	valorSend = send(cliente->valorAcept, data, extraidos, 0);
	if (valorSend == -1) {cout<<"Mal enviado a cliente nº: "<<cliente->valorAcept<<endl; }
	archivo.close();
	delete []data;
	char* data2=new char[3];
	memset((void*)data2,'\0',3);
	data2[0]='e';
	data2[1]='o';
	data2[2]='f';
	int auxValorSend;
	auxValorSend=send(cliente->valorAcept,data2,3,0);
	delete []data2;
	return (int)auxValorSend;

}


void ServidorCliente::interactuarConCliente(){
	bool seguir=true;
	int paraVerSiCortoComunicacion=0;
	char* xml,* data;
	while(seguir){
		xml=this->recibirDeCliente();
		seguir=((xml)!=" ");
		if(seguir){
			list<string>* lista=this->procesador->seConectoJugador(xml);
			if(lista!=NULL){
				if(lista->front()=="Correcto"){
					lista->pop_front();
					lista->pop_front();
					string nombre=lista->front();
					lista->pop_front();
					lista->pop_front();
					string password=lista->front();
					lista->pop_front();
					if(this->procesador->estaJugandoJugador(nombre)){
						lista->push_front("Ya esta logueado ese usuario");
						lista->push_front("V");
						lista->push_front("Error");
					}else{
						MYSQL_RES *res;
						MYSQL_ROW row;
						Conexion* conexion = Conexion::instancia();
						string q="select id from usuarios where usuario='"+nombre+"'";
						res = conexion->ejecutarQuery(q.c_str());
						row = mysql_fetch_row(res);
						string id = row[0];
						conexion->liberarConexion(res);

						string query = "insert into estadistica (fechaLogin,usuarioId) values(STR_TO_DATE(DATE_FORMAT(now(),'%d/%m/%Y'),'%d/%m/%Y'), "+id+")";
						res = conexion->ejecutarQuery(query.c_str());
						conexion->liberarConexion(res);

						this->jugador=new Jugador(nombre,password);
						lista->push_front(password);
						lista->push_front("password");
						lista->push_front(nombre);
						lista->push_front("Usuario");
						lista->push_front("Correcto");
					}
					data=this->procesador->getXml(lista,"U");
					paraVerSiCortoComunicacion=this->enviarACliente(data);
					delete xml;
				}else{
					data=this->procesador->getXml(lista,"U");
					paraVerSiCortoComunicacion=this->enviarACliente(data);
					delete xml;
				}
			}else if(this->procesador->enviarArchivo(xml)){
				string path=this->procesador->getPathArchivo();
				paraVerSiCortoComunicacion=this->enviarArchivoBMP(path);
				delete xml;
			}else if(this->procesador->empezarPartida(xml)){
				list<string>* lista=new list<string>();
				if(this->jugador!=NULL){
					this->procesador->agregarJugador(this->jugador);
					lista->push_front(this->jugador->getNombre());
					lista->push_front("password");
					lista->push_front(this->jugador->getNombre());
					lista->push_front("Usuario");
					lista->push_front("Correcto");
				}else{
					lista->push_front("No logueo usuario");
					lista->push_front("V");
					lista->push_front("Error");
				}
				data=this->procesador->getXml(lista,"M");
				paraVerSiCortoComunicacion=this->enviarACliente(data);
				delete xml;
			}else if(this->procesador->recibirArchivo(xml)){
				string path=this->procesador->getPathArchivo();
				char * data=new char[4];
				data[0]='h';
				data[1]='h';
				data[2]='h';
				data[3]='h';
				this->enviarACliente(data);
				this->recibirArchivoDeCliente(path);
				data=new char[4];
				data[0]='h';
				data[1]='h';
				data[2]='h';
				data[3]='h';
				this->enviarACliente(data);
				paraVerSiCortoComunicacion=1;
				delete xml;
			}else{
				data=this->procesador->getRespuesta(xml,this->jugador);
				paraVerSiCortoComunicacion=this->enviarACliente(data);
				delete xml;
			}
			//la corroboracion es para ver si devuelve 0 es porq se desconecto el cliente
			seguir=((paraVerSiCortoComunicacion!=0)and(paraVerSiCortoComunicacion!=(-1)));
		}
	}
	if(this->jugador!=NULL){
		this->procesador->quitarJugador(this->jugador);
		cout<<"Se quito el jugador: "<<this->jugador->getNombre()<<endl;
//		delete this->jugador;
	}
}
ServidorCliente::~ServidorCliente() {
	delete this->procesador;
}
