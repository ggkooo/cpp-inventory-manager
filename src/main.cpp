#include <iostream>
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
        const Category* cat = categoryController.searchById(product.getCategoryId());
        std::string categoryName = cat ? cat->getName() : "Desconhecida";
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

int main() {
    ProductController productController;
    CategoryController categoryController;

    // Products and categorys hardcoded examples
    categoryController.add(Category(1, "Eletrônicos"));
    categoryController.add(Category(2, "Alimentos"));
    productController.add(Product(1, "Notebook", 1, 10));
    productController.add(Product(2, "Arroz", 2, 50));

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
            int id;
            std::string name;
            std::cout << "ID da categoria: ";
            std::cin >> id;
            std::cin.ignore();
            std::cout << "Nome da categoria: ";
            std::getline(std::cin, name);
            categoryController.add(Category(id, name));
            std::cout << "Categoria adicionada!\n";
        }
        else if (option == 2) {
            listCategories(categoryController);
        }
        else if (option == 3) {
            int id, categoryId, quantity;
            std::string name;
            std::cout << "ID do produto: ";
            std::cin >> id;
            std::cin.ignore();
            std::cout << "Nome do produto: ";
            std::getline(std::cin, name);
            std::cout << "ID da categoria do produto: ";
            std::cin >> categoryId;
            std::cout << "Quantidade: ";
            std::cin >> quantity;
            productController.add(Product(id, name, categoryId, quantity));
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
}