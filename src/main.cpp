#include <iostream>
#include <laserpants/dotenv-0.9.3/dotenv.h>

#include "models/db_connection.h"
#include "models/product.h"
#include "models/category.h"
#include "controllers/product_controller.h"
#include "controllers/category_controller.h"

void listProducts(const ProductController& productController, const CategoryController& categoryController) {
    auto products = productController.show();
    if (products.empty()) {
        std::cout << "Nenhum produto cadastrado.\n";
        return;
    }
    std::cout << "\n--- Lista de Produtos ---\n";
    for (const auto& product : products) {
        auto catOpt = categoryController.searchById(product.getCategoryId());
        std::string categoryName = catOpt.has_value() ? catOpt->getName() : "Desconhecida";
        std::cout << "ID: " << product.getId()
                  << " | Nome: " << product.getName()
                  << " | Categoria: " << categoryName
                  << " | Quantidade: " << product.getQuantity()
                  << std::endl;
    }
}

void listCategories(const CategoryController& categoryController) {
    auto categories = categoryController.list();
    if (categories.empty()) {
        std::cout << "Nenhuma categoria cadastrada.\n";
        return;
    }
    std::cout << "\n--- Lista de Categorias ---\n";
    for (const auto& category : categories) {
        std::cout << "ID: " << category.getId()
                  << " | Nome: " << category.getName()
                  << std::endl;
    }
}

int main()
{
    try
    {
        dotenv::init("../.env");
        const char* host_c = std::getenv("DB_HOST");
        const char* user_c = std::getenv("DB_USER");
        const char* password_c = std::getenv("DB_PASSWORD");
        const char* schema_c = std::getenv("DB_SCHEMA");
        if (!host_c || !user_c || !password_c || !schema_c) {
            throw std::runtime_error("Variáveis de ambiente do banco de dados não encontradas. Verifique o arquivo .env.");
        }
        std::string host(host_c);
        std::string user(user_c);
        std::string password(password_c);
        std::string schema(schema_c);
        DBConnection db(host_c, user_c, password_c, schema_c);
        auto conn = db.getConnection();

        ProductController productController(&db);
        CategoryController categoryController(&db);

        int option;
        do {
            std::cout << "\n===== Gerenciador de Estoque =====\n";
            std::cout << "1. Adicionar categoria\n";
            std::cout << "2. Listar categorias\n";
            std::cout << "3. Adicionar produto\n";
            std::cout << "4. Listar produtos\n";
            std::cout << "5. Remover produto\n";
            std::cout << "6. Remover categoria\n";
            std::cout << "0. Sair\n";
            std::cout << "Escolha uma opção: ";
            std::cin >> option;
            std::cin.ignore();

            if (option == 1) {
                std::string name;
                std::cout << "Nome da categoria: ";
                std::getline(std::cin, name);
                categoryController.add(name);
                std::cout << "Categoria adicionada!\n";
            }
            else if (option == 2) {
                listCategories(categoryController);
            }
            else if (option == 3) {
                int categoryId, quantity;
                std::string name;
                std::cout << "Nome do produto: ";
                std::getline(std::cin, name);
                std::cout << "ID da categoria do produto: ";
                std::cin >> categoryId;
                std::cout << "Quantidade: ";
                std::cin >> quantity;
                productController.add(name, categoryId, quantity);
                std::cout << "Produto adicionado!\n";
            }
            else if (option == 4) {
                listProducts(productController, categoryController);
            }
            else if (option == 5) {
                int id;
                std::cout << "ID do produto para remover: ";
                std::cin >> id;
                if (productController.remove(id))
                    std::cout << "Produto removido!\n";
                else
                    std::cout << "Produto não encontrado.\n";
            }
            else if (option == 6) {
                int id;
                std::cout << "ID da categoria para remover: ";
                std::cin >> id;
                if (categoryController.remove(id))
                    std::cout << "Categoria removida!\n";
                else
                    std::cout << "Categoria não encontrada.\n";
            }
            else if (option == 0) {
                std::cout << "Saindo...\n";
            }
            else {
                std::cout << "Opção inválida!\n";
            }
        } while (option != 0);

        return 0;
    } catch (const std::exception& e)
    {
        std::cerr << "Erro: " << e.what() << std::endl;
        return 1;
    }
}
