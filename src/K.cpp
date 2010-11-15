/*
 * K.cpp
 *
 *  Created on: 14/11/2010
 *      Author: javier
 */

#include "K.h"

K::K() {
	// TODO Auto-generated constructor stub

}

list<string>* K::realizarOpearacion(list<char*>* operandos){
	//MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;

	list<string>* respuesta = new list<string>();
	list<string>::iterator it=respuesta->begin();

	Conexion* conexion = Conexion::instancia();

	string query = "select usuario, plata from usuarios order by plata desc";
	res = conexion->ejecutarQuery(query.c_str());
	int size =(int) mysql_num_fields(res);
	while ((row = mysql_fetch_row(res)))
	{

	 //if ((row = mysql_fetch_row(res)) !=NULL){
		// int size = (int) mysql_num_fields(res);
		 for (int i = 0; i < size; i++) {
			 respuesta->push_back(row[i]);
		}

	 }
//	else{
//		 it=respuesta->begin();
//		 		it=respuesta->insert(it,"Error");
//		 		it++;
//		 		it=respuesta->insert(it,"V");
//		 		it++;
//		 		it=respuesta->insert(it,"No hay datos");
//		 		return respuesta;
//	 }
	 conexion->liberarConexion(res);

	respuesta->push_front("Correcto");
	return respuesta;

}




K::~K() {
	// TODO Auto-generated destructor stub
}
