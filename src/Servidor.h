#ifndef SERVIDOR_H_
#define SERVIDOR_H_

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


class Servidor{
private:
	int descriptorSocket,valorAccept;
	sockaddr_in estructurDeDirecciones,clienteAdress;
public:
	Servidor();
	void escuchar();
	void aceptar();
	void recibir();
	virtual ~Servidor();
};

#endif /* SERVIDOR_H_ */
