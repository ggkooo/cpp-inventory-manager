#include "MainWindow.h"
#include "pages/HomePage.h"
#include "pages/ProductsPage.h"
#include "../models/db_connection.h"
#include "../controllers/product_controller.h"
#include "../controllers/category_controller.h"
#include <QApplication>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QStackedWidget>
#include <laserpants/dotenv-0.9.3/dotenv.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    setWindowTitle("Inventory Manager - Qt GUI");
    showMaximized();

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
    dbConnection = new DBConnection(host, user, password, schema);
    categoryController = new CategoryController(dbConnection);
    productController = new ProductController(dbConnection);

    // Widget central e layout principal
    QWidget *centralWidget = new QWidget(this);
    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);

    // Sidebar
    sidebarWidget = new QWidget(centralWidget);
    QVBoxLayout *sidebarLayout = new QVBoxLayout(sidebarWidget);
    sidebarLayout->setAlignment(Qt::AlignTop);

    // Sidebar buttons (now class members)
    btnHome = new QPushButton("Home", sidebarWidget);
    btnProducts = new QPushButton("Products", sidebarWidget);
    btnCategories = new QPushButton("Categories", sidebarWidget);
    btnExit = new QPushButton("Exit", sidebarWidget);
    btnHome->setCursor(Qt::PointingHandCursor);
    btnProducts->setCursor(Qt::PointingHandCursor);
    btnCategories->setCursor(Qt::PointingHandCursor);
    btnExit->setCursor(Qt::PointingHandCursor);
    sidebarLayout->addWidget(btnHome);
    sidebarLayout->addSpacing(10);
    sidebarLayout->addWidget(btnProducts);
    sidebarLayout->addSpacing(10);
    sidebarLayout->addWidget(btnCategories);
    sidebarLayout->addSpacing(10);
    sidebarLayout->addWidget(btnExit);
    sidebarLayout->addStretch();

    sidebarWidget->setLayout(sidebarLayout);
    sidebarWidget->setFixedWidth(200);

    // Estilo da sidebar e botões
    sidebarWidget->setStyleSheet(
        "background-color: #2d2d30;"
        "border-top-left-radius: 12px; border-bottom-left-radius: 12px;"
    );
    QString btnStyle =
        "QPushButton {"
        "  background-color: #393942;"
        "  color: #fff;"
        "  border: none;"
        "  border-radius: 8px;"
        "  padding: 12px 24px;"
        "  font-size: 16px;"
        "  margin-bottom: 4px;"
        "  text-align: left;"
        "}"
        "QPushButton:hover {"
        "  background-color: #50505a;"
        "}"
        "QPushButton:pressed {"
        "  background-color: #22222a;"
        "}";
    QString btnSelectedStyle =
        "QPushButton {"
        "  background-color: #0078d7;"
        "  color: #fff;"
        "  border: none;"
        "  border-radius: 8px;"
        "  padding: 12px 24px;"
        "  font-size: 16px;"
        "  margin-bottom: 4px;"
        "  text-align: left;"
        "}"
        "QPushButton:hover {"
        "  background-color: #2893e3;"
        "}"
        "QPushButton:pressed {"
        "  background-color: #005fa3;"
        "}";
    btnHome->setStyleSheet(btnSelectedStyle);
    btnProducts->setStyleSheet(btnStyle);
    btnCategories->setStyleSheet(btnStyle);
    btnExit->setStyleSheet(btnStyle);

    // QStackedWidget para páginas
    stackedWidget = new QStackedWidget(centralWidget);
    HomePage *homePage = new HomePage(stackedWidget);
    stackedWidget->addWidget(homePage); // index 0
    // ProductsPage
    productsPage = new ProductsPage(productController, categoryController, stackedWidget);
    stackedWidget->addWidget(productsPage); // index 1
    stackedWidget->setCurrentIndex(0); // HomePage como padrão

    // Layout principal
    mainLayout->addWidget(sidebarWidget);
    mainLayout->addWidget(stackedWidget, 1);
    setCentralWidget(centralWidget);

    // Conexão dos botões
    connect(btnHome, &QPushButton::clicked, this, [=]() {
        stackedWidget->setCurrentIndex(0);
        btnHome->setStyleSheet(btnSelectedStyle);
        btnProducts->setStyleSheet(btnStyle);
        btnCategories->setStyleSheet(btnStyle);
    });
    connect(btnProducts, &QPushButton::clicked, this, [=]() {
        productsPage->refreshTable();
        stackedWidget->setCurrentIndex(1);
        btnHome->setStyleSheet(btnStyle);
        btnProducts->setStyleSheet(btnSelectedStyle);
        btnCategories->setStyleSheet(btnStyle);
    });
}

MainWindow::~MainWindow() {}
