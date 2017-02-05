#include "sql_cli.h"
#include <cstdlib>

sql::Connection *mysqlConn;

void init_sql_connect()
{
/* connect to mysql */
    sql::mysql::MySQL_Driver *driver;
    try{
        driver = sql::mysql::get_mysql_driver_instance();

        mysqlConn = driver->connect("tcp://127.0.0.1:3306", "dzmj", "123456");

        if (!mysqlConn->isValid())
        {
            std::cout << "Connect to MySQL Server failed!" << std::endl;
            return ;
        }
        mysqlConn->setSchema("dzmj");
    }
    catch(sql::SQLException &e)
    {
        std::cout << e.what() << std::endl;
        exit(-1);
    }
}
