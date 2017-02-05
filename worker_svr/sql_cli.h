#ifndef SQL_CLI_H
#define SQL_CLI_H

#include <mysql_driver.h>
#include <cppconn/statement.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/prepared_statement.h>

extern sql::Connection *mysqlConn;

void init_sql_connect();


#endif // SQL_CLI_H
