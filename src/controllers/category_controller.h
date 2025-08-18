#pragma once
#include "../models/category.h"
#include <vector>

class CategoryController
{
public:
    void add(const Category& category);
    [[nodiscard]] std::vector<Category> list() const;
    bool remove(int id);
    [[nodiscard]] const Category* searchById(int id) const;

private:
    std::vector<Category> categories;
};
