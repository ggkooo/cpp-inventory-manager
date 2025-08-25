#include "product.h"
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <stdexcept>
#include <vector>

Product::Product(int id, const std::string& name, const std::string& description, int categoryId, int quantity, double costPrice, double salePrice, const std::string& unit, const std::string& sku, int supplierId, const std::string& status, double weight, const std::string& dimensions, const std::string& image, const std::string& createdAt, const std::string& updatedAt)
    : id(id), name(name), description(description), categoryId(categoryId), quantity(quantity), costPrice(costPrice), salePrice(salePrice), unit(unit), sku(sku), supplierId(supplierId), status(status), weight(weight), dimensions(dimensions), image(image), createdAt(createdAt), updatedAt(updatedAt) {}

int Product::getId() const { return id; }
std::string Product::getName() const { return name; }
std::string Product::getDescription() const { return description; }
int Product::getCategoryId() const { return categoryId; }
int Product::getQuantity() const { return quantity; }
double Product::getCostPrice() const { return costPrice; }
double Product::getSalePrice() const { return salePrice; }
std::string Product::getUnit() const { return unit; }
std::string Product::getSku() const { return sku; }
int Product::getSupplierId() const { return supplierId; }
std::string Product::getStatus() const { return status; }
double Product::getWeight() const { return weight; }
std::string Product::getDimensions() const { return dimensions; }
std::string Product::getImage() const { return image; }
std::string Product::getCreatedAt() const { return createdAt; }
std::string Product::getUpdatedAt() const { return updatedAt; }

void Product::setQuantity(int quantity) { this->quantity = quantity; }

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
    const std::unique_ptr<sql::ResultSet> res(stmt->executeQuery(
        "SELECT id, name, description, category_id, quantity, cost_price, sale_price, unit, sku, supplier_id, status, weight, dimensions, image, created_at, updated_at FROM products"));
    while (res->next()) {
        products.emplace_back(
            res->getInt("id"),
            res->getString("name"),
            res->getString("description"),
            res->getInt("category_id"),
            res->getInt("quantity"),
            res->getDouble("cost_price"),
            res->getDouble("sale_price"),
            res->getString("unit"),
            res->getString("sku"),
            res->isNull("supplier_id") ? -1 : res->getInt("supplier_id"),
            res->getString("status"),
            res->isNull("weight") ? 0.0 : res->getDouble("weight"),
            res->getString("dimensions"),
            res->getString("image"),
            res->getString("created_at"),
            res->getString("updated_at")
        );
    }
    return products;
}

Product Product::getById(const std::shared_ptr<sql::Connection>& conn, int id) {
    const std::unique_ptr<sql::PreparedStatement> prepared_statement(conn->prepareStatement(
        "SELECT id, name, description, category_id, quantity, cost_price, sale_price, unit, sku, supplier_id, status, weight, dimensions, image, created_at, updated_at FROM products WHERE id = ?"));
    prepared_statement->setInt(1, id);
    const std::unique_ptr<sql::ResultSet> res(prepared_statement->executeQuery());
    if (res->next()) {
        return Product(
            res->getInt("id"),
            res->getString("name"),
            res->getString("description"),
            res->getInt("category_id"),
            res->getInt("quantity"),
            res->getDouble("cost_price"),
            res->getDouble("sale_price"),
            res->getString("unit"),
            res->getString("sku"),
            res->isNull("supplier_id") ? -1 : res->getInt("supplier_id"),
            res->getString("status"),
            res->isNull("weight") ? 0.0 : res->getDouble("weight"),
            res->getString("dimensions"),
            res->getString("image"),
            res->getString("created_at"),
            res->getString("updated_at")
        );
    } else {
        throw std::runtime_error("Product not found");
    }
}

void Product::update(const std::shared_ptr<sql::Connection>& conn,
                     int id,
                     const std::string& name,
                     const std::string& description,
                     int categoryId,
                     int quantity,
                     double costPrice,
                     double salePrice,
                     const std::string& unit,
                     const std::string& sku,
                     int supplierId,
                     const std::string& status,
                     double weight,
                     const std::string& dimensions,
                     const std::string& image) {
    std::unique_ptr<sql::PreparedStatement> prepared_statement(
        conn->prepareStatement(
            "UPDATE products SET name = ?, description = ?, category_id = ?, quantity = ?, cost_price = ?, sale_price = ?, unit = ?, sku = ?, supplier_id = ?, status = ?, weight = ?, dimensions = ?, image = ?, updated_at = NOW() WHERE id = ?"
        )
    );
    prepared_statement->setString(1, name);
    prepared_statement->setString(2, description);
    prepared_statement->setInt(3, categoryId);
    prepared_statement->setInt(4, quantity);
    prepared_statement->setDouble(5, costPrice);
    prepared_statement->setDouble(6, salePrice);
    prepared_statement->setString(7, unit);
    prepared_statement->setString(8, sku);
    prepared_statement->setInt(9, supplierId);
    prepared_statement->setString(10, status);
    prepared_statement->setDouble(11, weight);
    prepared_statement->setString(12, dimensions);
    prepared_statement->setString(13, image);
    prepared_statement->setInt(14, id);
    prepared_statement->execute();
}

void Product::remove(const std::shared_ptr<sql::Connection>& conn, int id) {
    std::unique_ptr<sql::PreparedStatement> prepared_statement(conn->prepareStatement("DELETE FROM products WHERE id = ?"));
    prepared_statement->setInt(1, id);
    prepared_statement->execute();
}
