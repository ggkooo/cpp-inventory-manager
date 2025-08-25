#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QStackedWidget>
#include <QPushButton>

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
};

#endif // MAINWINDOW_H
