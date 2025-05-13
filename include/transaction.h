#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <QString>
#include <QDate>

class Transaction
{
public:
    enum class Type {
        Income,
        Expense
    };

    Transaction(Type type, double amount, const QString &label, const QDate &date = QDate::currentDate());

    Type type() const;
    double amount() const;
    QString label() const;
    QDate date() const;

private:
    Type m_type;
    double m_amount;
    QString m_label;
    QDate m_date;
};

#endif // TRANSACTION_H
