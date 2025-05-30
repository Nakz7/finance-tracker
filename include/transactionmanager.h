#ifndef TRANSACTIONMANAGER_H
#define TRANSACTIONMANAGER_H

#include <QList>
#include "transaction.h"

/**
 * @brief La classe CTransactionManager gère une liste de transactions financières.
 *
 * Fournit des méthodes pour ajouter, supprimer, filtrer et résumer les transactions.
 */
class CTransactionManager
{
public:
    /**
     * @brief Constructeur par défaut.
     */
    CTransactionManager() = default;

    /**
     * @brief Ajoute une transaction à la liste.
     * @param transaction La transaction à ajouter
     */
    void addTransaction(const CTransaction &transaction);

    /**
     * @brief Supprime toutes les transactions.
     */
    void clear();

    /**
     * @brief Retourne le nombre total de transactions enregistrées.
     * @return Le nombre de transactions.
     */
    int transactionCount() const;

    /**
     * @brief Calcule le solde total (revenus - dépenses).
     * @return La balance du compte.
     */
    double totalBalance() const;

    /**
     * @brief Calcule la somme totale des revenus.
     * @return Le total des transactions de type revenu.
     */
    double totalIncome() const;

    /**
     * @brief Calcule la somme totale des dépenses.
     * @return Le total des transactions de type dépense.
     */
    double totalExpense() const;

    /**
     * @brief Retourne toutes les transactions enregistrées.
     * @return Liste constante des transactions.
     */
    const QList<CTransaction>& transactions() const;

    /**
     * @brief Retourne la liste des transactions pour un mois/année donné.
     * @param year Année recherchée
     * @param month Mois recherché (1-12)
     * @return Liste filtrée des transactions du mois/année.
     */
    QList<CTransaction> transactionsByMonth(int year, int month) const;

    /**
     * @brief Retourne la liste des transactions appartenant à une catégorie donnée.
     * @param category Catégorie recherchée (QString)
     * @return Liste filtrée des transactions de cette catégorie.
     */
    QList<CTransaction> transactionsByCategory(const QString& category) const;

    /**
     * @brief Retourne la liste des transactions dont le montant est compris dans une plage donnée.
     * @param minAmount Montant minimum (inclus)
     * @param maxAmount Montant maximum (inclus)
     * @return Liste filtrée des transactions.
     */
    QList<CTransaction> transactionsByAmountRange(double minAmount, double maxAmount) const;

    /**
     * @brief Supprime la transaction à l'index donné.
     * @param index Index de la transaction à supprimer
     * @return true si la suppression a réussi, false sinon.
     */
    bool removeTransaction(int index);

private:
    QList<CTransaction> m_transactions;
};

#endif // TRANSACTIONMANAGER_H
