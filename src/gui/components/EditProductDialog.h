#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QPushButton>
#include <QTextEdit>
#include <QDoubleSpinBox>
#include <QLabel>
#include "models/product.h"
#include "models/category.h"

class EditProductDialog : public QDialog {
    Q_OBJECT
public:
    explicit EditProductDialog(QWidget *parent = nullptr);
    ~EditProductDialog();
    void setProduct(const Product &product);
    void setCategories(const QList<Category> &categories);
    void setSuppliers(const QList<std::pair<int, QString>> &suppliers);
    Product getProduct() const;

signals:
    void productSaved(const Product &product);

private slots:
    void onSaveClicked();

private:
    QLineEdit *nameEdit;
    QTextEdit *descriptionEdit;
    QComboBox *categoryCombo;
    QSpinBox *quantitySpin;
    QDoubleSpinBox *costPriceSpin;
    QDoubleSpinBox *salePriceSpin;
    QLineEdit *unitEdit;
    QLineEdit *skuEdit;
    QComboBox *statusCombo;
    QDoubleSpinBox *weightSpin;
    QLineEdit *dimensionsEdit;
    QLineEdit *imageEdit;
    QLabel *createdAtLabel;
    QLabel *updatedAtLabel;
    QPushButton *saveButton;
    QPushButton *cancelButton;
    int productId;
    int productCategoryId;
    std::string createdAt;
    std::string updatedAt;
    QComboBox *supplierCombo;
    QList<std::pair<int, QString>> supplierList;

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;
};
