#include "Servidor.h"
void* cortarConexion(void* seguir){
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

int main(){
	void *seguir;
	Servidor* servidor=new Servidor();
	seguir=(void*)servidor;
	servidor->escuchar();
	pthread_t thread;
	int creado=pthread_create(&thread,NULL,cortarConexion,(void*)seguir);
	if(creado!=0) cout<<"mal creado el thread"<<endl;
	servidor->aceptar();
	servidor->~Servidor();
	return 0;
}
