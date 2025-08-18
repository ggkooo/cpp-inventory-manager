#pragma once
#include <string>

class Product {
public:
    Product(int id, const std::string& name, int categoryId, int quantity);

    int getId() const;
    std::string getName() const;
    int getCategoryId() const;
    int getQuantity() const;

    void setQuantity(int quantity);
private:
    int id;
    std::string name;
    int categoryId;
    int quantity;
};
