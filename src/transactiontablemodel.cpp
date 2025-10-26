#include "transactiontablemodel.h"

TransactionTableModel::TransactionTableModel(Transactions::CTransactionManager *manager, QObject *parent)
    : QAbstractTableModel(parent), m_manager(manager)
{}

TransactionTableModel::~TransactionTableModel() {}

int TransactionTableModel::rowCount(const QModelIndex &/*parent*/) const
{
    return m_manager ? m_manager->transactionCount() : 0;
}

int TransactionTableModel::columnCount(const QModelIndex &/*parent*/) const
{
    return 5; // Type, Amount, Label, Date, Category
}

QVariant TransactionTableModel::data(const QModelIndex &index, int role) const
{
    if (!m_manager || role != Qt::DisplayRole || !index.isValid())
        return QVariant();

    const auto &transactions = m_manager->transactions();
    if (index.row() < 0 || index.row() >= transactions.size())
        return QVariant();

    const Transactions::CTransaction &tx = transactions[index.row()];
    switch (index.column()) {
    case 0: return (tx.type() == Transactions::CTransaction::Type::Income) ? "Income" : "Expense";
    case 1: return tx.amount();
    case 2: return tx.label();
    case 3: return tx.date().toString("yyyy-MM-dd");
    case 4: return tx.category();
    default: return QVariant();
    }
}

QVariant TransactionTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation != Qt::Horizontal || role != Qt::DisplayRole)
        return QVariant();

    switch (section) {
    case 0: return "Type";
    case 1: return "Amount";
    case 2: return "Label";
    case 3: return "Date";
    case 4: return "Category";
    default: return QVariant();
    }
}
