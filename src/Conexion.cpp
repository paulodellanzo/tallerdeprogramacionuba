/*
 * conexion.cpp
 *
 */

#include "Conexion.h"

Conexion * Conexion::instanciaUnica;
MYSQL*  Conexion::conn;
Conexion::Conexion(int i) {
	ParserServidor *parserAux = new ParserServidor(PATHARCHIVOCONF);
	//this->conn=conn;
	if (parserAux->comprobarSintaxis()) {
		this->infoconexion = parserAux->getInformacionConexion();
		this->conn= mysql_init(NULL);

		    if (!mysql_real_connect(this->conn,this->infoconexion->server, this->infoconexion->user,this->infoconexion->password, this->infoconexion->database, 0, NULL, 0)) {
		      printf("Error en la conexion : %s\n", mysql_error(this->conn));
		      exit(1);
		    }
	} else {
		cout << "Sintaxis de archivo de configuración incorrecta" << endl;
		cout<<"Se cerrara la aplicacion..."<<endl;
		sleep(1);
		exit(0);
	}
}
	Conexion *Conexion::instancia(){
			    if (!instanciaUnica){
			    	instanciaUnica =new Conexion(1);
			    }
			    return instanciaUnica;
	}


//
//MYSQL* Conexion::crearConexion()
//{
//    MYSQL *connection = mysql_init(NULL);
//
//    if (!mysql_real_connect(connection,"localhost", "root","root", "poker", 0, NULL, 0)) {
//      printf("Error en la conexion : %s\n", mysql_error(connection));
//      exit(1);
//    }
//    return connection;
//}

MYSQL_RES* Conexion::ejecutarQuery(const char *sql_query)
{
   if (mysql_query(this->conn, sql_query))
   {
      printf("MySQL query error : %s\n", mysql_error(this->conn));
      exit(1);
   }

   return mysql_use_result(this->conn);
}

void Conexion::liberarConexion(MYSQL_RES *result){

	mysql_free_result(result);

}


