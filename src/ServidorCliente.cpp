#include "ServidorCliente.h"

ServidorCliente::ServidorCliente(paraThreadsRecibidos* cliente) {
	this->cliente=cliente;
	this->procesador=new Procesador();
}

char* ServidorCliente::recibirDeCliente(){
	char* data=new char[MAXBYTES];
	socklen_t leng=sizeof(char[MAXBYTES]);
	ssize_t valorRecive=recv(cliente->valorAcept,data,leng,0);
	if((valorRecive!=-1)and(valorRecive!=0)){
		data[valorRecive]='\0';
		return data;
	}
	data=" ";
	return data;
}

int ServidorCliente::enviarACliente(const char* data){
	socklen_t leng=sizeof(char[MAXBYTES]);
	int valorSend=send(cliente->valorAcept,data,leng,0);
	return valorSend;
}

void ServidorCliente::interactuarConCliente(){
	bool seguir=true;
	int paraVerSiCortoComunicacion;
	char* xml;
	while(seguir){
		xml=this->recibirDeCliente();
		seguir=((xml)!=" ");
		if(seguir){
			const char* data;
			data=this->procesador->getRespuesta(xml);
			paraVerSiCortoComunicacion=this->enviarACliente(data);
			//la corroboracion es para ver si devuelve 0 es porq se desconecto el cliente
			seguir=(paraVerSiCortoComunicacion!=0);
		}
	}
}
ServidorCliente::~ServidorCliente() {
	// TODO Auto-generated destructor stub
}
