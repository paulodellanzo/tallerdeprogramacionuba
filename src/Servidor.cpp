#include "Servidor.h"

Servidor::Servidor() {
	//creamos el socket
	this->descriptorSocket=socket(AF_INET,SOCK_STREAM,0);
	if(this->descriptorSocket==-1){
		cout<<"Mal creado socket"<<endl;
	}
	else{
		cout<<"Socket bien creado"<<endl;
	}

	//para llamar al bind()
	this->estructurDeDirecciones.sin_family=AF_INET;//para lo de family QUE SEA LOCAL
	this->estructurDeDirecciones.sin_port=htons(PORT);
	this->estructurDeDirecciones.sin_addr.s_addr=htonl(INADDR_ANY);//INADDR_ANY coloca nuestra direccion IP automaticamente

	for(int i=0;i<8;i++){
			this->estructurDeDirecciones.sin_zero[i]=0;}

	socklen_t length=sizeof(sockaddr);

	int valorBind=bind(this->descriptorSocket,(struct sockaddr*)&(this->estructurDeDirecciones),length);
	if(valorBind==-1){
		cout<<"Fallo en Bind"<<endl;
	}else{
		cout<<"Bind correcto"<<endl;
	}

}
void Servidor::escuchar(){
	//para el listen
	int valorListen=listen(descriptorSocket,10);

	if(valorListen==-1){
		cout<<"Mal listen"<<endl;
	}else{
		cout<<"Bien listen"<<endl;
	}

}

void Servidor::aceptar(){
	//Para el accept
	socklen_t length=sizeof(sockaddr);
	valorAccept=accept(descriptorSocket,(struct sockaddr*)&clienteAdress,&length);
	if(valorAccept==-1){
		cout<<"Mal accpet"<<endl;
	}else{
		cout<<"Bien accept"<<endl;
	}
}

void Servidor::recibir(){
	char data[MAXBYTES];
	socklen_t leng=sizeof(data);
	socklen_t leng2=sizeof(sockaddr);
	ssize_t valorRecive=recvfrom(valorAccept,&data,leng,0,(struct sockaddr*)&clienteAdress,&leng2);
	if(valorRecive==-1){
		cout<<"Mal recibido"<<endl;
	}else{
		data[valorRecive]='\0';
		cout<<data<<endl;
	}
}
Servidor::~Servidor() {
	close(descriptorSocket);
}
