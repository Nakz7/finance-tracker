#include "transaction.h"

/**
 * @brief Constructeur d'une transaction.
 */
CTransaction::CTransaction(Type type, double amount, const QString &label, const QDate &date, const QString &category)
    : m_type(type)
    , m_amount(amount)
    , m_label(label)
    , m_date(date)
    , m_category(category)
{
}

CTransaction::Type CTransaction::type() const
{
    return m_type;
}

double CTransaction::amount() const
{
    return m_amount;
}

QString CTransaction::label() const
{
    return m_label;
}

QDate CTransaction::date() const
{
    return m_date;
}

QString CTransaction::category() const
{
    return m_category;
}
