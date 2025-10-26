#include <gtest/gtest.h>
#include <QFile>
#include <QTextStream>
#include "transactionmanager.h"

/**
 * @brief Teste l’ajout et le comptage du nombres de transactions.
 */
TEST(TransactionManagerTest, AddAndCountTransactions)
{
    Transactions::CTransactionManager manager;
    EXPECT_EQ(manager.transactionCount(), 0);

    manager.addTransaction(Transactions::CTransaction(Transactions::CTransaction::Type::Income, 1000.0, "Salaire"));
    manager.addTransaction(Transactions::CTransaction(Transactions::CTransaction::Type::Expense, 200.0, "Courses"));

    EXPECT_EQ(manager.transactionCount(), 2);
}

/**
 * @brief Teste le calcul de balance du compte.
 */
TEST(TransactionManagerTest, CalculateBalance)
{
    Transactions::CTransactionManager manager;
    manager.addTransaction(Transactions::CTransaction(Transactions::CTransaction::Type::Income, 1000.0, "Salaire"));
    manager.addTransaction(Transactions::CTransaction(Transactions::CTransaction::Type::Expense, 350.0, "Loyer"));

    EXPECT_DOUBLE_EQ(manager.totalBalance(), 650.0);
}

/**
 * @brief Teste la méthode clear() de CTransactionManager.
 */
TEST(TransactionManagerTest, ClearTransactions)
{
    Transactions::CTransactionManager manager;
    manager.addTransaction(Transactions::CTransaction(Transactions::CTransaction::Type::Income, 1000.0, "Salaire"));
    manager.addTransaction(Transactions::CTransaction(Transactions::CTransaction::Type::Expense, 200.0, "Courses"));
    ASSERT_EQ(manager.transactionCount(), 2);

    manager.clear();
    EXPECT_EQ(manager.transactionCount(), 0);
    EXPECT_TRUE(manager.transactions().isEmpty());
}

/**
 * @brief Teste l’accès à la liste des transactions.
 */
TEST(TransactionManagerTest, GetAllTransactions)
{
    Transactions::CTransactionManager manager;
    Transactions::CTransaction t1(Transactions::CTransaction::Type::Income, 1000.0, "Salaire");
    Transactions::CTransaction t2(Transactions::CTransaction::Type::Expense, 50.0, "Courses");
    manager.addTransaction(t1);
    manager.addTransaction(t2);

    const QList<Transactions::CTransaction>& txs = manager.transactions();
    ASSERT_EQ(txs.size(), 2);
    EXPECT_EQ(txs[0].label(), "Salaire");
    EXPECT_EQ(txs[1].label(), "Courses");
}

/**
 * @brief Teste la somme des revenus.
 */
TEST(TransactionManagerTest, TotalIncome)
{
    Transactions::CTransactionManager manager;
    manager.addTransaction(Transactions::CTransaction(Transactions::CTransaction::Type::Income, 1000.0, "Salaire"));
    manager.addTransaction(Transactions::CTransaction(Transactions::CTransaction::Type::Income, 150.0, "Remboursement"));
    manager.addTransaction(Transactions::CTransaction(Transactions::CTransaction::Type::Expense, 100.0, "Courses"));

    EXPECT_DOUBLE_EQ(manager.totalIncome(), 1150.0);
}

/**
 * @brief Teste la récupération des transactions d'un mois donné.
 */
TEST(TransactionManagerTest, TransactionsByMonth)
{
    Transactions::CTransactionManager manager;
    manager.addTransaction(Transactions::CTransaction(Transactions::CTransaction::Type::Income, 1000.0, "Salaire", QDate(2024, 6, 1)));
    manager.addTransaction(Transactions::CTransaction(Transactions::CTransaction::Type::Expense, 120.0, "Courses", QDate(2024, 6, 3)));
    manager.addTransaction(Transactions::CTransaction(Transactions::CTransaction::Type::Expense, 80.0, "Essence", QDate(2024, 5, 27)));
    manager.addTransaction(Transactions::CTransaction(Transactions::CTransaction::Type::Income, 200.0, "Cadeau", QDate(2024, 7, 15)));

    QList<Transactions::CTransaction> juneTxs = manager.transactionsByMonth(2024, 6);
    ASSERT_EQ(juneTxs.size(), 2);
    EXPECT_EQ(juneTxs[0].label(), "Salaire");
    EXPECT_EQ(juneTxs[1].label(), "Courses");

    QList<Transactions::CTransaction> julyTxs = manager.transactionsByMonth(2024, 7);
    ASSERT_EQ(julyTxs.size(), 1);
    EXPECT_EQ(julyTxs[0].label(), "Cadeau");
}

/**
 * @brief Teste le calcul du total des dépenses.
 */
TEST(TransactionManagerTest, TotalExpense)
{
    Transactions::CTransactionManager manager;
    manager.addTransaction(Transactions::CTransaction(Transactions::CTransaction::Type::Income, 900.0, "Salaire"));
    manager.addTransaction(Transactions::CTransaction(Transactions::CTransaction::Type::Expense, 200.0, "Courses"));
    manager.addTransaction(Transactions::CTransaction(Transactions::CTransaction::Type::Expense, 75.5, "Essence"));

    EXPECT_DOUBLE_EQ(manager.totalExpense(), 275.5);
}

/**
 * @brief Teste le filtrage des transactions par catégorie.
 */
TEST(TransactionManagerTest, TransactionsByCategory)
{
    Transactions::CTransactionManager manager;
    manager.addTransaction(Transactions::CTransaction(Transactions::CTransaction::Type::Income, 1200.0, "Salaire", QDate(2024, 6, 1), "Travail"));
    manager.addTransaction(Transactions::CTransaction(Transactions::CTransaction::Type::Expense, 150.0, "Courses", QDate(2024, 6, 3), "Alimentation"));
    manager.addTransaction(Transactions::CTransaction(Transactions::CTransaction::Type::Expense, 50.0, "Essence", QDate(2024, 6, 10), "Transport"));
    manager.addTransaction(Transactions::CTransaction(Transactions::CTransaction::Type::Income, 200.0, "Vente", QDate(2024, 6, 15), "Divers"));
    manager.addTransaction(Transactions::CTransaction(Transactions::CTransaction::Type::Expense, 60.0, "Dîner", QDate(2024, 6, 20), "Alimentation"));

    // Test catégorie "Alimentation"
    QList<Transactions::CTransaction> alimentationTxs = manager.transactionsByCategory("Alimentation");
    ASSERT_EQ(alimentationTxs.size(), 2);
    EXPECT_EQ(alimentationTxs[0].label(), "Courses");
    EXPECT_EQ(alimentationTxs[1].label(), "Dîner");

    // Test catégorie "Travail"
    QList<Transactions::CTransaction> travailTxs = manager.transactionsByCategory("Travail");
    ASSERT_EQ(travailTxs.size(), 1);
    EXPECT_EQ(travailTxs[0].label(), "Salaire");

    // Test catégorie inexistante
    QList<Transactions::CTransaction> santeTxs = manager.transactionsByCategory("Santé");
    ASSERT_TRUE(santeTxs.isEmpty());
}

/**
 * @brief Teste la suppression d'une transaction par index.
 */
TEST(TransactionManagerTest, RemoveTransactionByIndex)
{
    Transactions::CTransactionManager manager;
    manager.addTransaction(Transactions::CTransaction(Transactions::CTransaction::Type::Income, 800.0, "Salaire"));
    manager.addTransaction(Transactions::CTransaction(Transactions::CTransaction::Type::Expense, 50.0, "Courses"));
    manager.addTransaction(Transactions::CTransaction(Transactions::CTransaction::Type::Expense, 30.0, "Café"));

    EXPECT_EQ(manager.transactionCount(), 3);

    // Suppression de la transaction d'indice 1 ("Courses")
    bool removed = manager.removeTransaction(1);
    EXPECT_TRUE(removed);
    EXPECT_EQ(manager.transactionCount(), 2);
    EXPECT_EQ(manager.transactions()[0].label(), "Salaire");
    EXPECT_EQ(manager.transactions()[1].label(), "Café");

    // Suppression d'un index invalide
    removed = manager.removeTransaction(5);
    EXPECT_FALSE(removed);
    EXPECT_EQ(manager.transactionCount(), 2);
}

/**
 * @brief Teste le filtrage des transactions par plage de montants.
 */
TEST(TransactionManagerTest, TransactionsByAmountRange)
{
    Transactions::CTransactionManager manager;
    manager.addTransaction(Transactions::CTransaction(Transactions::CTransaction::Type::Expense, 10.0, "Café"));
    manager.addTransaction(Transactions::CTransaction(Transactions::CTransaction::Type::Expense, 250.0, "Vacances"));
    manager.addTransaction(Transactions::CTransaction(Transactions::CTransaction::Type::Income, 1500.0, "Salaire"));
    manager.addTransaction(Transactions::CTransaction(Transactions::CTransaction::Type::Income, 70.0, "Vente", QDate::currentDate(), "Divers"));

    // Transactions entre 50 et 300 (inclus)
    QList<Transactions::CTransaction> txs = manager.transactionsByAmountRange(50.0, 300.0);
    ASSERT_EQ(txs.size(), 2);
    EXPECT_EQ(txs[0].label(), "Vacances");
    EXPECT_EQ(txs[1].label(), "Vente");

    // Transactions entre 1 et 20
    QList<Transactions::CTransaction> txsLow = manager.transactionsByAmountRange(1.0, 20.0);
    ASSERT_EQ(txsLow.size(), 1);
    EXPECT_EQ(txsLow[0].label(), "Café");

    // Transactions entre 2000 et 3000
    QList<Transactions::CTransaction> txsHigh = manager.transactionsByAmountRange(2000.0, 3000.0);
    ASSERT_TRUE(txsHigh.isEmpty());
}

/**
 * @brief Teste le filtrage des transactions par plage de dates.
 */
TEST(TransactionManagerTest, TransactionsByDateRange)
{
    Transactions::CTransactionManager manager;
    manager.addTransaction(Transactions::CTransaction(Transactions::CTransaction::Type::Income, 1000.0, "Salaire", QDate(2024, 6, 1)));
    manager.addTransaction(Transactions::CTransaction(Transactions::CTransaction::Type::Expense, 120.0, "Courses", QDate(2024, 6, 15)));
    manager.addTransaction(Transactions::CTransaction(Transactions::CTransaction::Type::Expense, 80.0, "Essence", QDate(2024, 5, 27)));
    manager.addTransaction(Transactions::CTransaction(Transactions::CTransaction::Type::Income, 200.0, "Cadeau", QDate(2024, 6, 30)));

    QDate from(2024, 6, 1);
    QDate to(2024, 6, 30);
    QList<Transactions::CTransaction> juneTxs = manager.transactionsByDateRange(from, to);
    ASSERT_EQ(juneTxs.size(), 3);
}

/**
 * @brief Teste l’export des transactions au format CSV.
 */
TEST(TransactionManagerTest, ExportToCSV)
{
    Transactions::CTransactionManager manager;
    manager.addTransaction(Transactions::CTransaction(Transactions::CTransaction::Type::Income, 1200.0, "Salaire", QDate(2024, 6, 1), "Travail"));
    manager.addTransaction(Transactions::CTransaction(Transactions::CTransaction::Type::Expense, 150.0, "Courses", QDate(2024, 6, 3), "Alimentation"));

    QString tmpFile = "test_transactions.csv";
    ASSERT_TRUE(manager.exportToCSV(tmpFile));

    QFile file(tmpFile);
    ASSERT_TRUE(file.open(QIODevice::ReadOnly | QIODevice::Text));
    QTextStream in(&file);
    QString content = in.readAll();
    file.close();
    file.remove();  // Nettoyage du fichier temporaire

    // Vérifie que le header et les transactions sont présents
    EXPECT_TRUE(content.contains("Type,Amount,Label,Date,Category"));
    EXPECT_TRUE(content.contains("Income,1200.0,Salaire,2024-06-01,Travail"));
    EXPECT_TRUE(content.contains("Expense,150.0,Courses,2024-06-03,Alimentation"));
}
