#include "Poker.h"

float Poker::esEscaleraReal(list<Carta>* cartas){
	list<Carta>::iterator it=cartas->begin();

	for(int i=0;i<4;i++){
		char palo1[255];
		char palo2[255];
		strcpy(palo1,it->getPalo().c_str());
		it++;
		strcpy(palo2,it->getPalo().c_str());
		if (strcmp(palo1,palo2)!=0)
			return 0;
	}

	it=cartas->begin();
	if(!strcmp(it->getNumero().c_str(),"1") && !strcmp((++it)->getNumero().c_str(),"10") &&
	!strcmp((++it)->getNumero().c_str(),"11") && !strcmp((++it)->getNumero().c_str(),"12")
	&& !strcmp((++it)->getNumero().c_str(),"13")){
		return 10;
	}
	else
		return 0;
}

float Poker::esEscaleraDeColor(list<Carta>* cartas){
	list<Carta>::iterator it=cartas->begin();

	for(int i=0;i<4;i++){
		char palo1[255];
		char palo2[255];
		strcpy(palo1,it->getPalo().c_str());
		it++;
		strcpy(palo2,it->getPalo().c_str());
		if (strcmp(palo1,palo2)!=0)
			return 0;
	}

	it=cartas->begin();
	if(atoi(it->getNumero().c_str())==atoi((++it)->getNumero().c_str())-1 &&
	atoi(it->getNumero().c_str())==atoi((++it)->getNumero().c_str())-1 &&
	atoi(it->getNumero().c_str())==atoi((++it)->getNumero().c_str())-1 &&
	atoi(it->getNumero().c_str())==atoi((++it)->getNumero().c_str())-1){
		return 9;
	}
	else
		return 0;
}

float Poker::esPoker(list<Carta>* cartas){
	list<Carta>::iterator it=cartas->begin();
	char numero[5];
	char numero2[5];
	char numero3[5];
	char numero4[5];

	strcpy(numero,it->getNumero().c_str());
	it++;
	strcpy(numero2,it->getNumero().c_str());
	it++;
	if(strcmp(numero,numero2)==0){
		strcpy(numero2,it->getNumero().c_str());
		it++;
		strcpy(numero3,it->getNumero().c_str());
		it++;
		if (strcmp(numero,numero2)==0 and strcmp(numero,numero3)==0){
			return 8;
		}
		else{
			return 0;
		}
	}
	strcpy(numero,it->getNumero().c_str());
	it++;
	strcpy(numero3,it->getNumero().c_str());
	it++;
	strcpy(numero4,it->getNumero().c_str());
	if(strcmp(numero2,numero)==0 and strcmp(numero2,numero3)==0 and strcmp(numero2,numero4)==0 ){
		return 8;
	}
	return 0;
}

float Poker::esFull(list<Carta>* cartas){
	list<Carta>::iterator it=cartas->begin();
	char numero[5];
	char numero2[5];
	char numero3[5];
	char numero4[5];
	strcpy(numero,it->getNumero().c_str());
	it++;
	strcpy(numero2,it->getNumero().c_str());
	it++;
	if(strcmp(numero,numero2)!=0){
		return 0;
	}
	strcpy(numero2,it->getNumero().c_str());
	it++;

	if(strcmp(numero,numero2)==0){
		strcpy(numero2,it->getNumero().c_str());
		it++;
		strcpy(numero3,it->getNumero().c_str());
		if(strcmp(numero2,numero3)==0){
			return 7;
		}
		return 0;
	}
	strcpy(numero3,it->getNumero().c_str());
	it++;
	strcpy(numero4,it->getNumero().c_str());

	if(strcmp(numero2,numero3)==0 and strcmp(numero3,numero4)==0){
		return 7;
	}
	return 0;
}

float Poker::esColor(list<Carta>* cartas){
	list<Carta>::iterator it=cartas->begin();

	for(int i=0;i<4;i++){
		char palo1[255];
		char palo2[255];
		strcpy(palo1,it->getPalo().c_str());
		it++;
		strcpy(palo2,it->getPalo().c_str());
		if (strcmp(palo1,palo2)!=0)
			return 0;
	}
	return 6;
}

float Poker::esEscalera(list<Carta>* cartas){
	list<Carta>::iterator it=cartas->begin();

	it=cartas->begin();
	if(!strcmp(it->getNumero().c_str(),"1") && !strcmp((++it)->getNumero().c_str(),"10") &&
	!strcmp((++it)->getNumero().c_str(),"11") && !strcmp((++it)->getNumero().c_str(),"12")
	&& !strcmp((++it)->getNumero().c_str(),"13")){
		return 5;
	}

	it=cartas->begin();
	if(atoi(it->getNumero().c_str())==atoi((++it)->getNumero().c_str())-1 &&
	atoi(it->getNumero().c_str())==atoi((++it)->getNumero().c_str())-1 &&
	atoi(it->getNumero().c_str())==atoi((++it)->getNumero().c_str())-1 &&
	atoi(it->getNumero().c_str())==atoi((++it)->getNumero().c_str())-1){
		return 5;
	}
	else
		return 0;
}

float Poker::esTrio(list<Carta>* cartas){
	char numero[5];
	char numero2[5];
	char numero3[5];
	char numero4[5];
	char numero5[5];
	list<Carta>::iterator it=cartas->begin();
	strcpy(numero,it->getNumero().c_str());
	it++;
	strcpy(numero2,it->getNumero().c_str());
	it++;
	if(strcmp(numero,numero2)==0){
		strcpy(numero3,it->getNumero().c_str());
		if(strcmp(numero2,numero3)==0){
			return 4;
		}
		return 0;
	}
	strcpy(numero3,it->getNumero().c_str());
	it++;
	if(strcmp(numero2,numero3)==0){
		strcpy(numero4,it->getNumero().c_str());
		if(strcmp(numero3,numero4)==0){
			return 4;
		}
		return 0;
	}
	strcpy(numero4,it->getNumero().c_str());
	it ++;
	strcpy(numero5,it->getNumero().c_str());
	if(strcmp(numero3,numero4)==0 and strcmp(numero4,numero5)==0)
	{
		return 4;
	}
	return 0;
}

float Poker::esDoblePar(list<Carta>* cartas){
	list<Carta>::iterator it=cartas->begin();
	char numero[5];
	char numero2[5];
	char numero3[5];
	char numero4[5];
	char numero5[5];
	strcpy(numero,it->getNumero().c_str());
	it ++;
	strcpy(numero2,it->getNumero().c_str());
	it ++;

	if(strcmp(numero,numero2)==0){
		strcpy(numero3,it->getNumero().c_str());
		it ++;
		strcpy(numero4,it->getNumero().c_str());
		it ++;
		if(strcmp(numero3,numero4)==0){
			return 3;
		}
		strcpy(numero5,it->getNumero().c_str());
		if(strcmp(numero4,numero5)==0){
			return 3;
		}
		return 0;
	}
	strcpy(numero3,it->getNumero().c_str());
	it ++;
	if(strcmp(numero2,numero3)!=0){
		return 0;
	}
	strcpy(numero4,it->getNumero().c_str());
	it ++;
	strcpy(numero5,it->getNumero().c_str());
	if(strcmp(numero4,numero5)==0){
		return 3;
	}
	return 0;
}

float Poker::esPar(list<Carta>* cartas){
	list<Carta>::iterator it=cartas->begin();
	char numero[5];
	char numero2[5];
	float resultadoParcial=0;
	strcpy(numero,it->getNumero().c_str());
	it ++;
	strcpy(numero2,it->getNumero().c_str());
	it ++;
	if(strcmp(numero,numero2)==0){
		if(strcmp(numero,"1")==0){
			strcpy(numero,"14");
		}
		resultadoParcial=resultadoParcial+atof(numero)*pow(15,8);
		for(int k=5;k<=7;k++){
			strcpy(numero2,it->getNumero().c_str());
			it++;
			resultadoParcial=resultadoParcial+atof(numero2)*pow(15,k);
		}
		return resultadoParcial;
	}
	strcpy(numero,it->getNumero().c_str());
	it ++;
	if(strcmp(numero,numero2)==0){
		it=cartas->begin();
		strcpy(numero,it->getNumero().c_str());
		it++;
		if(strcmp(numero,"1")==0){
			resultadoParcial=resultadoParcial+14*pow(15,7);
			resultadoParcial=resultadoParcial+atof(numero2)*pow(15,8);
			it++;
			it++;
			strcpy(numero,it->getNumero().c_str());
			resultadoParcial=resultadoParcial+atof(numero)*pow(15,5);
			it++;
			strcpy(numero,it->getNumero().c_str());
			resultadoParcial=resultadoParcial+atof(numero)*pow(15,6);
		}
		else{
			resultadoParcial=resultadoParcial+atof(numero)*pow(15,5);
			resultadoParcial=resultadoParcial+atof(numero2)*pow(15,8);
			it++;
			it++;
			strcpy(numero,it->getNumero().c_str());
			resultadoParcial=resultadoParcial+atof(numero)*pow(15,6);
			it++;
			strcpy(numero,it->getNumero().c_str());
			resultadoParcial=resultadoParcial+atof(numero)*pow(15,7);
		}

		return resultadoParcial;
	}
	strcpy(numero2,it->getNumero().c_str());
	it ++;
	if(strcmp(numero,numero2)==0){
		it=cartas->begin();
		strcpy(numero,it->getNumero().c_str());
		it++;
		if(strcmp(numero,"1")==0){
			resultadoParcial=resultadoParcial+14*pow(15,7);
			strcpy(numero,it->getNumero().c_str());
			resultadoParcial=resultadoParcial+atof(numero)*pow(15,5);
			it++;
			it++;
			strcpy(numero,it->getNumero().c_str());
			resultadoParcial=resultadoParcial+atof(numero)*pow(15,8);
			it++;
			strcpy(numero,it->getNumero().c_str());
			resultadoParcial=resultadoParcial+atof(numero)*pow(15,6);

		}
		else{
			resultadoParcial=resultadoParcial+atof(numero)*pow(15,5);
			it++;
			strcpy(numero,it->getNumero().c_str());
			resultadoParcial=resultadoParcial+atof(numero)*pow(15,6);
			it++;
			it++;
			strcpy(numero,it->getNumero().c_str());
			resultadoParcial=resultadoParcial+atof(numero)*pow(15,8);
			it++;
			strcpy(numero,it->getNumero().c_str());
			resultadoParcial=resultadoParcial+atof(numero)*pow(15,7);
		}
		return resultadoParcial;
	}
	strcpy(numero,it->getNumero().c_str());
	if(strcmp(numero,numero2)==0){
		it=cartas->begin();
		strcpy(numero,it->getNumero().c_str());
		it++;
		if(strcmp(numero,"1")==0){
			resultadoParcial=resultadoParcial+14*pow(15,7);
			strcpy(numero,it->getNumero().c_str());
			it++;
			resultadoParcial=resultadoParcial+atof(numero)*pow(15,5);
			strcpy(numero,it->getNumero().c_str());
			it++;
			resultadoParcial=resultadoParcial+atof(numero)*pow(15,6);
			strcpy(numero,it->getNumero().c_str());
			resultadoParcial=resultadoParcial+atof(numero)*pow(15,8);
		}
		else{
			resultadoParcial=resultadoParcial+atof(numero)*pow(15,5);
			strcpy(numero,it->getNumero().c_str());
			it++;
			resultadoParcial=resultadoParcial+atof(numero)*pow(15,6);
			strcpy(numero,it->getNumero().c_str());
			it++;
			resultadoParcial=resultadoParcial+atof(numero)*pow(15,7);
			strcpy(numero,it->getNumero().c_str());
			resultadoParcial=resultadoParcial+atof(numero)*pow(15,8);
		}
		return resultadoParcial;
	}
	return 0;
}

float Poker::mayorCarta(list<Carta>* cartas){
	float resultadoParcial=0;
	float auxiliar[4];
	char numeroAux[5];
	list<Carta>::iterator it=cartas->begin();
	strcpy(numeroAux,it->getNumero().c_str());
	if(strcmp(numeroAux,"1")==0){
		auxiliar[4]=14;
		for(int j=0;j<4;j++){
			it++;
			strcpy(numeroAux,it->getNumero().c_str());
			auxiliar[j]=atof(numeroAux);
		}
	}
	else{
		for(int j=0;j<5;j++){
			strcpy(numeroAux,it->getNumero().c_str());
			auxiliar[j]=atof(numeroAux);
			it++;
		}
	}
	for(int j=0;j<5;j++){
		resultadoParcial=resultadoParcial+auxiliar[j]*pow(15,j);
	}

	return resultadoParcial;
}

float Poker::getPuntajeMano(list<Carta>* cartas){

	float puntajeParcial;
	puntajeParcial=esEscaleraReal(cartas);
	if(puntajeParcial!=0)
		return puntajeParcial;
	puntajeParcial= esEscaleraDeColor(cartas);
	if(puntajeParcial!=0)
		return puntajeParcial;
	puntajeParcial= esPoker(cartas);
	if(puntajeParcial!=0)
		return puntajeParcial;
	puntajeParcial= esFull(cartas);
	if(puntajeParcial!=0)
		return puntajeParcial;
	puntajeParcial= esColor(cartas);
	if(puntajeParcial!=0)
		return puntajeParcial;
	puntajeParcial= esEscalera(cartas);
	if(puntajeParcial!=0)
		return puntajeParcial;
	puntajeParcial= esTrio(cartas);
	if(puntajeParcial!=0)
		return puntajeParcial;
	puntajeParcial= esDoblePar(cartas);
	if(puntajeParcial!=0)
		return puntajeParcial;
	puntajeParcial= esPar(cartas);
	if(puntajeParcial!=0)
		return puntajeParcial;
	return mayorCarta(cartas);
}

bool compararCartas(Carta carta1,Carta carta2){
	if (atoi(carta1.getNumero().c_str())<atoi(carta2.getNumero().c_str()))
		return true;
	else
		return false;
}

Poker::Poker(list<Carta>* cartas) {
	cartas->sort(compararCartas);
	this->puntaje=getPuntajeMano(cartas);

}

list<Carta>* Poker::getMejoresCartas(){
	return mejoresCartas;
}

float Poker::getPuntaje(){
	return puntaje;
}

Poker::~Poker() {

}
