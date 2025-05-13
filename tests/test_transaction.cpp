#include <gtest/gtest.h>
#include "transaction.h"

TEST(TransactionTest, CanCreateIncomeTransaction)
{
    Transaction t(Transaction::Type::Income, 1500.0, "Salaire");

    EXPECT_EQ(t.type(), Transaction::Type::Income);
    EXPECT_DOUBLE_EQ(t.amount(), 1500.0);
    EXPECT_EQ(t.label(), "Salaire");
    EXPECT_TRUE(t.date().isValid());
}

TEST(TransactionTest, CanCreateExpenseTransaction)
{
    Transaction t(Transaction::Type::Expense, 60.5, "Courses", QDate(2024, 12, 15));

    EXPECT_EQ(t.type(), Transaction::Type::Expense);
    EXPECT_DOUBLE_EQ(t.amount(), 60.5);
    EXPECT_EQ(t.label(), "Courses");
    EXPECT_EQ(t.date(), QDate(2024, 12, 15));
}
