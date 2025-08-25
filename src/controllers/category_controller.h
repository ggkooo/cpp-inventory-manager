#pragma once
#include <vector>

#include "../models/category.h"
#include "../models/db_connection.h"

class CategoryController
{
public:
    explicit CategoryController(DBConnection* dbConnection);
    void add(const std::string& name);
    [[nodiscard]] std::vector<Category> list() const;
    bool remove(int id);

private:
    DBConnection* dbConnection;
};
