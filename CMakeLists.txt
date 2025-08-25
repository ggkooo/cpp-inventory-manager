cmake_minimum_required(VERSION 3.10)
project(cpp-inventory-manager)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SRC_FILES
        src/main.cpp
        src/models/product.cpp
        src/models/category.cpp
        src/models/db_connection.cpp
        src/controllers/product_controller.cpp
        src/controllers/category_controller.cpp
        src/models/supplier.cpp
)
find_package(Qt5 COMPONENTS Widgets REQUIRED)

set(GUI_SRC_FILES
        src/gui/MainWindow.cpp
        src/gui/pages/HomePage.cpp
        src/gui/pages/ProductsPage.cpp
        src/gui/components/EditProductDialog.cpp
)
set(GUI_HDR_FILES
        src/gui/MainWindow.h
        src/gui/pages/HomePage.h
        src/gui/pages/ProductsPage.h
        src/gui/components/EditProductDialog.h
)

set(SRC_FILES
    ${SRC_FILES}
    ${GUI_SRC_FILES}
    ${GUI_HDR_FILES}
)

add_executable(cpp_inventory_manager_
    ${SRC_FILES}
)

include_directories(${Qt5Widgets_INCLUDE_DIRS} src/gui/components src/)
target_include_directories(cpp_inventory_manager_ PRIVATE src/external/dotenv-cpp/include)
target_link_libraries(cpp_inventory_manager_ PRIVATE mysqlcppconn)
if(Qt5Widgets_FOUND)
    target_link_libraries(cpp_inventory_manager_ PRIVATE Qt5::Widgets)
endif()
