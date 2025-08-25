#include "product_controller.h"

ProductController::ProductController(DBConnection* dbConnection)
    : dbConnection(dbConnection) {}

void ProductController::add(std::string name, int categoryId, int quantity) const
{
    Product::insert(dbConnection->getConnection(), name, categoryId, quantity);
}

std::vector<Product> ProductController::show() const
{
    auto allProducts = Product::getAll(dbConnection->getConnection());
    return allProducts;
}

bool ProductController::remove(int id)
{
    try
    {
        Product::remove(dbConnection->getConnection(), id);
        return true;
    } catch (const std::exception& e)
    {
        return false;
    }
}

Product* ProductController::searchById(int id)
{
    try
    {
        Product product = Product::getById(dbConnection->getConnection(), id);
        return new Product(product);
    } catch (const std::exception& e)
    {
        return nullptr;
    }
}

