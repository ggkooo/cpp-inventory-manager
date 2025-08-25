#include "EditProductDialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QEvent>
#include <QMouseEvent>

EditProductDialog::EditProductDialog(QWidget *parent) : QDialog(parent), productId(-1) {
    setWindowTitle("Edit Product");
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Name
    QHBoxLayout *nameLayout = new QHBoxLayout;
    nameLayout->addWidget(new QLabel("Name:"));
    nameEdit = new QLineEdit;
    nameLayout->addWidget(nameEdit);
    mainLayout->addLayout(nameLayout);

    // Description
    QHBoxLayout *descLayout = new QHBoxLayout;
    descLayout->addWidget(new QLabel("Description:"));
    descriptionEdit = new QTextEdit;
    descriptionEdit->setFixedHeight(40);
    descLayout->addWidget(descriptionEdit);
    mainLayout->addLayout(descLayout);

    // Category
    QHBoxLayout *catLayout = new QHBoxLayout;
    catLayout->addWidget(new QLabel("Category:"));
    categoryCombo = new QComboBox;
    catLayout->addWidget(categoryCombo);
    mainLayout->addLayout(catLayout);

    // Quantity
    QHBoxLayout *qtyLayout = new QHBoxLayout;
    qtyLayout->addWidget(new QLabel("Quantity:"));
    quantitySpin = new QSpinBox;
    quantitySpin->setMinimum(0);
    quantitySpin->setMaximum(1e6);
    qtyLayout->addWidget(quantitySpin);
    mainLayout->addLayout(qtyLayout);

    // Cost Price
    QHBoxLayout *costLayout = new QHBoxLayout;
    costLayout->addWidget(new QLabel("Cost Price:"));
    costPriceSpin = new QDoubleSpinBox;
    costPriceSpin->setMinimum(0);
    costPriceSpin->setMaximum(1e9);
    costPriceSpin->setDecimals(2);
    costLayout->addWidget(costPriceSpin);
    mainLayout->addLayout(costLayout);

    // Sale Price
    QHBoxLayout *saleLayout = new QHBoxLayout;
    saleLayout->addWidget(new QLabel("Sale Price:"));
    salePriceSpin = new QDoubleSpinBox;
    salePriceSpin->setMinimum(0);
    salePriceSpin->setMaximum(1e9);
    salePriceSpin->setDecimals(2);
    saleLayout->addWidget(salePriceSpin);
    mainLayout->addLayout(saleLayout);

    // Unit
    QHBoxLayout *unitLayout = new QHBoxLayout;
    unitLayout->addWidget(new QLabel("Unit:"));
    unitEdit = new QLineEdit;
    unitLayout->addWidget(unitEdit);
    mainLayout->addLayout(unitLayout);

    // SKU
    QHBoxLayout *skuLayout = new QHBoxLayout;
    skuLayout->addWidget(new QLabel("SKU:"));
    skuEdit = new QLineEdit;
    skuLayout->addWidget(skuEdit);
    mainLayout->addLayout(skuLayout);

    // Supplier (ComboBox)
    QHBoxLayout *supplierLayout = new QHBoxLayout;
    supplierLayout->addWidget(new QLabel("Supplier:"));
    supplierCombo = new QComboBox;
    supplierCombo->setFocusPolicy(Qt::StrongFocus);
    supplierCombo->installEventFilter(this);
    supplierLayout->addWidget(supplierCombo);
    mainLayout->addLayout(supplierLayout);

    // Status
    QHBoxLayout *statusLayout = new QHBoxLayout;
    statusLayout->addWidget(new QLabel("Status:"));
    statusCombo = new QComboBox;
    statusCombo->addItem("ativo");
    statusCombo->addItem("inativo");
    statusCombo->addItem("descontinuado");
    statusLayout->addWidget(statusCombo);
    mainLayout->addLayout(statusLayout);

    // Weight
    QHBoxLayout *weightLayout = new QHBoxLayout;
    weightLayout->addWidget(new QLabel("Weight:"));
    weightSpin = new QDoubleSpinBox;
    weightSpin->setMinimum(0);
    weightSpin->setMaximum(1e6);
    weightSpin->setDecimals(2);
    weightLayout->addWidget(weightSpin);
    mainLayout->addLayout(weightLayout);

    // Dimensions
    QHBoxLayout *dimLayout = new QHBoxLayout;
    dimLayout->addWidget(new QLabel("Dimensions:"));
    dimensionsEdit = new QLineEdit;
    dimLayout->addWidget(dimensionsEdit);
    mainLayout->addLayout(dimLayout);

    // Image
    QHBoxLayout *imageLayout = new QHBoxLayout;
    imageLayout->addWidget(new QLabel("Image:"));
    imageEdit = new QLineEdit;
    imageLayout->addWidget(imageEdit);
    mainLayout->addLayout(imageLayout);

    // Created At (read-only)
    QHBoxLayout *createdAtLayout = new QHBoxLayout;
    createdAtLayout->addWidget(new QLabel("Created At:"));
    createdAtLabel = new QLabel;
    createdAtLayout->addWidget(createdAtLabel);
    mainLayout->addLayout(createdAtLayout);

    // Updated At (read-only)
    QHBoxLayout *updatedAtLayout = new QHBoxLayout;
    updatedAtLayout->addWidget(new QLabel("Updated At:"));
    updatedAtLabel = new QLabel;
    updatedAtLayout->addWidget(updatedAtLabel);
    mainLayout->addLayout(updatedAtLayout);

    // Buttons
    QHBoxLayout *btnLayout = new QHBoxLayout;
    saveButton = new QPushButton("Save");
    cancelButton = new QPushButton("Cancel");
    btnLayout->addWidget(saveButton);
    btnLayout->addWidget(cancelButton);
    mainLayout->addLayout(btnLayout);

    connect(saveButton, &QPushButton::clicked, this, &EditProductDialog::onSaveClicked);
    connect(cancelButton, &QPushButton::clicked, this, &EditProductDialog::reject);
}

EditProductDialog::~EditProductDialog() {}

void EditProductDialog::setProduct(const Product &product) {
    productId = product.getId();
    productCategoryId = product.getCategoryId();
    nameEdit->setText(QString::fromStdString(product.getName()));
    descriptionEdit->setText(QString::fromStdString(product.getDescription()));
    quantitySpin->setValue(product.getQuantity());
    costPriceSpin->setValue(product.getCostPrice());
    salePriceSpin->setValue(product.getSalePrice());
    unitEdit->setText(QString::fromStdString(product.getUnit()));
    skuEdit->setText(QString::fromStdString(product.getSku()));
    // Set supplier combo
    int supplierIdx = supplierCombo->findData(product.getSupplierId());
    if (supplierIdx >= 0) supplierCombo->setCurrentIndex(supplierIdx);
    int statusIdx = statusCombo->findText(QString::fromStdString(product.getStatus()));
    if (statusIdx >= 0) statusCombo->setCurrentIndex(statusIdx);
    weightSpin->setValue(product.getWeight());
    dimensionsEdit->setText(QString::fromStdString(product.getDimensions()));
    imageEdit->setText(QString::fromStdString(product.getImage()));
    createdAt = product.getCreatedAt();
    updatedAt = product.getUpdatedAt();
    createdAtLabel->setText(QString::fromStdString(createdAt));
    updatedAtLabel->setText(QString::fromStdString(updatedAt));
}

void EditProductDialog::setCategories(const QList<Category> &categories) {
    categoryCombo->clear();
    int idx = 0, selectedIdx = -1;
    for (const auto &cat : categories) {
        categoryCombo->addItem(QString::fromStdString(cat.getName()), cat.getId());
        if (cat.getId() == productCategoryId) selectedIdx = idx; // Compare with productCategoryId
        ++idx;
    }
    if (selectedIdx >= 0)
        categoryCombo->setCurrentIndex(selectedIdx);
}

void EditProductDialog::setSuppliers(const QList<std::pair<int, QString>> &suppliers) {
    supplierList = suppliers;
    supplierCombo->clear();
    for (const auto &pair : suppliers) {
        supplierCombo->addItem(pair.second, pair.first);
    }
}

Product EditProductDialog::getProduct() const {
    Product product(
        productId,
        nameEdit->text().toStdString(),
        descriptionEdit->toPlainText().toStdString(),
        categoryCombo->currentData().toInt(),
        quantitySpin->value(),
        costPriceSpin->value(),
        salePriceSpin->value(),
        unitEdit->text().toStdString(),
        skuEdit->text().toStdString(),
        supplierCombo->currentData().toInt(),
        statusCombo->currentText().toStdString(),
        weightSpin->value(),
        dimensionsEdit->text().toStdString(),
        imageEdit->text().toStdString(),
        createdAt,
        updatedAt
    );
    return product;
}

void EditProductDialog::onSaveClicked() {
    emit productSaved(getProduct());
    accept();
}

bool EditProductDialog::eventFilter(QObject *obj, QEvent *event) {
    if (obj == supplierCombo && event->type() == QEvent::MouseButtonPress) {
        supplierCombo->showPopup();
        return true;
    }
    return QDialog::eventFilter(obj, event);
}
