#include "budget.h"

namespace Budget {

CBudget::CBudget(int year, int month, const QString &category, double amount)
    : m_year(year), m_month(month), m_category(category), m_amount(amount)
{
}

int CBudget::year() const
{
    return m_year;
}

int CBudget::month() const
{
    return m_month;
}

QString CBudget::category() const
{
    return m_category;
}

double CBudget::amount() const
{
    return m_amount;
}

} // namespace Budget
