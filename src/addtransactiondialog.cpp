#include "addtransactiondialog.h"
#include <QtWidgets>
#include <QFormLayout>
#include <QDialogButtonBox>

namespace UI {

CAddTransactionDialog::CAddTransactionDialog(QWidget *parent)
    : QDialog(parent)
{
    setupUi();
}

void CAddTransactionDialog::setupUi()
{
    setWindowTitle("Add New Transaction");

    QFormLayout *formLayout = new QFormLayout(this);

    // --- Form Widgets ---
    m_typeComboBox = new QComboBox();
    m_typeComboBox->addItem("Expense", static_cast<int>(Transactions::CTransaction::Type::Expense));
    m_typeComboBox->addItem("Income", static_cast<int>(Transactions::CTransaction::Type::Income));

    m_amountSpinBox = new QDoubleSpinBox();
    m_amountSpinBox->setRange(0.01, 1000000.0);
    m_amountSpinBox->setDecimals(2);
    m_amountSpinBox->setPrefix("$ ");

    m_labelLineEdit = new QLineEdit();
    m_dateEdit = new QDateEdit(QDate::currentDate());
    m_dateEdit->setCalendarPopup(true);
    m_categoryLineEdit = new QLineEdit();

    formLayout->addRow("Type:", m_typeComboBox);
    formLayout->addRow("Amount:", m_amountSpinBox);
    formLayout->addRow("Label:", m_labelLineEdit);
    formLayout->addRow("Date:", m_dateEdit);
    formLayout->addRow("Category:", m_categoryLineEdit);

    // --- Buttons ---
    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    formLayout->addRow(buttonBox);

    setLayout(formLayout);
}

Transactions::CTransaction CAddTransactionDialog::getTransaction() const
{
    const Transactions::CTransaction::Type type = static_cast<Transactions::CTransaction::Type>(m_typeComboBox->currentData().toInt());
    const double amount = m_amountSpinBox->value();
    const QString label = m_labelLineEdit->text();
    const QDate date = m_dateEdit->date();
    const QString category = m_categoryLineEdit->text();

    return Transactions::CTransaction(type, amount, label, date, category);
}

} // namespace UI
