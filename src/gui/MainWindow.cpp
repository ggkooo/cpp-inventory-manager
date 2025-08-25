#include "MainWindow.h"
#include "pages/HomePage.h"
#include <QApplication>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QStackedWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    setWindowTitle("Inventory Manager - Qt GUI");
    showMaximized();

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
    stackedWidget->setCurrentIndex(0); // HomePage como padrão

    // Layout principal
    mainLayout->addWidget(sidebarWidget);
    mainLayout->addWidget(stackedWidget, 1);
    setCentralWidget(centralWidget);
}

MainWindow::~MainWindow() {}
