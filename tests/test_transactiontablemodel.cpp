#include <gtest/gtest.h>
#include "transactionmanager.h"
#include "transactiontablemodel.h"
#include <QModelIndex>
#include <QStringList>

/**
 * @brief Teste l’initialisation et la lecture du TableModel custom.
 */
TEST(TransactionTableModelTest, BasicModelData)
{
    Transactions::CTransactionManager manager;
    manager.addTransaction(Transactions::CTransaction(Transactions::CTransaction::Type::Income, 1200.0, "Salaire", QDate(2024, 6, 1), "Travail"));
    manager.addTransaction(Transactions::CTransaction(Transactions::CTransaction::Type::Expense, 150.0, "Courses", QDate(2024, 6, 3), "Alimentation"));

    TransactionTableModel model(&manager);

    // Nombre de lignes/colonnes
    EXPECT_EQ(model.rowCount(), 2);
    EXPECT_EQ(model.columnCount(), 5);

    // Vérifie les headers
    EXPECT_EQ(model.headerData(0, Qt::Horizontal, Qt::DisplayRole).toString(), "Type");
    EXPECT_EQ(model.headerData(1, Qt::Horizontal, Qt::DisplayRole).toString(), "Amount");
    EXPECT_EQ(model.headerData(2, Qt::Horizontal, Qt::DisplayRole).toString(), "Label");
    EXPECT_EQ(model.headerData(3, Qt::Horizontal, Qt::DisplayRole).toString(), "Date");
    EXPECT_EQ(model.headerData(4, Qt::Horizontal, Qt::DisplayRole).toString(), "Category");

    // Vérifie les données de la première ligne
    EXPECT_EQ(model.data(model.index(0, 0)).toString(), "Income");
    EXPECT_EQ(model.data(model.index(0, 1)).toDouble(), 1200.0);
    EXPECT_EQ(model.data(model.index(0, 2)).toString(), "Salaire");
    EXPECT_EQ(model.data(model.index(0, 3)).toString(), "2024-06-01");
    EXPECT_EQ(model.data(model.index(0, 4)).toString(), "Travail");

    // Vérifie les données de la deuxième ligne
    EXPECT_EQ(model.data(model.index(1, 0)).toString(), "Expense");
    EXPECT_EQ(model.data(model.index(1, 1)).toDouble(), 150.0);
    EXPECT_EQ(model.data(model.index(1, 2)).toString(), "Courses");
    EXPECT_EQ(model.data(model.index(1, 3)).toString(), "2024-06-03");
    EXPECT_EQ(model.data(model.index(1, 4)).toString(), "Alimentation");
}
