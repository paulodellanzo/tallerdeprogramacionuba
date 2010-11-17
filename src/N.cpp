#include "N.h"

N::N() {
	// TODO Auto-generated constructor stub

}

list<string>* N::realizarOpearacion(list<char*>* operandos){
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	string monto;
	string usuario;
	list<string>* respuesta = new list<string>();
	list<string>::iterator it=respuesta->begin();
	bool haySaldo=false;

	while(operandos->size()>0){
		if(strcmp(operandos->front(),"usuario")==0){
			operandos->pop_front();
			usuario=operandos->front();
			cout<<"usuario " + usuario +"\n";
			operandos->pop_front();
		}if(strcmp(operandos->front(),"monto")==0){
			operandos->pop_front();
			monto=operandos->front();
			cout<<"monto " + monto +"\n";
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
	Conexion* conexion = Conexion::instancia();

	string query = "select fechaUltimaCarga,CURRENT_DATE from usuarios where usuario='"+usuario+"'";

	res = conexion->ejecutarQuery(query.c_str());
	row = mysql_fetch_row(res);
	if(strcmp(row[0],row[1])==0){
		haySaldo=true;
	}
	conexion->liberarConexion(res);

	if(haySaldo){
		query="update usuarios set cargaUltimoDia=cargaUltimoDia+"+monto+", plata=plata+"+monto+" where usuario='"+usuario+"'";
	} else {
		query="update usuarios set fechaUltimaCarga=CURRENT_DATE, cargaUltimoDia="+monto+", plata=plata+"+monto+" where usuario='"+usuario+"'";
	}
	res = conexion->ejecutarQuery(query.c_str());
	conexion->liberarConexion(res);
	respuesta->push_back("Correcto");
	respuesta->push_back("monto");
	respuesta->push_back(monto);
	return respuesta;
}

N::~N() {
	// TODO Auto-generated destructor stub
}
