/*
 * K.cpp
 *
 */

#include "K.h"

K::K() {
	// TODO Auto-generated constructor stub

}

list<string>* K::realizarOpearacion(list<char*>* operandos, ofstream* archivo){
	//MYSQL *conn;
	list<string>* respuesta ;
	string titulo;
	this->archivoEstadistica=archivo;

	if(strcmp(operandos->back(),"ranking")==0){
		string query = "select usuario, plata from usuarios order by plata desc";
		respuesta=getRespuestaEstadistica(query);
		titulo="Ranking de usuarios";

	}else if(strcmp(operandos->back(),"listadoRegistradoDia")==0){
		string query = "select usuario,fechaRegistro from usuarios where fechaRegistro= CURRENT_DATE";
		respuesta=getRespuestaEstadistica(query);
		titulo="Listado de los usuarios registrados - Ultimo dia";
	}else if(strcmp(operandos->back(),"listadoConectadoDia")==0){
			string query = "select distinct(u.usuario),Date_format(fechaLogin,'%d/%m/%Y') from estadistica e,usuarios u where u.id=e.usuarioId and Date_format(fechaLogin,'%d/%m/%Y')=Date_format(now(),'%d/%m/%Y')";
			respuesta=getRespuestaEstadistica(query);
			titulo="Listado de los usuarios conectados - Ultimo dia";
	}else if(strcmp(operandos->back(),"listadoRegistradoMes")==0){
		string query = "select usuario,fechaRegistro from usuarios where DATE_FORMAT(fechaRegistro,'%m/%Y')= DATE_FORMAT(now(),'%m/%Y')";
		respuesta=getRespuestaEstadistica(query);
		titulo="Listado de los usuarios registrados - Ultimo mes";

	}else if(strcmp(operandos->back(),"listadoConectadoMes")==0){
				string query = "select distinct(u.usuario),Date_format(fechaLogin,'%d/%m/%Y') from estadistica e,usuarios u where u.id=e.usuarioId and Date_format(fechaLogin,'%m/%Y')=Date_format(now(),'%m/%Y')";
				respuesta=getRespuestaEstadistica(query);
				titulo="Listado de los usuarios conectados - Ultimo mes";

	}else if(strcmp(operandos->back(),"listadoConectadoAnio")==0){
		string query = "select distinct(u.usuario),Date_format(fechaLogin,'%d/%m/%Y')  from estadistica e,usuarios u where u.id=e.usuarioId and Date_format(fechaLogin,'%Y')=Date_format(now(),'%Y')";
		respuesta=getRespuestaEstadistica(query);
		titulo="Listado de los usuarios conectados - Ultimo año";
	}else if(strcmp(operandos->back(),"listadoRegistradoAnio")==0){
		string query = "select usuario,fechaRegistro from usuarios where Date_format(fechaRegistro,'%Y')=Date_format(now(),'%Y')";
		respuesta=getRespuestaEstadistica(query);
		titulo="Listado de los usuarios registrados - Ultimo año";

	}else if(strcmp(operandos->back(),"evolucionUsuarioConectado")==0){
		string query = "SELECT DATE_FORMAT(fechaLogin,'%d/%m/%Y'), COUNT(DISTINCT(usuarioId)) FROM estadistica group by fechaLogin";
		respuesta=getRespuestaEstadistica(query);
		titulo="Evolucion de los usuarios conectados";

	}else if(strcmp(operandos->back(),"evolucionUsuario")==0){
			string query = "SELECT fechaRegistro, COUNT(DISTINCT(id)) FROM usuarios group by fechaRegistro";
			respuesta=getRespuestaEstadistica(query);
			titulo="Evolucion de los usuarios";
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
	string op=operandos->back();
	this->escribirArchivoEstadisticas(titulo,op,respuesta);

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

void K::escribirArchivoEstadisticas(string titulo, string op, list<string>* respuesta){

	list<string>* titol = this->getTituloEstadistica(op);
		list<string>::iterator it = respuesta->begin();
		list<string>::iterator it2 = titol->begin();
		(*this->archivoEstadistica) << titulo << endl;
		while(it2 != titol->end()){
			(*this->archivoEstadistica) << *it2 << "\t"<<"\t";
			it2++;
			(*this->archivoEstadistica) << *it2 << endl;
			it2++;
		}

		while(it != respuesta->end()){
			(*this->archivoEstadistica) << *it <<"\t"<<"\t";
			it++;
			(*this->archivoEstadistica) << *it <<endl;
			it++;
		}
		(*this->archivoEstadistica) <<endl;
}

list<string>* K::getTituloEstadistica(string op){
	list<string>* resultado = new list<string>();
	list<string>::iterator it = resultado->begin();

	if (op=="ranking"){
		it = resultado->insert(it, "usuario");
		it++;
		it = resultado->insert(it, "fichas");
		return resultado;
	}else if (op=="evolucionUsuarioConectado"){
		it = resultado->insert(it, "fecha");
		it++;
		it = resultado->insert(it, "conectados");
		return resultado;
	}else if (op=="evolucionUsuario"){
		it = resultado->insert(it, "fecha");
		it++;
		it = resultado->insert(it, "registrados");
		return resultado;
	}else{
		it = resultado->insert(it, "usuario");
		it++;
		it = resultado->insert(it, "fecha");
		return resultado;

	}
}



K::~K() {
	// TODO Auto-generated destructor stub
}
