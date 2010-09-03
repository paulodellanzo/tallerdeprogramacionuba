#include "Servidor.h"
int main(){
	Servidor* servidor=new Servidor();
	servidor->escuchar();
	servidor->aceptar();
	servidor->~Servidor();
	return 0;
}
