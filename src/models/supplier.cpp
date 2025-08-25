#include "supplier.h"
#include <cppconn/statement.h>
#include <cppconn/resultset.h>

Supplier::Supplier(int id, const std::string& name) : id(id), name(name) {}
int Supplier::getId() const { return id; }
std::string Supplier::getName() const { return name; }

std::vector<Supplier> Supplier::getAll(const std::shared_ptr<sql::Connection>& conn) {
    std::vector<Supplier> suppliers;
    std::unique_ptr<sql::Statement> stmt(conn->createStatement());
    std::unique_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT id, name FROM suppliers"));
    while (res->next()) {
        suppliers.emplace_back(res->getInt("id"), res->getString("name"));
    }
    return suppliers;
}
