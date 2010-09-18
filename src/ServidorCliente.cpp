#include "ServidorCliente.h"
#include <sstream>
#include <fstream>
ServidorCliente::ServidorCliente(paraThreadsRecibidos* cliente) {
	this->cliente=cliente;
	this->procesador=new Procesador();
}

char* ServidorCliente::recibirDeCliente(){
	char* data=new char[MAXBYTESRECIBIDOS];
	bool seguir=true;
	ofstream* archivoResultado = new ofstream("recibidoDeCliente", ios::app);
	socklen_t leng=sizeof(char[MAXBYTESRECIBIDOS]);
	ssize_t valorRecive;
	while(seguir){
		valorRecive=recv(cliente->valorAcept,data,leng,0);
		if(valorRecive==0){
			delete data;
			return " ";
		}
		if(valorRecive==-1){
			cout<<"Mal recibido"<<endl;
		}else{
			//corroboro que los ultimos tres formen eof
			if((data[valorRecive-1]=='f')and(data[valorRecive-2]=='o')and(data[valorRecive-3]=='e')){
				seguir=false;
				ostringstream sstream;
				sstream << data;
				string lineaActual = sstream.str();
//				Para sacar el eof del archivo
				string::iterator it=lineaActual.end();
				it--;
				it=lineaActual.erase(it);
				it--;
				it=lineaActual.erase(it);
				it--;
				it=lineaActual.erase(it);
				*archivoResultado<<lineaActual;
//				 memset((void*)data,'-',valorRecive);
			}else{
				ostringstream sstream;
				sstream << data;
				string lineaActual = sstream.str();
				*archivoResultado<<lineaActual;
//				memset((void*)data,'-',valorRecive);
				delete data;
				data=new char[MAXBYTESRECIBIDOS];
			}
		}
	}
	delete data;
	archivoResultado->close();
	delete archivoResultado;
	return "";
}

int ServidorCliente::enviarACliente(char* data){
	ostringstream sstream;
	sstream << data;
	string paraVerCuantoPesa = sstream.str();
    unsigned int valorSend;
//	memset( (void*)data,'-',paraVerCuantoPesa.size());
    valorSend = send(cliente->valorAcept, data, paraVerCuantoPesa.size(), 0);
    if (valorSend == -1) {cout<<"Mal enviado a cliente nº: "<<cliente->valorAcept<<endl; }
//	memset( (void*)data,'-',paraVerCuantoPesa.size());
	delete data;
	char* data2=new char[3];
	data2[0]='e';
	data2[1]='o';
	data2[2]='f';
	valorSend=send(cliente->valorAcept,data2,3,0);
//	memset( (void*)data2,'-',3);
	delete data2;
	return valorSend;
}

void ServidorCliente::interactuarConCliente(){
	bool seguir=true;
	int paraVerSiCortoComunicacion=0;
	char* xml;
	while(seguir){
		xml=this->recibirDeCliente();
		seguir=((xml)!=" ");
		if(seguir){
			string aux="<pedido>\n"
						"	<operacion id=\"S\"/>\n"
						"		<parametros>\n"
						"			<parametro nombre=\"sum\">23\n"
						"			</parametro>\n"
						"			<parametro nombre=\"sum\">23\n"
						"			</parametro>\n"
						"			<parametro nombre=\"sum\">23\n"
						"			</parametro>\n"
						"	</parametros>\n"
						"</pedido>\n";
			char* data=new char[aux.size()];
			for(int i=0;i<aux.size();i++){data[i]=aux[i];}
//			data=this->procesador->getRespuesta(xml);
			paraVerSiCortoComunicacion=this->enviarACliente(data);
			//la corroboracion es para ver si devuelve 0 es porq se desconecto el cliente
			seguir=(paraVerSiCortoComunicacion!=0);
		}
	}
}
ServidorCliente::~ServidorCliente() {
	delete this->procesador;
}
