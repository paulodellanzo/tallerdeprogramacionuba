/*
 * conexion.h
 *
 */
#include "stdio.h"
#include <iostream>
#include <mysql.h>
#include <string>
#include <stdlib.h>
using namespace std;

#ifndef CONEXION_H_
#define CONEXION_H_

class Conexion {
public:
	Conexion();
	static MYSQL* crearConexion();
	static MYSQL_RES* ejecutarQuery(MYSQL *connection,const char *sql_query);

private:
	struct datos_conexion
	{
	    char *server;
	    char *user;
	    char *password;
	    char *database;
	}mysqlD;


	MYSQL *connection, mysql;
	MYSQL_RES *result;
	MYSQL_ROW row;


};

#endif /* CONEXION_H_ */
