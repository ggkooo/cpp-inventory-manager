#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QStackedWidget>
#include <QPushButton>
#include "../models/db_connection.h"
#include "../controllers/product_controller.h"
#include "../controllers/category_controller.h"
#include "pages/ProductsPage.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QWidget* sidebarWidget;
    QStackedWidget* stackedWidget;
    QPushButton* btnHome;
    QPushButton* btnProducts;
    QPushButton* btnCategories;
    QPushButton* btnExit;

    DBConnection* dbConnection;
    ProductController* productController;
    CategoryController* categoryController;
    ProductsPage* productsPage;
};

#endif // MAINWINDOW_H
