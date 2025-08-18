# 📦 C++ Inventory Manager

Welcome to the **C++ Inventory Manager**!  
This console application helps you manage products and categories in a simple inventory system.

## 🚀 Features

- 🗂️ Add, list, and remove **categories**
- 📋 Add, list, and remove **products**
- 🔗 Link products to categories
- 📊 See all your stock in one place

## 🛠️ How to Use

1. **Build the project** with your favorite C++ compiler
2. **Run the executable**
3. Use the interactive menu to:
    - Add new categories and products
    - View lists of products and categories
    - Remove items from your inventory

## 📁 Project Structure

```
src/
├── controllers/
│   ├── product_controller.h/.cpp
│   └── category_controller.h/.cpp
├── models/
│   ├── product.h/.cpp
│   └── category.h/.cpp
└── main.cpp
```

## ⚡ Example

```
===== Gerenciador de Estoque =====
1. Add category
2. List categories
3. Add product
4. List products
5. Remove product
6. Remove category
0. Exit
Choose an option:
```

## 📝 Notes

- All data is stored in memory (no database/file persistence yet).
- The program is in English, but some menu labels may be in Portuguese.

---

Made with 💙 using C++