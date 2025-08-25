#include "ProductsPage.h"
#include <QVBoxLayout>
#include <QStringList>
#include <QHeaderView>
#include <unordered_map>
#include <QHBoxLayout>
#include <QPushButton>
#include <QStyle>

ProductsPage::ProductsPage(ProductController* productController, CategoryController* categoryController, QWidget* parent)
    : QWidget(parent), productController(productController), categoryController(categoryController) {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    QHBoxLayout* filterLayout = new QHBoxLayout();
    searchEdit = new QLineEdit(this);
    searchEdit->setPlaceholderText("Buscar produto...");
    categoryCombo = new QComboBox(this);
    filterLayout->addWidget(searchEdit);
    filterLayout->addWidget(categoryCombo);
    mainLayout->addLayout(filterLayout);
    tableWidget = new QTableWidget(this);
    setupTable();
    mainLayout->addWidget(tableWidget);
    setLayout(mainLayout);
    connect(searchEdit, &QLineEdit::textChanged, this, &ProductsPage::onSearchTextChanged);
    connect(categoryCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &ProductsPage::onCategoryChanged);
    refreshTable();
}

void ProductsPage::setupTable() {
    tableWidget->setColumnCount(6);
    QStringList headers;
    headers << "ID" << "Name" << "Category" << "Quantity" << "Description" << "Actions";
    tableWidget->setHorizontalHeaderLabels(headers);
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    tableWidget->horizontalHeader()->setStretchLastSection(false);
    tableWidget->verticalHeader()->setVisible(false);
    tableWidget->setColumnWidth(0, 50);
    tableWidget->setColumnWidth(1, 350);
    tableWidget->setColumnWidth(2, 250);
    tableWidget->setColumnWidth(3, 100);
    tableWidget->setColumnWidth(4, 845);
    tableWidget->setColumnWidth(5, 60);
}

void ProductsPage::refreshTable() {
    loadCategories();
    loadProducts();
    applyFilters();
}

void ProductsPage::loadCategories() {
    categoryCombo->blockSignals(true);
    categoryCombo->clear();
    categoryMap.clear();
    std::vector<Category> categories = categoryController->list();
    categoryCombo->addItem("Todas", QVariant(-1));
    for (const auto& cat : categories) {
        categoryCombo->addItem(QString::fromStdString(cat.getName()), QVariant(cat.getId()));
        categoryMap[cat.getId()] = cat.getName();
    }
    categoryCombo->blockSignals(false);
}

void ProductsPage::loadProducts() {
    allProducts = productController->show();
}

void ProductsPage::applyFilters() {
    QString searchText = searchEdit->text().trimmed().toLower();
    int selectedCategoryId = categoryCombo->currentData().toInt();
    std::vector<const Product*> filtered;
    for (const auto& p : allProducts) {
        // Filtro de categoria
        if (selectedCategoryId != -1 && p.getCategoryId() != selectedCategoryId)
            continue;
        // Filtro de texto
        QString name = QString::fromStdString(p.getName()).toLower();
        if (!searchText.isEmpty() && !name.contains(searchText))
            continue;
        filtered.push_back(&p);
    }
    tableWidget->setRowCount(static_cast<int>(filtered.size()));
    for (int row = 0; row < static_cast<int>(filtered.size()); ++row) {
        const Product& p = *filtered[row];
        tableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(p.getId())));
        tableWidget->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(p.getName())));
        QString categoryDisplay;
        auto it = categoryMap.find(p.getCategoryId());
        if (it != categoryMap.end()) {
            categoryDisplay = QString::fromStdString(it->second);
        } else {
            categoryDisplay = "";
        }
        tableWidget->setItem(row, 2, new QTableWidgetItem(categoryDisplay));
        tableWidget->setItem(row, 3, new QTableWidgetItem(QString::number(p.getQuantity())));
        tableWidget->setItem(row, 4, new QTableWidgetItem(""));
        // Coluna de ações
        QWidget* actionWidget = new QWidget();
        QHBoxLayout* actionLayout = new QHBoxLayout(actionWidget);
        actionLayout->setContentsMargins(0, 0, 0, 0);
        actionLayout->setSpacing(2);
        QPushButton* editBtn = new QPushButton(actionWidget);
        editBtn->setIcon(style()->standardIcon(QStyle::SP_FileDialogDetailedView));
        editBtn->setToolTip("Editar produto");
        editBtn->setProperty("productId", p.getId());
        editBtn->setFixedSize(24, 24);
        connect(editBtn, &QPushButton::clicked, this, [this, p]() { this->onEditProduct(p.getId()); });
        QPushButton* deleteBtn = new QPushButton(actionWidget);
        deleteBtn->setIcon(style()->standardIcon(QStyle::SP_TrashIcon));
        deleteBtn->setToolTip("Excluir produto");
        deleteBtn->setProperty("productId", p.getId());
        deleteBtn->setFixedSize(24, 24);
        connect(deleteBtn, &QPushButton::clicked, this, [this, p]() { this->onDeleteProduct(p.getId()); });
        actionLayout->addWidget(editBtn);
        actionLayout->addWidget(deleteBtn);
        actionWidget->setLayout(actionLayout);
        tableWidget->setCellWidget(row, 5, actionWidget);
    }
}

void ProductsPage::onSearchTextChanged(const QString&) {
    applyFilters();
}

void ProductsPage::onCategoryChanged(int) {
    applyFilters();
}

void ProductsPage::onEditProduct(int productId) {
    // TODO: Implementar diálogo de edição
}

void ProductsPage::onDeleteProduct(int productId) {
    // TODO: Implementar confirmação e exclusão
}
