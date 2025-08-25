#pragma once
#include <vector>

#include "../models/product.h"
#include "../models/db_connection.h"

class ProductController
{
public:
    explicit ProductController(DBConnection* dbConnection);
    void add(std::string name, int categoryId, int quantity) const;
    [[nodiscard]] std::vector<Product> show() const;
    bool remove(int id);
    Product* searchById(int id);
    bool update(const Product& product);
    DBConnection* getDbConnection() const { return dbConnection; }

private:
    DBConnection* dbConnection;
    std::vector<Product> products;
};
