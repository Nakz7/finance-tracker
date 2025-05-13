#include "transaction.h"

Transaction::Transaction(Type type, double amount, const QString &label, const QDate &date)
    : m_type(type)
    , m_amount(amount)
    , m_label(label)
    , m_date(date)
{
}

Transaction::Type Transaction::type() const
{
    return m_type;
}

double Transaction::amount() const
{
    return m_amount;
}

QString Transaction::label() const
{
    return m_label;
}

QDate Transaction::date() const
{
    return m_date;
}
