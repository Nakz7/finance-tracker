#ifndef ADDTRANSACTIONDIALOG_H
#define ADDTRANSACTIONDIALOG_H

#include <QDialog>
#include "transaction.h" // For CTransaction return type

// Forward declarations
class QLineEdit;
class QDoubleSpinBox;
class QDateEdit;
class QComboBox;

namespace UI {

/**
 * @brief La classe CAddTransactionDialog est une boîte de dialogue pour ajouter une nouvelle transaction.
 *
 * Elle fournit un formulaire permettant à l'utilisateur de saisir les détails
 * d'une transaction (type, montant, libellé, date, catégorie).
 */
class CAddTransactionDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Construit la boîte de dialogue.
     * @param parent Le widget parent, par défaut nullptr.
     */
    explicit CAddTransactionDialog(QWidget *parent = nullptr);

    /**
     * @brief Retourne la transaction créée à partir des données du formulaire.
     * @return Un objet CTransaction.
     */
    CTransaction getTransaction() const;

private:
    void setupUi();

    // UI Members
    QComboBox*      m_typeComboBox;
    QDoubleSpinBox* m_amountSpinBox;
    QLineEdit*      m_labelLineEdit;
    QDateEdit*      m_dateEdit;
    QLineEdit*      m_categoryLineEdit;
};

} // namespace UI

#endif // ADDTRANSACTIONDIALOG_H
