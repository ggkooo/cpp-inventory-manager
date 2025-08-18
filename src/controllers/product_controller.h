#pragma once
#include "../models/product.h"
#include <vector>

class ProductController
{
public:
    void add(const Product&product);
    [[nodiscard]] std::vector<Product> show() const;
    bool remove(int id);
    Product* searchById(int id);

private:
    std::vector<Product> products;
};
