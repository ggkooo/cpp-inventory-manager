#ifndef DB_CONNECTION_H
#define DB_CONNECTION_H

#include <memory>
#include <cppconn/connection.h>
#include <mysql_driver.h>

class DBConnection {
public:
    DBConnection(const std::string& host, const std::string& user, const std::string& password, const std::string& schema);
    ~DBConnection();
    std::shared_ptr<sql::Connection> getConnection();
private:
    std::shared_ptr<sql::Connection> conn;
};

#endif // DB_CONNECTION_H

