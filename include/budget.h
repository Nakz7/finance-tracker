#ifndef BUDGET_H
#define BUDGET_H

#include <QString>

namespace Budget {

/**
 * @brief La classe CBudget représente un budget mensuel pour une catégorie spécifique.
 *
 * Elle définit un montant maximum alloué pour une catégorie donnée
 * sur une période d'un mois (mois et année).
 */
class CBudget
{
public:
    /**
     * @brief Constructeur de CBudget.
     * @param year L'année du budget.
     * @param month Le mois du budget (1-12).
     * @param category La catégorie concernée par le budget.
     * @param amount Le montant maximum alloué pour le budget.
     */
    CBudget(int year, int month, const QString &category, double amount);

    /**
     * @brief Retourne l'année du budget.
     */
    int year() const;

    /**
     * @brief Retourne le mois du budget.
     */
    int month() const;

    /**
     * @brief Retourne la catégorie du budget.
     */
    QString category() const;

    /**
     * @brief Retourne le montant du budget.
     */
    double amount() const;

private:
    int m_year;         ///< L'année du budget.
    int m_month;        ///< Le mois du budget (1-12).
    QString m_category; ///< La catégorie du budget.
    double m_amount;    ///< Le montant du budget.
};

} // namespace Budget

#endif // BUDGET_H
