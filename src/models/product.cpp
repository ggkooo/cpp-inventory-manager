#include "product.h"
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <stdexcept>
#include <vector>

Product::Product(int id, const std::string& name, int categoryId, int quantity) : id(id), name(name), categoryId(categoryId), quantity(quantity) {}

int Product::getId() const
{
    return id;
}

std::string Product::getName() const
{
    return name;
}

int Product::getCategoryId() const
{
    return categoryId;
}

int Product::getQuantity() const
{
    return quantity;
}

void Product::setQuantity(int quantity)
{
    this->quantity = quantity;
}

void Product::insert(const std::shared_ptr<sql::Connection>& conn, const std::string& name, int categoryId, int quantity) {
    std::unique_ptr<sql::PreparedStatement> prepared_statement(conn->prepareStatement("INSERT INTO products (name, category_id, quantity) VALUES (?, ?, ?)"));
    prepared_statement->setString(1, name);
    prepared_statement->setInt(2, categoryId);
    prepared_statement->setInt(3, quantity);
    prepared_statement->execute();
}

std::vector<Product> Product::getAll(const std::shared_ptr<sql::Connection>& conn) {
    std::vector<Product> products;
    const std::unique_ptr<sql::Statement> stmt(conn->createStatement());
    const std::unique_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT id, name, category_id, quantity FROM products"));
    while (res->next()) {
        products.emplace_back(res->getInt("id"), res->getString("name"), res->getInt("category_id"), res->getInt("quantity"));
    }
    return products;
}

Product Product::getById(const std::shared_ptr<sql::Connection>& conn, int id) {
    const std::unique_ptr<sql::PreparedStatement> prepared_statement(conn->prepareStatement("SELECT id, name, category_id, quantity FROM products WHERE id = ?"));
    prepared_statement->setInt(1, id);
    const std::unique_ptr<sql::ResultSet> res(prepared_statement->executeQuery());
    if (res->next()) {
        return Product(res->getInt("id"), res->getString("name"), res->getInt("category_id"), res->getInt("quantity"));
    } else
    {
        throw std::runtime_error("Produto não encontrado");
    }
}

void Product::update(const std::shared_ptr<sql::Connection>& conn, int id, const std::string& name, int categoryId, int quantity) {
    std::unique_ptr<sql::PreparedStatement> prepared_statement(conn->prepareStatement("UPDATE products SET name = ?, category_id = ?, quantity = ? WHERE id = ?"));
    prepared_statement->setString(1, name);
    prepared_statement->setInt(2, categoryId);
    prepared_statement->setInt(3, quantity);
    prepared_statement->setInt(4, id);
    prepared_statement->execute();
}

void Product::remove(const std::shared_ptr<sql::Connection>& conn, int id) {
    std::unique_ptr<sql::PreparedStatement> prepared_statement(conn->prepareStatement("DELETE FROM products WHERE id = ?"));
    prepared_statement->setInt(1, id);
    prepared_statement->execute();
}
