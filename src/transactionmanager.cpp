#include "transactionmanager.h"

/**
 * @brief Ajoute une transaction à la liste.
 * @param transaction La transaction à ajouter
 */
void CTransactionManager::addTransaction(const CTransaction &transaction)
{
    m_transactions.append(transaction);
}

/**
 * @brief Supprime toutes les transactions.
 */
void CTransactionManager::clear()
{
    m_transactions.clear();
}

/**
 * @brief Retourne le nombre total de transactions enregistrées.
 * @return Le nombre de transactions.
 */
int CTransactionManager::transactionCount() const
{
    return m_transactions.size();
}

/**
 * @brief Calcule le solde total (revenus - dépenses).
 * @return La balance du compte.
 */
double CTransactionManager::totalBalance() const
{
    double balance = 0.0;
    for (const auto &tx : m_transactions) {
        if (tx.type() == CTransaction::Type::Income)
            balance += tx.amount();
        else
            balance -= tx.amount();
    }
    return balance;
}

/**
 * @brief Calcule la somme totale des revenus.
 * @return Le total des transactions de type revenu.
 */
double CTransactionManager::totalIncome() const
{
    double total = 0.0;
    for (const auto &tx : m_transactions) {
        if (tx.type() == CTransaction::Type::Income)
            total += tx.amount();
    }
    return total;
}

/**
 * @brief Calcule la somme totale des dépenses.
 * @return Le total des transactions de type dépense.
 */
double CTransactionManager::totalExpense() const
{
    double total = 0.0;
    for (const auto &tx : m_transactions) {
        if (tx.type() == CTransaction::Type::Expense)
            total += tx.amount();
    }
    return total;
}

/**
 * @brief Retourne toutes les transactions enregistrées.
 * @return Liste constante des transactions.
 */
const QList<CTransaction>& CTransactionManager::transactions() const
{
    return m_transactions;
}

/**
 * @brief Retourne la liste des transactions pour un mois/année donné.
 * @param year Année recherchée
 * @param month Mois recherché (1-12)
 * @return Liste filtrée des transactions du mois/année.
 */
QList<CTransaction> CTransactionManager::transactionsByMonth(int year, int month) const
{
    QList<CTransaction> filtered;
    for (const auto &tx : m_transactions) {
        if (tx.date().year() == year && tx.date().month() == month) {
            filtered.append(tx);
        }
    }
    return filtered;
}

/**
 * @brief Retourne la liste des transactions appartenant à une catégorie donnée.
 * @param category Catégorie recherchée (QString)
 * @return Liste filtrée des transactions de cette catégorie.
 */
QList<CTransaction> CTransactionManager::transactionsByCategory(const QString& category) const
{
    QList<CTransaction> filtered;
    for (const auto &tx : m_transactions) {
        if (tx.category() == category) {
            filtered.append(tx);
        }
    }
    return filtered;
}

/**
 * @brief Retourne la liste des transactions dont le montant est compris dans une plage donnée.
 * @param minAmount Montant minimum (inclus)
 * @param maxAmount Montant maximum (inclus)
 * @return Liste filtrée des transactions.
 */
QList<CTransaction> CTransactionManager::transactionsByAmountRange(double minAmount, double maxAmount) const
{
    QList<CTransaction> filtered;
    for (const auto &tx : m_transactions) {
        if (tx.amount() >= minAmount && tx.amount() <= maxAmount) {
            filtered.append(tx);
        }
    }
    return filtered;
}

/**
 * @brief Supprime la transaction à l'index donné.
 * @param index Index de la transaction à supprimer
 * @return true si la suppression a réussi, false sinon.
 */
bool CTransactionManager::removeTransaction(int index)
{
    if (index < 0 || index >= m_transactions.size())
        return false;
    m_transactions.removeAt(index);
    return true;
}

/**
 * @brief Exporte la liste des transactions au format CSV dans le fichier donné.
 * @param filePath Le chemin du fichier CSV à générer.
 * @return true si l'export a réussi, false sinon.
 */
bool CTransactionManager::exportToCSV(const QString& filePath) const
{
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    QTextStream out(&file);
    // Header CSV
    out << "Type,Amount,Label,Date,Category\n";
    for (const auto& tx : m_transactions) {
        QString typeStr = (tx.type() == CTransaction::Type::Income) ? "Income" : "Expense";
        out << typeStr << ','
            << QString::number(tx.amount()) << ','
            << tx.label() << ','
            << tx.date().toString("yyyy-MM-dd") << ','
            << tx.category() << '\n';
    }
    file.close();
    return true;
}
