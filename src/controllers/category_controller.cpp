#include "category_controller.h"

CategoryController::CategoryController(DBConnection* dbConnection)
    : dbConnection(dbConnection) {}

void CategoryController::add(const std::string& name)
{
    Category::insert(dbConnection->getConnection(), name);
}

std::vector<Category> CategoryController::list() const
{
    return Category::getAll(dbConnection->getConnection());
}

bool CategoryController::remove(int id)
{
    Category::remove(dbConnection->getConnection(), id);
    return true;
}

std::optional<Category> CategoryController::searchById(int id) const {
    auto categories = list();
    for (const auto& category : categories) {
        if (category.getId() == id) {
            return category;
        }
    }
    return std::nullopt;
}
