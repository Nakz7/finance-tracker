#ifndef BUDGETMANAGER_H
#define BUDGETMANAGER_H

#include <QList>
#include "budget.h"
#include "transaction.h" // Required for the CheckBudget function

namespace Budget {

/**
 * @brief La classe CBudgetManager gère une collection de budgets.
 *
 * Fournit la logique pour ajouter des budgets et vérifier si les dépenses
 * pour une catégorie donnée dépassent le budget alloué pour un mois spécifique.
 */
class CBudgetManager
{
public:
    /**
     * @brief Constructeur par défaut.
     */
    CBudgetManager() = default;

    /**
     * @brief Ajoute un budget à la collection.
     * @param budget L'objet CBudget à ajouter.
     */
    void addBudget(const CBudget& budget);

    /**
     * @brief Vérifie si les dépenses pour une catégorie et un mois donnés dépassent le budget.
     * @param transactions Une liste de toutes les transactions à considérer.
     * @param newExpense La nouvelle dépense qui vient d'être ajoutée.
     * @return true si le budget est dépassé, false sinon.
     */
    bool isBudgetExceeded(const QList<CTransaction>& transactions, const CTransaction& newExpense) const;

    /**
     * @brief Récupère le budget pour une catégorie et une date spécifiques.
     * @param year L'année du budget.
     * @param month Le mois du budget.
     * @param category La catégorie du budget.
     * @return Un pointeur vers l'objet CBudget correspondant, ou nullptr si non trouvé.
     */
    const CBudget* findBudget(int year, int month, const QString& category) const;


private:
    QList<CBudget> m_budgets; ///< La liste des budgets gérés.
};

} // namespace Budget

#endif // BUDGETMANAGER_H
