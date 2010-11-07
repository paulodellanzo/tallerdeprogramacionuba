#include "R.h"

R::R() {
	// TODO Auto-generated constructor stub

}

list<string>* R::realizarOpearacion(list<char*>* operandos){
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
	bool usuarioExiste;
	conn = Conexion::crearConexion();

	string query = "select usuario from usuarios where usuario='"+usuario+"'";
	res = Conexion::ejecutarQuery(conn, query.c_str());
	 if ((row = mysql_fetch_row(res)) !=NULL){
		 usuarioExiste = true;
	 }else{
		 usuarioExiste=false;
	 }
	if(usuarioExiste){
		it=respuesta->begin();
		it=respuesta->insert(it,"Error");
		it++;
		it=respuesta->insert(it,"V");
		it++;
		it=respuesta->insert(it,"Ya existe el usuario");
		return respuesta;
	}
	query="insert into usuarios (usuario,password,plata) values ('"+usuario+"','"+pass+"',0)";
	res = Conexion::ejecutarQuery(conn, query.c_str());
	respuesta->push_back("Correcto");
	respuesta->push_back("Usuario");
	respuesta->push_back(usuario);
	return respuesta;
}

R::~R() {
	// TODO Auto-generated destructor stub
}
