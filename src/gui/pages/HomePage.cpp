#include "HomePage.h"
#include <QVBoxLayout>
#include <QLabel>

HomePage::HomePage(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);
    QLabel *label = new QLabel("Welcome to Inventory Manager home page!", this);
    label->setAlignment(Qt::AlignCenter);
    layout->addWidget(label);
    setLayout(layout);
}

HomePage::~HomePage() {}
