#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <QString>
#include <QDate>

/**
 * @brief La classe CTransaction représente une opération financière (revenu ou dépense).
 */
class CTransaction
{
public:
    /**
     * @brief Type de transaction : revenu ou dépense.
     */
    enum class Type {
        Income,  ///< Revenu
        Expense  ///< Dépense
    };

    /**
         * @brief Constructeur d'une transaction.
         * @param type Le type (Income ou Expense)
         * @param amount Le montant
         * @param label L'intitulé de la transaction
         * @param date La date (défaut : date du jour)
         * @param category La catégorie (défaut : chaîne vide)
         */
    CTransaction(Type type, double amount, const QString &label, const QDate &date = QDate::currentDate(), const QString &category = "");

    /**
     * @brief Retourne le type de la transaction.
     */
    Type type() const;

    /**
     * @brief Retourne le montant de la transaction.
     */
    double amount() const;

    /**
     * @brief Retourne l'intitulé (libellé) de la transaction.
     */
    QString label() const;

    /**
     * @brief Retourne la date de la transaction.
     */
    QDate date() const;

    /**
     * @brief Retourne la catégorie de la transaction.
     */
    QString category() const;

private:
    Type m_type; ///< Type de la transaction
    double m_amount; ///< Total de la transaction
    QString m_label; ///< Label de la transaction
    QDate m_date; ///< Date de la transaction
    QString m_category; ///< Catégorie de la transaction
};



#endif // TRANSACTION_H
