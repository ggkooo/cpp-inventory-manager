#pragma once
#include <string>

class Category
{
public:
    Category(int id, const std::string& name);

    int getId() const;
    std::string getName() const;
private:
    int id;
    std::string name;
};
