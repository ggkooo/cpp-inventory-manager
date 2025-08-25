cmake_minimum_required(VERSION 3.10)
project(cpp-inventory-manager)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SRC_FILES
        src/main.cpp
        src/models/product.cpp
        src/models/category.cpp
        src/models/db_connection.cpp
        src/controllers/product_controller.cpp
        src/controllers/category_controller.cpp
)
add_executable(cpp_inventory_manager_ ${SRC_FILES})

include_directories(/usr/include/cppconn)
target_link_libraries(cpp_inventory_manager_ PRIVATE mysqlcppconn)
target_include_directories(cpp_inventory_manager_ PRIVATE src/external/dotenv-cpp/include)
