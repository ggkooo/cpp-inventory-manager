#include "ProductsPage.h"
#include <QVBoxLayout>
#include <QStringList>
#include <QHeaderView>
#include <unordered_map>
#include <QHBoxLayout>
#include <QPushButton>
#include <QStyle>
#include "../components/EditProductDialog.h"
#include <QMessageBox>
#include <QMenu>
#include "models/supplier.h"

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
    tableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(tableWidget, &QTableWidget::customContextMenuRequested, this, &ProductsPage::showContextMenu);
    refreshTable();
}

void ProductsPage::setupTable() {
    tableWidget->setColumnCount(16);
    QStringList headers;
    headers << "ID" << "Name" << "Description" << "Category" << "Supplier" << "Quantity" << "Cost Price" << "Sale Price" << "Unit" << "SKU" << "Status" << "Weight" << "Dimensions" << "Image" << "Created At" << "Updated At";
    tableWidget->setHorizontalHeaderLabels(headers);
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    tableWidget->horizontalHeader()->setStretchLastSection(false);
    tableWidget->verticalHeader()->setVisible(false);
    // Adjust column widths for clarity
    tableWidget->setColumnWidth(0, 50);   // ID
    tableWidget->setColumnWidth(1, 250);  // Name
    tableWidget->setColumnWidth(2, 350);  // Description
    tableWidget->setColumnWidth(3, 200);  // Category
    tableWidget->setColumnWidth(4, 200);  // Supplier (larger)
    tableWidget->setColumnWidth(5, 80);   // Quantity
    tableWidget->setColumnWidth(6, 100);  // Cost Price
    tableWidget->setColumnWidth(7, 100);  // Sale Price
    tableWidget->setColumnWidth(8, 80);   // Unit
    tableWidget->setColumnWidth(9, 100);  // SKU
    tableWidget->setColumnWidth(10, 100); // Status
    tableWidget->setColumnWidth(11, 80);  // Weight
    tableWidget->setColumnWidth(12, 120); // Dimensions
    tableWidget->setColumnWidth(13, 120); // Image
    tableWidget->setColumnWidth(14, 150); // Created At
    tableWidget->setColumnWidth(15, 150); // Updated At
}

void ProductsPage::refreshTable() {
    loadCategories();
    loadSuppliers();
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

void ProductsPage::loadSuppliers() {
    supplierMap.clear();
    // Assuming you have access to a DB connection via productController
    auto conn = productController->getDbConnection()->getConnection();
    auto suppliers = Supplier::getAll(conn);
    for (const auto& s : suppliers) {
        supplierMap[s.getId()] = s.getName();
    }
}

void ProductsPage::loadProducts() {
    allProducts = productController->show();
}

void ProductsPage::applyFilters() {
    QString searchText = searchEdit->text().trimmed().toLower();
    int selectedCategoryId = categoryCombo->currentData().toInt();
    tableWidget->setRowCount(0);
    int row = 0;
    for (const auto& p : allProducts) {
        if (selectedCategoryId != -1 && p.getCategoryId() != selectedCategoryId)
            continue;
        QString name = QString::fromStdString(p.getName()).toLower();
        if (!searchText.isEmpty() && !name.contains(searchText))
            continue;
        QString categoryName = categoryMap.find(p.getCategoryId()) != categoryMap.end() ? QString::fromStdString(categoryMap[p.getCategoryId()]) : "";
        QString supplierName = supplierMap.find(p.getSupplierId()) != supplierMap.end() ? QString::fromStdString(supplierMap[p.getSupplierId()]) : "";
        tableWidget->insertRow(row);
        tableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(p.getId())));
        tableWidget->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(p.getName())));
        tableWidget->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(p.getDescription())));
        tableWidget->setItem(row, 3, new QTableWidgetItem(categoryName));
        tableWidget->setItem(row, 4, new QTableWidgetItem(supplierName));
        tableWidget->setItem(row, 5, new QTableWidgetItem(QString::number(p.getQuantity())));
        tableWidget->setItem(row, 6, new QTableWidgetItem(QString::number(p.getCostPrice(), 'f', 2)));
        tableWidget->setItem(row, 7, new QTableWidgetItem(QString::number(p.getSalePrice(), 'f', 2)));
        tableWidget->setItem(row, 8, new QTableWidgetItem(QString::fromStdString(p.getUnit())));
        tableWidget->setItem(row, 9, new QTableWidgetItem(QString::fromStdString(p.getSku())));
        tableWidget->setItem(row, 10, new QTableWidgetItem(QString::fromStdString(p.getStatus())));
        tableWidget->setItem(row, 11, new QTableWidgetItem(QString::number(p.getWeight(), 'f', 2)));
        tableWidget->setItem(row, 12, new QTableWidgetItem(QString::fromStdString(p.getDimensions())));
        tableWidget->setItem(row, 13, new QTableWidgetItem(QString::fromStdString(p.getImage())));
        tableWidget->setItem(row, 14, new QTableWidgetItem(QString::fromStdString(p.getCreatedAt())));
        tableWidget->setItem(row, 15, new QTableWidgetItem(QString::fromStdString(p.getUpdatedAt())));
        // Set row color based on status (use stronger but not aggressive colors)
        QString status = QString::fromStdString(p.getStatus()).toLower().trimmed();
        if (status == "descontinuado") {
            QColor bgColor(255, 153, 153); // stronger light red
            QColor textColor(80, 0, 0); // dark red text for contrast
            for (int col = 0; col < tableWidget->columnCount(); ++col) {
                if (!tableWidget->item(row, col)) tableWidget->setItem(row, col, new QTableWidgetItem(""));
                tableWidget->item(row, col)->setBackground(bgColor);
                tableWidget->item(row, col)->setForeground(textColor);
            }
        } else if (status == "ativo") {
            QColor bgColor(153, 255, 153); // stronger light green
            QColor textColor(0, 80, 0); // dark green text for contrast
            for (int col = 0; col < tableWidget->columnCount(); ++col) {
                if (!tableWidget->item(row, col)) tableWidget->setItem(row, col, new QTableWidgetItem(""));
                tableWidget->item(row, col)->setBackground(bgColor);
                tableWidget->item(row, col)->setForeground(textColor);
            }
        } else if (status == "inativo") {
            QColor bgColor(255, 255, 153); // stronger light yellow
            QColor textColor(80, 80, 0); // dark yellow text for contrast
            for (int col = 0; col < tableWidget->columnCount(); ++col) {
                if (!tableWidget->item(row, col)) tableWidget->setItem(row, col, new QTableWidgetItem(""));
                tableWidget->item(row, col)->setBackground(bgColor);
                tableWidget->item(row, col)->setForeground(textColor);
            }
        }
        row++;
    }
}

void ProductsPage::onSearchTextChanged(const QString&) {
    applyFilters();
}

void ProductsPage::onCategoryChanged(int) {
    applyFilters();
}

void ProductsPage::onEditProduct(int productId) {
    // Find the product
    auto it = std::find_if(allProducts.begin(), allProducts.end(), [productId](const Product& p) { return p.getId() == productId; });
    if (it == allProducts.end()) return;
    Product product = *it;

    // Get categories
    std::vector<Category> categories = categoryController->list();
    QList<Category> qCategories;
    for (const auto& cat : categories) qCategories.append(cat);

    // Prepare suppliers for the dialog
    QList<std::pair<int, QString>> qSuppliers;
    for (const auto& pair : supplierMap) {
        qSuppliers.append(std::make_pair(pair.first, QString::fromStdString(pair.second)));
    }
    // Open dialog
    EditProductDialog dlg(this);
    dlg.setSuppliers(qSuppliers); // Set suppliers first
    dlg.setProduct(product);
    dlg.setCategories(qCategories);
    if (dlg.exec() == QDialog::Accepted) {
        Product updated = dlg.getProduct();
        productController->update(updated);
        refreshTable();
    }
}

void ProductsPage::onDeleteProduct(int productId) {
    auto it = std::find_if(allProducts.begin(), allProducts.end(), [productId](const Product& p) { return p.getId() == productId; });
    if (it == allProducts.end()) return;
    Product product = *it;
    QMessageBox::StandardButton reply = QMessageBox::question(
        this,
        "Delete Product",
        QString("Are you sure you want to delete '%1'?").arg(QString::fromStdString(product.getName())),
        QMessageBox::Yes|QMessageBox::No
    );
    if (reply == QMessageBox::Yes) {
        productController->remove(productId);
        refreshTable();
    }
}

void ProductsPage::showContextMenu(const QPoint &pos) {
    QModelIndex index = tableWidget->indexAt(pos);
    int row = index.row();
    if (row < 0 || row >= tableWidget->rowCount()) return;
    int productId = tableWidget->item(row, 0)->text().toInt();
    QMenu menu(this);
    QAction* editAction = menu.addAction("Edit");
    QAction* deleteAction = menu.addAction("Delete");
    QAction* selectedAction = menu.exec(tableWidget->viewport()->mapToGlobal(pos));
    if (selectedAction == editAction) {
        onEditProduct(productId);
    } else if (selectedAction == deleteAction) {
        onDeleteProduct(productId);
    }
}

ProductsPage::~ProductsPage() {}
