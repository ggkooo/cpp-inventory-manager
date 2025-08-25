#pragma once
#include <string>
#include <memory>
#include <vector>

#include "db_connection.h"

class Category
{
public:
    explicit Category(std::string  name);
    Category(int id, std::string name);

    [[nodiscard]] int getId() const;
    [[nodiscard]] std::string getName() const;

    static void insert(const std::shared_ptr<sql::Connection>& conn, const std::string& name);
    static Category getById(const std::shared_ptr<sql::Connection>& conn, int id);
    static std::vector<Category> getAll(const std::shared_ptr<sql::Connection>& conn);
    static void update(const std::shared_ptr<sql::Connection>& conn, int id, const std::string& name);
    static void remove(const std::shared_ptr<sql::Connection>& conn, int id);
private:
    int id{};
    std::string name;
};
