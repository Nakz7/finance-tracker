#include <gtest/gtest.h>
#include "transaction.h"

/**
 * @brief Teste la création d’une transaction de revenu.
 */
TEST(TransactionTest, CanCreateIncomeTransaction)
{
    CTransaction t(CTransaction::Type::Income, 1500.0, "Salaire");

    EXPECT_EQ(t.type(), CTransaction::Type::Income);
    EXPECT_DOUBLE_EQ(t.amount(), 1500.0);
    EXPECT_EQ(t.label(), "Salaire");
    EXPECT_TRUE(t.date().isValid());
}

/**
 * @brief Teste la création d’une transaction de dépense.
 */
TEST(TransactionTest, CanCreateExpenseTransaction)
{
    CTransaction t(CTransaction::Type::Expense, 60.5, "Courses", QDate(2024, 12, 15));

    EXPECT_EQ(t.type(), CTransaction::Type::Expense);
    EXPECT_DOUBLE_EQ(t.amount(), 60.5);
    EXPECT_EQ(t.label(), "Courses");
    EXPECT_EQ(t.date(), QDate(2024, 12, 15));
}

/**
 * @brief Teste la création d’une transaction avec catégorie.
 */
TEST(TransactionTest, CanCreateTransactionWithCategory)
{
    CTransaction t(CTransaction::Type::Expense, 120.0, "Courses", QDate(2024, 6, 3), "Alimentation");
    EXPECT_EQ(t.type(), CTransaction::Type::Expense);
    EXPECT_DOUBLE_EQ(t.amount(), 120.0);
    EXPECT_EQ(t.label(), "Courses");
    EXPECT_EQ(t.date(), QDate(2024, 6, 3));
    EXPECT_EQ(t.category(), "Alimentation");
}

/**
 * @brief Teste la création d’une transaction sans catégorie (valeur par défaut).
 */
TEST(TransactionTest, CanCreateTransactionWithDefaultCategory)
{
    CTransaction t(CTransaction::Type::Income, 1000.0, "Salaire");
    EXPECT_EQ(t.category(), "");
}
