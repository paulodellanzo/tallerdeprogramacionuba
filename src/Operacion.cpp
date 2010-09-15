#include "Operacion.h"

Operacion::Operacion() {
	// TODO Auto-generated constructor stub

}

bool Operacion::esUnNumero(char* numero){
	//Corroborar que no se un tipo 4.2.3
//	bool aparecioPunto=false;
//	for(int i=0;i<TAMANOVECTOROPERANDOS;i++){
//		if((numero[i]!='-')or(numero[0]>'9')){
//			if((numero[0]!='.')){
//				return false;
//			}else{
//				if(aparecioPunto){
//					return false;
//				}else{
//					aparecioPunto=true;
//				}
//
//			}
//		}
//
//	}
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

list<string>* Operacion::realizarOpearacion(list<char*>* operandos){
	return new list<string>();
}

Operacion::~Operacion() {
	// TODO Auto-generated destructor stub
}
