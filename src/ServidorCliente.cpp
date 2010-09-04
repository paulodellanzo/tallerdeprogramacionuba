#include "ServidorCliente.h"

ServidorCliente::ServidorCliente(paraThreadsRecibidos* cliente) {
	//creamos el socket
	this->descriptorSocket=socket(AF_INET,SOCK_STREAM,0);
	if(this->descriptorSocket==-1){
		cout<<"Mal creado socket"<<endl;
	}
	else{
		cout<<"Socket bien creado"<<endl;
	}
	this->cliente=cliente;

}

void ServidorCliente::interactuarConCliente(){
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

ServidorCliente::~ServidorCliente() {
	// TODO Auto-generated destructor stub
}
