#include "budgetmanager.h"
#include <numeric>

namespace Budget {

void CBudgetManager::addBudget(const CBudget& budget)
{
    m_budgets.append(budget);
}

const CBudget* CBudgetManager::findBudget(int year, int month, const QString& category) const
{
    for (const auto& budget : m_budgets) {
        if (budget.year() == year && budget.month() == month && budget.category() == category) {
            return &budget;
        }
    }
    return nullptr;
}

bool CBudgetManager::isBudgetExceeded(const QList<Transactions::CTransaction>& transactions, const Transactions::CTransaction& newExpense) const
{
    // Ensure the new transaction is actually an expense
    if (newExpense.type() != Transactions::CTransaction::Type::Expense) {
        return false;
    }

    const int year = newExpense.date().year();
    const int month = newExpense.date().month();
    const QString category = newExpense.category();

    // Find the budget for the given category and period
    const CBudget* budget = findBudget(year, month, category);
    if (!budget) {
        // No budget set for this category, so it can't be exceeded
        return false;
    }

    // Calculate total expenses for the period and category
    double totalExpenses = 0.0;
    for (const auto& t : transactions) {
        if (t.date().year() == year && t.date().month() == month && t.category() == category && t.type() == Transactions::CTransaction::Type::Expense) {
            totalExpenses += t.amount();
        }
    }

    // The check includes the new expense, which is assumed to be already in the list.
    return totalExpenses > budget->amount();
}

} // namespace Budget
