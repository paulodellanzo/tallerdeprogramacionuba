#ifndef SERVIDORCLIENTE_H_
#define SERVIDORCLIENTE_H_

using namespace std;
#include <string>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>
#include "Procesador.h"

struct paraThreadsRecibidos{
	sockaddr_in clientAdress;
	int valorAcept,descriptorSocket;
};

class ServidorCliente{
private:
	paraThreadsRecibidos* cliente;
	Procesador* procesador;

public:
	ServidorCliente(paraThreadsRecibidos* cliente);
	void interactuarConCliente();
	char* recibirDeCliente();
	int enviarACliente(const char* data);
	virtual ~ServidorCliente();
};

#endif /* SERVIDORCLIENTE_H_ */
