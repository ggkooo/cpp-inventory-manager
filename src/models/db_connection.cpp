#include "db_connection.h"
#include <cppconn/exception.h>
#include <stdexcept>

DBConnection::DBConnection(const std::string& host, const std::string& user, const std::string& password, const std::string& schema) {
    try {
        sql::mysql::MySQL_Driver* driver = sql::mysql::get_mysql_driver_instance();
        conn = std::shared_ptr<sql::Connection>(driver->connect(host, user, password));
        conn->setSchema(schema);
    } catch (sql::SQLException& e) {
        throw std::runtime_error("Erro ao conectar ao banco de dados: " + std::string(e.what()));
    }
}

DBConnection::~DBConnection() {
    if (conn) {
        conn->close();
    }
}

std::shared_ptr<sql::Connection> DBConnection::getConnection() {
    return conn;
}

