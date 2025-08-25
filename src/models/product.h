#pragma once
#include <string>
#include <memory>
#include <vector>
#include "db_connection.h"

class Product {
public:
    Product(int id, const std::string& name, int categoryId, int quantity);

    [[nodiscard]] int getId() const;
    [[nodiscard]] std::string getName() const;
    [[nodiscard]] int getCategoryId() const;
    [[nodiscard]] int getQuantity() const;

    void setQuantity(int quantity);

    static void insert(const std::shared_ptr<sql::Connection>& conn, const std::string& name, int categoryId, int quantity);
    static std::vector<Product> getAll(const std::shared_ptr<sql::Connection>& conn);
    static Product getById(const std::shared_ptr<sql::Connection>& conn, int id);
    static void update(const std::shared_ptr<sql::Connection>& conn, int id, const std::string& name, int categoryId, int quantity);
    static void remove(const std::shared_ptr<sql::Connection>& conn, int id);
private:
    int id;
    std::string name;
    int categoryId;
    int quantity;
};
