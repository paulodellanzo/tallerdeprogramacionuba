/*
 * conexion.cpp
 *
 */

#include "Conexion.h"

Conexion::Conexion() {
}


MYSQL* Conexion::crearConexion()
{
    MYSQL *connection = mysql_init(NULL);

    if (!mysql_real_connect(connection,"localhost", "root","root", "poker", 0, NULL, 0)) {
      printf("Error en la conexion : %s\n", mysql_error(connection));
      exit(1);
    }
    return connection;
}

MYSQL_RES* Conexion::ejecutarQuery(MYSQL *connection,const char *sql_query)
{
   if (mysql_query(connection, sql_query))
   {
      printf("MySQL query error : %s\n", mysql_error(connection));
      exit(1);
   }

   return mysql_use_result(connection);
}
