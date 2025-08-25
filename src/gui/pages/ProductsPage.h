#pragma once
#include <QWidget>
#include <QTableWidget>
#include <QLineEdit>
#include <QComboBox>
#include <vector>
#include <unordered_map>
#include "../../controllers/product_controller.h"
#include "../../controllers/category_controller.h"

class ProductsPage : public QWidget {
    Q_OBJECT
public:
    explicit ProductsPage(ProductController* productController, CategoryController* categoryController, QWidget* parent = nullptr);
    void refreshTable();
private slots:
    void onSearchTextChanged(const QString& text);
    void onCategoryChanged(int index);
    void onEditProduct(int productId);
    void onDeleteProduct(int productId);

private:
    QTableWidget* tableWidget;
    QLineEdit* searchEdit;
    QComboBox* categoryCombo;
    ProductController* productController;
    CategoryController* categoryController;
    std::vector<Product> allProducts;
    std::unordered_map<int, std::string> categoryMap;
    void setupTable();
    void loadCategories();
    void loadProducts();
    void applyFilters();
};
