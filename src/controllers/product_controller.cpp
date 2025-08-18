#include "product_controller.h"

void ProductController::add(const Product& product)
{
    products.push_back(product);
}

std::vector<Product> ProductController::show() const
{
    return products;
}

bool ProductController::remove(int id)
{
    for (auto it = products.begin(); it != products.end(); ++it)
    {
        if (it->getId() == id)
        {
            products.erase(it);
            return true;
        }
    }
    return false;
}

Product* ProductController::searchById(int id)
{
    for (auto& product : products)
    {
        if (product.getId() == id)
        {
            return &product;
        }
    }
    return nullptr;
}

