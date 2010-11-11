/*
 * conexion.h
 *
 */
#include "stdio.h"
#include <iostream>
#include <mysql/mysql.h>
#include <string>
#include <stdlib.h>
#include "ParserServidor.h"
#define PATHARCHIVOCONF "config.ini"
using namespace std;

#ifndef CONEXION_H_
#define CONEXION_H_


class Conexion {
protected:
	Conexion(int i);

public:
	static Conexion* instancia();
	//static MYSQL* crearConexion();
	 MYSQL_RES* ejecutarQuery(const char *sql_query);
	 void liberarConexion(MYSQL_RES *result);

private:
	ParserServidor* parser;
	static Conexion* instanciaUnica;
	MYSQL *connection;
	static MYSQL* conn;
	informacionConexion* infoconexion;



};

#endif /* CONEXION_H_ */
