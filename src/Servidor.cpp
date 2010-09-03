#include "Servidor.h"
#include <pthread.h>

void* recibir(void* structThreads){
	paraThreadsRecibidos* threads=(paraThreadsRecibidos*)structThreads;
	char data[MAXBYTES];
	socklen_t leng=sizeof(data);
	socklen_t leng2=sizeof(sockaddr);
	ssize_t valorRecive=recvfrom(threads->valorAcept,&data,leng,0,(struct sockaddr*)&(threads->clientAdress),&leng2);
	if(valorRecive==-1){
		cout<<"Mal recibido"<<endl;
	}else{
		data[valorRecive]='\0';
		cout<<data<<endl;
	}
	cout<<"fin del thread"<<endl;
	void* arg;
	pthread_exit(arg);
	return arg;
}

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
	while(true){
		socklen_t length=sizeof(sockaddr);
		valorAccept=accept(descriptorSocket,(struct sockaddr*)&clienteAdress,&length);
		if(valorAccept==-1){
			cout<<"Mal accpet"<<endl;
		}else{
			cout<<"Bien accept"<<endl;
		}
		paraThreadsRecibidos threads;
		threads.clientAdress=clienteAdress;
		threads.valorAcept=valorAccept;
		pthread_t thread;
		int creado=pthread_create(&thread,NULL,recibir,(void*)&threads);
		if(creado==0) cout<<"bien creado"<<endl;
	}
}

//static void Servidor::recibi(paraThreadsRecibidos obj){
//	char data[MAXBYTES];
//	socklen_t leng=sizeof(data);
//	socklen_t leng2=sizeof(sockaddr);
//	ssize_t valorRecive=recvfrom(obj.valorAcept,&data,leng,0,(struct sockaddr*)&(obj.clientAdress),&leng2);
//	if(valorRecive==-1){
//		cout<<"Mal recibido"<<endl;
//	}else{
//		data[valorRecive]='\0';
//		cout<<data<<endl;
//	}
//}
Servidor::~Servidor() {
	close(descriptorSocket);}
