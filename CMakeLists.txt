cmake_minimum_required(VERSION 3.10)
project(cpp-inventory-manager)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SRC_FILES
        src/main.cpp
        src/models/product.cpp
        src/models/category.cpp
        src/controllers/product_controller.cpp
        src/controllers/category_controller.cpp
)
add_executable(cpp_inventory_manager_ ${SRC_FILES})