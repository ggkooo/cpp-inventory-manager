#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <utility>
#include <vector>

#include "category.h"

Category::Category(int id, std::string  name) : id(id), name(std::move(name)) {}

int Category::getId() const
{
    return id;
}

std::string Category::getName() const
{
    return name;
}

void Category::insert(const std::shared_ptr<sql::Connection>& conn, const std::string& name) {
    const std::unique_ptr<sql::PreparedStatement> prepared_statement(conn->prepareStatement("INSERT INTO categories (name) VALUES (?)"));
    prepared_statement->setString(1, name);
    prepared_statement->execute();
}

std::vector<Category> Category::getAll(const std::shared_ptr<sql::Connection>& conn) {
    std::vector<Category> categories;
    const std::unique_ptr<sql::Statement> stmt(conn->createStatement());
    const std::unique_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT id, name FROM categories"));
    while (res->next()) {
        categories.emplace_back(res->getInt("id"), res->getString("name"));
    }
    return categories;
}

void Category::update(const std::shared_ptr<sql::Connection>& conn, int id, const std::string& name) {
    const std::unique_ptr<sql::PreparedStatement> prepared_statement(conn->prepareStatement("UPDATE categories SET name = ? WHERE id = ?"));
    prepared_statement->setString(1, name);
    prepared_statement->setInt(2, id);
    prepared_statement->execute();
}

void Category::remove(const std::shared_ptr<sql::Connection>& conn, int id) {
    const std::unique_ptr<sql::PreparedStatement> prepared_statement(conn->prepareStatement("DELETE FROM categories WHERE id = ?"));
    prepared_statement->setInt(1, id);
    prepared_statement->execute();
}
