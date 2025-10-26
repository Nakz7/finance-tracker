#include <gtest/gtest.h>
#include "budgetmanager.h"
#include "transactionmanager.h" // Using the main transaction manager to hold transactions

using namespace Budget;

class BudgetManagerTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Sample transactions
        tm.addTransaction(Transactions::CTransaction(Transactions::CTransaction::Type::Expense, 100.0, "Groceries", QDate(2024, 7, 5), "Food"));
        tm.addTransaction(Transactions::CTransaction(Transactions::CTransaction::Type::Expense, 50.0, "More Groceries", QDate(2024, 7, 10), "Food"));
        tm.addTransaction(Transactions::CTransaction(Transactions::CTransaction::Type::Expense, 80.0, "Gas", QDate(2024, 7, 12), "Transport"));

        // Sample budget
        bm.addBudget(CBudget(2024, 7, "Food", 200.0));
    }

    Transactions::CTransactionManager tm;
    CBudgetManager bm;
};

TEST_F(BudgetManagerTest, BudgetNotExceeded) {
    // New expense that does NOT exceed the budget (100 + 50 + 40 = 190 <= 200)
    Transactions::CTransaction newExpense(Transactions::CTransaction::Type::Expense, 40.0, "Snacks", QDate(2024, 7, 15), "Food");
    tm.addTransaction(newExpense);

    ASSERT_FALSE(bm.isBudgetExceeded(tm.transactions(), newExpense));
}

TEST_F(BudgetManagerTest, BudgetIsExceeded) {
    // New expense that DOES exceed the budget (100 + 50 + 60 = 210 > 200)
    Transactions::CTransaction newExpense(Transactions::CTransaction::Type::Expense, 60.0, "Extra Snacks", QDate(2024, 7, 18), "Food");
    tm.addTransaction(newExpense);

    ASSERT_TRUE(bm.isBudgetExceeded(tm.transactions(), newExpense));
}

TEST_F(BudgetManagerTest, NoBudgetSet) {
    // New expense in a category with no budget
    Transactions::CTransaction newExpense(Transactions::CTransaction::Type::Expense, 100.0, "Train ticket", QDate(2024, 7, 20), "Transport");
    tm.addTransaction(newExpense);

    ASSERT_FALSE(bm.isBudgetExceeded(tm.transactions(), newExpense));
}

TEST_F(BudgetManagerTest, NotAnExpense) {
    // An income transaction should not trigger budget check
    Transactions::CTransaction newIncome(Transactions::CTransaction::Type::Income, 500.0, "Bonus", QDate(2024, 7, 22), "Food");
    tm.addTransaction(newIncome);

    ASSERT_FALSE(bm.isBudgetExceeded(tm.transactions(), newIncome));
}
