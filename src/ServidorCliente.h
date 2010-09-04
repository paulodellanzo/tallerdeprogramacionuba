#ifndef SERVIDORCLIENTE_H_
#define SERVIDORCLIENTE_H_

#define PORT 5434
#define MAXBYTES 3000000

using namespace std;
#include <string>
#include "ParserServidor.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>

struct paraThreadsRecibidos{
	sockaddr_in clientAdress;
	int valorAcept,descriptorSocket;
};

class ServidorCliente{
private:
	ParserServidor* parser;
	int descriptorSocket;
	paraThreadsRecibidos* cliente;
public:
	ServidorCliente(paraThreadsRecibidos* cliente);
	void recibirDeCliente();
	void enviarACliente();
	virtual ~ServidorCliente();
};

#endif /* SERVIDORCLIENTE_H_ */
