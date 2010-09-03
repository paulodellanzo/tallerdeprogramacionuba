#include "Servidor.h"
int main(){
	Servidor* servidor=new Servidor();
	servidor->escuchar();
	servidor->aceptar();
	servidor->recibir();
	servidor->~Servidor();
	return 0;
}
