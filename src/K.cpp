/*
 * K.cpp
 *
 */

#include "K.h"

K::K() {
	// TODO Auto-generated constructor stub

}

list<string>* K::realizarOpearacion(list<char*>* operandos){
	//MYSQL *conn;
	list<string>* respuesta ;

	if(strcmp(operandos->back(),"ranking")==0){
		string query = "select usuario, plata from usuarios order by plata desc";
		respuesta=getRespuestaEstadistica(query);

	}else if(strcmp(operandos->back(),"listadoRegistradoDia")==0){
		string query = "select usuario,fechaRegistro from usuarios where fechaRegistro= CURRENT_DATE";
		respuesta=getRespuestaEstadistica(query);

	}else if(strcmp(operandos->back(),"listadoConectadoDia")==0){
			string query = "select distinct(u.usuario),Date_format(fechaLogin,'%d/%m/%Y') from estadistica e,usuarios u where u.id=e.usuarioId and Date_format(fechaLogin,'%d/%m/%Y')=Date_format(now(),'%d/%m/%Y')";
			respuesta=getRespuestaEstadistica(query);

	}else if(strcmp(operandos->back(),"listadoRegistradoMes")==0){
		string query = "select usuario,fechaRegistro from usuarios where DATE_FORMAT(fechaRegistro,'%m/%Y')= DATE_FORMAT(now(),'%m/%Y')";
		respuesta=getRespuestaEstadistica(query);

	}else if(strcmp(operandos->back(),"listadoConectadoMes")==0){
				string query = "select distinct(u.usuario),Date_format(fechaLogin,'%d/%m/%Y') from estadistica e,usuarios u where u.id=e.usuarioId and Date_format(fechaLogin,'%m/%Y')=Date_format(now(),'%m/%Y')";
				respuesta=getRespuestaEstadistica(query);

	}else if(strcmp(operandos->back(),"listadoConectadoAnio")==0){
		string query = "select distinct(u.usuario),Date_format(fechaLogin,'%d/%m/%Y')  from estadistica e,usuarios u where u.id=e.usuarioId and Date_format(fechaLogin,'%Y')=Date_format(now(),'%Y')";
		respuesta=getRespuestaEstadistica(query);

	}else if(strcmp(operandos->back(),"listadoRegistradoAnio")==0){

		string query = "select usuario,fechaRegistro from usuarios where Date_format(fechaRegistro,'%Y')=Date_format(now(),'%Y')";
		respuesta=getRespuestaEstadistica(query);

	}else if(strcmp(operandos->back(),"evolucionUsuarioConectado")==0){
		string query = "SELECT DATE_FORMAT(fechaLogin,'%d/%m/%Y'), COUNT(DISTINCT(usuarioId)) FROM estadistica group by fechaLogin";
		respuesta=getRespuestaEstadistica(query);

	}else if(strcmp(operandos->back(),"evolucionUsuario")==0){
			string query = "SELECT fechaRegistro, COUNT(DISTINCT(id)) FROM usuarios group by fechaRegistro";
			respuesta=getRespuestaEstadistica(query);

	}else{
		respuesta = new list<string>();
		list<string>::iterator it=respuesta->begin();
		it=respuesta->begin();
				it=respuesta->insert(it,"Error");
				it++;
				it=respuesta->insert(it,"V");
				it++;
				it=respuesta->insert(it,"operacion invalida");
				return respuesta;
	}

	respuesta->push_front("Correcto");
	return respuesta;

}
list<string>* K::getRespuestaEstadistica(string query){
	MYSQL_RES *res;
	MYSQL_ROW row;

	Conexion* conexion = Conexion::instancia();

	list<string>* respuesta = new list<string>();
	list<string>::iterator it=respuesta->begin();

	res = conexion->ejecutarQuery(query.c_str());
			int size =(int) mysql_num_fields(res);
			while ((row = mysql_fetch_row(res)))
			{
			  for (int i = 0; i < size; i++) {
					 respuesta->push_back(row[i]);
				}
			 }
	conexion->liberarConexion(res);
			return respuesta;
}


K::~K() {
	// TODO Auto-generated destructor stub
}
