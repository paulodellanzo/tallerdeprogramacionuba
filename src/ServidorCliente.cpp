#include "ServidorCliente.h"

ServidorCliente::ServidorCliente(paraThreadsRecibidos* cliente) {
	this->cliente=cliente;
}

void ServidorCliente::recibirDeCliente(){
	char data[MAXBYTES];
	socklen_t leng=sizeof(data);
	ssize_t valorRecive=recv(cliente->valorAcept,&data,leng,0);
	if(valorRecive==-1){
		cout<<"Mal recibido"<<endl;
	}else{
		data[valorRecive]='\0';
		cout<<data<<endl;
	}
}

void ServidorCliente::enviarACliente(){
	char data[MAXBYTES]="A ver si llega";
	socklen_t leng=sizeof(data);
	int valorSend=send(cliente->valorAcept,&data,leng,0);
	if(valorSend==-1){
		cout<<"Mal enviado"<<endl;
	}else{
		cout<<"Se envio info"<<endl;
	}
}

ServidorCliente::~ServidorCliente() {
	// TODO Auto-generated destructor stub
}
