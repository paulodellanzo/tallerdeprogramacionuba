#include "U.h"

U::U() {
	// TODO Auto-generated constructor stub

}

list<string>* U::realizarOpearacion(list<char*>* operandos){
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	string usuario;
	string pass;
	list<string>* respuesta = new list<string>();
		list<string>::iterator it=respuesta->begin();

	while(operandos->size()>0){
			if(strcmp(operandos->front(),"usuario")==0){
				operandos->pop_front();
				usuario=operandos->front();
				cout<<"usuario " + usuario +"\n";
				operandos->pop_front();
			}if(strcmp(operandos->front(),"password")==0){
				operandos->pop_front();
				pass=operandos->front();
				cout<<"pass " + pass+"\n";
				operandos->pop_front();

			}else{
				it=respuesta->begin();
				it=respuesta->insert(it,"Error");
				it++;
				it=respuesta->insert(it,"V");
				it++;
				it=respuesta->insert(it,"Falta ingresar usuario o password");
				return respuesta;
			}
		}
	bool usuValido;
	conn = Conexion::crearConexion();

	string query = "select usuario from usuarios where usuario='"+usuario+"' and password='"+pass+"'";
	const char* q = query.c_str();
	res = Conexion::ejecutarQuery(conn, query.c_str());

	double valido=0;
	 if ((row = mysql_fetch_row(res)) !=NULL){
		 cout<<row[0];
		 usuValido = true;
		 valido=0;
	 }else{
		 usuValido=false;
		 valido =1;
	 }

	if(!usuValido){
		it=respuesta->begin();
		it=respuesta->insert(it,"Error");
		it++;
		it=respuesta->insert(it,"V");
		it++;
		it=respuesta->insert(it,"Usuario invalido");
		return respuesta;
	}
//	ostringstream sstream;
//		sstream << valido;
//		string validoString = sstream.str();
//	it=respuesta->begin();
//	respuesta->insert(it,"Correcto");
//	it++;
//	it = respuesta->insert(it, "usuario");
//	it++;
//	it = respuesta->insert(it, validoString);

	respuesta->push_front("Correcto");
	return respuesta;

}



U::~U() {
	// TODO Auto-generated destructor stub
}
