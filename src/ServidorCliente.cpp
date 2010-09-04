#include "ServidorCliente.h"

ServidorCliente::ServidorCliente(paraThreadsRecibidos* cliente) {
	this->cliente=cliente;
}

int ServidorCliente::recibirDeCliente(){
	char data[MAXBYTES];
	socklen_t leng=sizeof(data);
	ssize_t valorRecive=recv(cliente->valorAcept,&data,leng,0);
	cout<<valorRecive<<endl;
	if(valorRecive==-1){
		cout<<"Mal recibido"<<endl;
	}else{
		data[valorRecive]='\0';
		cout<<data<<endl;
	}
	return valorRecive;
}

int ServidorCliente::enviarACliente(){
	char data[MAXBYTES]="A ver si llega";
	socklen_t leng=sizeof(data);
	int valorSend=send(cliente->valorAcept,&data,leng,0);
	if(valorSend==-1){
		cout<<"Mal enviado"<<endl;
	}else{
		cout<<"Se envio info"<<endl;
	}
	return valorSend;
}

ServidorCliente::~ServidorCliente() {
	// TODO Auto-generated destructor stub
}
