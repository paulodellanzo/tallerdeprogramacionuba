#ifndef SERVIDOR_H_
#define SERVIDOR_H_

using namespace std;
using namespace std;
#include <string>
#include <ctype.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <string.h>
#include <sstream>
#include <string>
#include <fstream>
#include <ctype.h>
#include <list>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <pthread.h>
#include "ServidorCliente.h"
#include "Procesador.h"


class Servidor{
private:
	int descriptorSocket,valorAccept;
	sockaddr_in estructurDeDirecciones,clienteAdress;
	pthread_mutex_t mutex;
public:
	Servidor();
	void escuchar();
	void aceptar();
	virtual ~Servidor();
};

#endif /* SERVIDOR_H_ */
