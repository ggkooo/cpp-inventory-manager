#pragma once
#include <string>
#include <memory>
#include <vector>
#include "db_connection.h"

class Product {
public:
    Product(int id, const std::string& name, const std::string& description, int categoryId, int quantity, double costPrice, double salePrice, const std::string& unit, const std::string& sku, int supplierId, const std::string& status, double weight, const std::string& dimensions, const std::string& image, const std::string& createdAt, const std::string& updatedAt);

    [[nodiscard]] int getId() const;
    [[nodiscard]] std::string getName() const;
    [[nodiscard]] std::string getDescription() const;
    [[nodiscard]] int getCategoryId() const;
    [[nodiscard]] int getQuantity() const;
    [[nodiscard]] double getCostPrice() const;
    [[nodiscard]] double getSalePrice() const;
    [[nodiscard]] std::string getUnit() const;
    [[nodiscard]] std::string getSku() const;
    [[nodiscard]] int getSupplierId() const;
    [[nodiscard]] std::string getStatus() const;
    [[nodiscard]] double getWeight() const;
    [[nodiscard]] std::string getDimensions() const;
    [[nodiscard]] std::string getImage() const;
    [[nodiscard]] std::string getCreatedAt() const;
    [[nodiscard]] std::string getUpdatedAt() const;

    void setQuantity(int quantity);

    static void insert(const std::shared_ptr<sql::Connection>& conn, const std::string& name, int categoryId, int quantity);
    static std::vector<Product> getAll(const std::shared_ptr<sql::Connection>& conn);
    static Product getById(const std::shared_ptr<sql::Connection>& conn, int id);
    static void update(const std::shared_ptr<sql::Connection>& conn,
                      int id,
                      const std::string& name,
                      const std::string& description,
                      int categoryId,
                      int quantity,
                      double costPrice,
                      double salePrice,
                      const std::string& unit,
                      const std::string& sku,
                      int supplierId,
                      const std::string& status,
                      double weight,
                      const std::string& dimensions,
                      const std::string& image);
    static void remove(const std::shared_ptr<sql::Connection>& conn, int id);
private:
    int id;
    std::string name;
    std::string description;
    int categoryId;
    int quantity;
    double costPrice;
    double salePrice;
    std::string unit;
    std::string sku;
    int supplierId;
    std::string status;
    double weight;
    std::string dimensions;
    std::string image;
    std::string createdAt;
    std::string updatedAt;
};
