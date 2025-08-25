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
find_package(Qt5 COMPONENTS Widgets REQUIRED)

set(GUI_SRC_FILES
        src/gui/MainWindow.cpp
        src/gui/pages/HomePage.cpp
)
set(GUI_HDR_FILES
        src/gui/MainWindow.h
        src/gui/pages/HomePage.h
)

set(SRC_FILES
    ${SRC_FILES}
    ${GUI_SRC_FILES}
    ${GUI_HDR_FILES}
)

include_directories(${Qt5Widgets_INCLUDE_DIRS})

add_definitions(${Qt5Widgets_DEFINITIONS})

set(CMAKE_AUTOMOC ON)

add_executable(cpp_inventory_manager_ ${SRC_FILES})

include_directories(/usr/include/cppconn)
target_link_libraries(cpp_inventory_manager_ PRIVATE mysqlcppconn)
target_include_directories(cpp_inventory_manager_ PRIVATE src/external/dotenv-cpp/include)

if(Qt5Widgets_FOUND)
    target_link_libraries(cpp_inventory_manager_ PRIVATE Qt5::Widgets)
endif()
