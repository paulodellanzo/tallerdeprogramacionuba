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
	MYSQL_RES *res;
	MYSQL_ROW row;

	list<string>* respuesta = new list<string>();
	list<string>::iterator it=respuesta->begin();

	Conexion* conexion = Conexion::instancia();

	if(strcmp(operandos->back(),"ranking")==0){
		string query = "select usuario, plata from usuarios order by plata desc";
		res = conexion->ejecutarQuery(query.c_str());
		int size =(int) mysql_num_fields(res);
		while ((row = mysql_fetch_row(res)))
		{
		  for (int i = 0; i < size; i++) {
				 respuesta->push_back(row[i]);
			}

		 }
	}else if(strcmp(operandos->back(),"listadoRegistradoDia")==0){
		string query = "select usuario,fechaRegistro from usuarios where DATE_FORMAT(fechaRegistro,'%d/%m/%Y')= DATE_FORMAT(CURDATE(),'%d/%m/%Y')";
			res = conexion->ejecutarQuery(query.c_str());
			int size =(int) mysql_num_fields(res);
			while ((row = mysql_fetch_row(res)))
			{
			  for (int i = 0; i < size; i++) {
					 respuesta->push_back(row[i]);
				}

			 }

	}else if(strcmp(operandos->back(),"listadoRegistradoMes")==0){
		string query = "select usuario,fechaRegistro from usuarios where DATE_FORMAT(fechaRegistro,'%m/%Y')= DATE_FORMAT(now(),'%m/%Y')";
					res = conexion->ejecutarQuery(query.c_str());
					int size =(int) mysql_num_fields(res);
					while ((row = mysql_fetch_row(res)))
					{
					  for (int i = 0; i < size; i++) {
							 respuesta->push_back(row[i]);
						}

					 }

	}else if(strcmp(operandos->back(),"listadoRegistradoAnio")==0){

		string query = "select usuario,fechaRegistro from usuarios where Date_format(fechaRegistro,'%Y')=Date_format(now(),'%Y')";
							res = conexion->ejecutarQuery(query.c_str());
							int size =(int) mysql_num_fields(res);
							while ((row = mysql_fetch_row(res)))
							{
							  for (int i = 0; i < size; i++) {
									 respuesta->push_back(row[i]);
								}

							 }


	}else if(strcmp(operandos->back(),"evolucion")==0){
		string query = "select usuario,fechaRegistro from usuarios where Date_format(fechaRegistro,'%Y')=Date_format(now(),'%Y')";
								res = conexion->ejecutarQuery(query.c_str());
								int size =(int) mysql_num_fields(res);
								while ((row = mysql_fetch_row(res)))
								{
								  for (int i = 0; i < size; i++) {
										 respuesta->push_back(row[i]);
									}

								 }

	}else{
		//error
	}

	 conexion->liberarConexion(res);

	respuesta->push_front("Correcto");
	return respuesta;

}




K::~K() {
	// TODO Auto-generated destructor stub
}
