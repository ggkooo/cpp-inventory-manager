#include "category_controller.h"

CategoryController::CategoryController(DBConnection* dbConnection)
    : dbConnection(dbConnection) {}

void CategoryController::add(const Category& category)
{
    categories.push_back(category);
}

std::vector<Category> CategoryController::list() const
{
    return categories;
}

bool CategoryController::remove(int id)
{
    for (auto it = categories.begin(); it != categories.end(); ++it)
    {
        if (it->getId() == id)
        {
            categories.erase(it);
            return true;
        }
    }
    return false;
}

const Category* CategoryController::searchById(int id) const
{
    for (auto& category : categories)
    {
        if (category.getId() == id)
        {
            return &category;
        }
    }
    return nullptr;
}
