#pragma once
#include <string>
#include <vector>
#include <memory>
#include <cppconn/connection.h>

class Supplier {
public:
    Supplier(int id, const std::string& name);
    int getId() const;
    std::string getName() const;
    static std::vector<Supplier> getAll(const std::shared_ptr<sql::Connection>& conn);
private:
    int id;
    std::string name;
};

