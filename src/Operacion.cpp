#include "Operacion.h"

Operacion::Operacion() {
	// TODO Auto-generated constructor stub

}

list<string>* Operacion::realizarOpearacion(list<char*>* operandos){
	return NULL;
}

bool Operacion::esUnNumero(char* numero){
	ostringstream sstream;
	sstream << numero;
	string numeroAux = sstream.str();
	bool esUnNumero=true;
	bool aparecioPunto=false;
	int i=0;
	while((esUnNumero)and(i<numeroAux.size())){
		esUnNumero=(((numero[i]<='9')and(numero[i]>='0'))or((numero[i]=='.')and(!aparecioPunto)));
		if(numero[i]=='.') aparecioPunto=true;
		i++;
		}
	return esUnNumero;
}

Operacion::~Operacion() {
	// TODO Auto-generated destructor stub
}
