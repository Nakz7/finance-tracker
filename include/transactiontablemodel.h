#ifndef TRANSACTIONTABLEMODEL_H
#define TRANSACTIONTABLEMODEL_H

#include <QAbstractTableModel>
#include "transactionmanager.h"

/**
 * @brief Modèle Qt personnalisé pour l’affichage des transactions dans une vue tabulaire.
 */
class TransactionTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    /**
     * @brief Constructeur.
     * @param manager Pointeur vers le gestionnaire de transactions (doit exister tant que le modèle existe)
     * @param parent Objet parent Qt
     */
    explicit TransactionTableModel (Transactions::CTransactionManager *manager, QObject *parent = nullptr);
    ~TransactionTableModel() override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

private:
    Transactions::CTransactionManager *m_manager;
};

#endif // TRANSACTIONTABLEMODEL_H
