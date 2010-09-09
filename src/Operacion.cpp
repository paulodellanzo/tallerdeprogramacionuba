#include "Operacion.h"

Operacion::Operacion() {
	// TODO Auto-generated constructor stub

}

bool Operacion::esUnNumero(char* numero){
	//Corroborar que no se un tipo 4.2.3
	bool aparecioPunto=false;
	for(int i=0;i<TAMANOVECTOROPERANDOS;i++){
		if((numero[i]!='-')or(numero[0]>'9')){
			if((numero[0]!='.')){
				return false;
			}else{
				if(aparecioPunto){
					return false;
				}else{
					aparecioPunto=true;
				}

			}
		}

	}
	return true;
}

list<string>* Operacion::realizarOpearacion(list<char*>* operandos){
	return new list<string>();
}

Operacion::~Operacion() {
	// TODO Auto-generated destructor stub
}
