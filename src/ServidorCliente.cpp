#include "ServidorCliente.h"
#include <sstream>
#include <fstream>
ServidorCliente::ServidorCliente(paraThreadsRecibidos* cliente) {
	this->cliente=cliente;
	this->procesador=Procesador::instancia();
}

char* ServidorCliente::recibirDeCliente(){
	char* data=new char[MAXBYTESRECIBIDOS];
	memset((void*)data,'\0',MAXBYTESRECIBIDOS);
	bool seguir=true;
	ofstream* archivoResultado = new ofstream("recibidoDeCliente", ios::out);
	socklen_t leng=sizeof(char[MAXBYTESRECIBIDOS]);
	ssize_t valorRecive;
	while(seguir){
		valorRecive=recv(cliente->valorAcept,data,leng,0);
		if(valorRecive==0){
			delete data;
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
				delete data;
				data=new char[MAXBYTESRECIBIDOS];
				memset((void*)data,'\0',MAXBYTESRECIBIDOS);
			}
		}
	}
	delete data;
	archivoResultado->close();
	delete archivoResultado;
	string recibido;
	string *recibidoAux=new string;
	ifstream* archivo=new ifstream("recibidoDeCliente");
	while(!archivo->eof()){
		std::getline(*archivo,*recibidoAux);
		recibido+=*recibidoAux;
		recibido+="\n";
	}
	char* dataAux=new char[recibido.size()];
	memset(dataAux,'\0',recibido.size());
	for(int i=0;i<recibido.size();i++) dataAux[i]=recibido[i];
	archivo->close();
	return dataAux;
}

int ServidorCliente::enviarACliente(char* data){
	ostringstream sstream;
	sstream << data;
	string paraVerCuantoPesa = sstream.str();
    unsigned int valorSend;
    valorSend = send(cliente->valorAcept, data, paraVerCuantoPesa.size(), 0);
    if (valorSend == -1) {cout<<"Mal enviado a cliente nº: "<<cliente->valorAcept<<endl; }
	delete data;
	char* data2=new char[3];
	memset((void*)data2,'\0',3);
	data2[0]='e';
	data2[1]='o';
	data2[2]='f';
	valorSend=send(cliente->valorAcept,data2,3,0);
	delete data2;
	return valorSend;
}

void ServidorCliente::interactuarConCliente(){
	bool seguir=true;
	int paraVerSiCortoComunicacion=0;
	char* xml;
	while(seguir){
		xml=this->recibirDeCliente();
		seguir=((xml)!=" ");
		if(seguir){
			char* data;
			data=this->procesador->getRespuesta(xml);
			paraVerSiCortoComunicacion=this->enviarACliente(data);
			//la corroboracion es para ver si devuelve 0 es porq se desconecto el cliente
			seguir=(paraVerSiCortoComunicacion!=0);
		}
	}
}
ServidorCliente::~ServidorCliente() {
	delete this->procesador;
}
