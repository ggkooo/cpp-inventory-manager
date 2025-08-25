#include <QApplication>
#include <iostream>
#include <laserpants/dotenv-0.9.3/dotenv.h>

#include "gui/MainWindow.h"
#include "models/db_connection.h"
#include "models/product.h"
#include "models/category.h"
#include "controllers/product_controller.h"
#include "controllers/category_controller.h"

void listProducts(const ProductController& productController, const CategoryController& categoryController) {
    auto products = productController.show();
    if (products.empty()) {
        std::cout << "No products registered.\n";
        return;
    }
    std::cout << "\n--- Product List ---\n";
    for (const auto& product : products) {
        auto catOpt = categoryController.searchById(product.getCategoryId());
        std::string categoryName = catOpt.has_value() ? catOpt->getName() : "Unknown";
        std::cout << "ID: " << product.getId()
                  << " | Name: " << product.getName()
                  << " | Category: " << categoryName
                  << " | Quantity: " << product.getQuantity()
                  << std::endl;
    }
}

void listCategories(const CategoryController& categoryController) {
    auto categories = categoryController.list();
    if (categories.empty()) {
        std::cout << "No categories registered.\n";
        return;
    }
    std::cout << "\n--- Category List ---\n";
    for (const auto& category : categories) {
        std::cout << "ID: " << category.getId()
                  << " | Name: " << category.getName()
                  << std::endl;
    }
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow window;
    window.show();

    try
    {
        dotenv::init("../.env");
        const char* host_c = std::getenv("DB_HOST");
        const char* user_c = std::getenv("DB_USER");
        const char* password_c = std::getenv("DB_PASSWORD");
        const char* schema_c = std::getenv("DB_SCHEMA");
        if (!host_c || !user_c || !password_c || !schema_c) {
            throw std::runtime_error("Database environment variables not found. Check the .env file.");
        }
        std::string host(host_c);
        std::string user(user_c);
        std::string password(password_c);
        std::string schema(schema_c);
        DBConnection db(host_c, user_c, password_c, schema_c);
        auto conn = db.getConnection();

        ProductController productController(&db);
        CategoryController categoryController(&db);

        return app.exec();
    } catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}
