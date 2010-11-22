#include "Servidor.h"
void* cortarConexion(void* seguir){
	sleep(2);
	system("clear");
	string respuesta="";
	while((respuesta!="D")and(respuesta!="d")){
		cout<<"Para desconectar aprete D"<<endl;
		cin>>respuesta;
	}
	cout<<"Se desconectara el servidor"<<endl;
	sleep(1);
	exit(0);
}

int main(int argc,char* argv[]){
	char ip[255];
	int puerto;
	if(argc!=3){
		cout<<"Cantidad de parámetros incorrecta"<<endl;
		return 1;
	}
	strcpy(ip,argv[1]);
	puerto=atoi(argv[2]);

	void *seguir;
	Servidor* servidor=new Servidor(ip,puerto);
	seguir=(void*)servidor;
	servidor->escuchar();
	pthread_t thread;
	int creado=pthread_create(&thread,NULL,cortarConexion,(void*)seguir);
	if(creado!=0) cout<<"mal creado el thread"<<endl;
	servidor->aceptar();
	delete servidor;
	return 0;
}
