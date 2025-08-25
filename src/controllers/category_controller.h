#pragma once
#include "../models/category.h"
#include "../models/db_connection.h"
#include <vector>

class CategoryController
{
public:
    explicit CategoryController(DBConnection* dbConnection);
    void add(const Category& category);
    [[nodiscard]] std::vector<Category> list() const;
    bool remove(int id);
    [[nodiscard]] const Category* searchById(int id) const;

private:
    DBConnection* dbConnection;
    std::vector<Category> categories;
};
