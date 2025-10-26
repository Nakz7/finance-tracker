#include <gtest/gtest.h>
#include "budget.h"

using namespace Budget;

TEST(BudgetTest, CanCreateBudgetAndGetValue) {
    CBudget budget(2024, 7, "Food", 500.0);

    ASSERT_EQ(budget.year(), 2024);
    ASSERT_EQ(budget.month(), 7);
    ASSERT_EQ(budget.category().toStdString(), "Food");
    ASSERT_DOUBLE_EQ(budget.amount(), 500.0);
}
