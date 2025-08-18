#include "product.h"

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

