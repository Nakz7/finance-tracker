#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "budgetmanager.h" // Include the full definition for MOC
#include "transactionmanager.h" // Include the full definition for MOC

// Forward declarations
class QComboBox;
class QSpinBox;
class QPushButton;

namespace UI {
    enum class DateRange {
        CurrentMonth,
        Last3Months,
        CurrentYear,
        Custom
    };
}

namespace QtCharts
{
    class QChartView;
    class QChart;
}

/**
 * @brief La classe MainWindow est la fenêtre principale de l'application.
 *
 * Elle affiche les données des transactions sous forme de graphique et fournit
 * des contrôles pour filtrer les données affichées.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Construit un objet MainWindow.
     * @param parent Le widget parent, par défaut nullptr.
     */
    explicit MainWindow(QWidget *parent = nullptr);

    /**
     * @brief Destructeur de l'objet MainWindow.
     */
    ~MainWindow();

    // --- Test Accessors ---
    /**
     * @brief Retourne un pointeur vers le combobox de sélection du mois (pour les tests).
     */
    QComboBox* monthComboBox() const { return m_monthComboBox; }

    /**
     * @brief Retourne un pointeur vers le spinbox de sélection de l'année (pour les tests).
     */
    QSpinBox* yearSpinBox() const { return m_yearSpinBox; }

    /**
     * @brief Retourne un pointeur vers l'objet QChart (pour les tests).
     */
    QtCharts::QChart* chart() const { return m_chart; }

    /**
     * @brief Retourne un pointeur vers le gestionnaire de transactions (pour les tests).
     */
    CTransactionManager* transactionManager() const { return m_transactionManager; }

    /**
     * @brief Retourne un pointeur vers le gestionnaire de budgets (pour les tests).
     */
    Budget::CBudgetManager* budgetManager() const { return m_budgetManager; }

    /**
     * @brief Retourne un pointeur vers le combobox de sélection de la plage de dates (pour les tests).
     */
    QComboBox* dateRangeComboBox() const { return m_dateRangeComboBox; }

public slots:
    /**
     * @brief Met à jour le graphique en fonction des filtres sélectionnés.
     *
     * Ce slot est connecté aux signaux des widgets de filtre (mois, année).
     */
    void updateChart();

private slots:
    /**
     * @brief Ouvre la boîte de dialogue pour ajouter une nouvelle transaction.
     */
    void onAddTransactionClicked();

private:
    /**
     * @brief Configure l'interface utilisateur (widgets, layouts).
     */
    void setupUi();

    // Membres UI
    QtCharts::QChartView* m_chartView = nullptr; ///< La vue qui affiche le graphique.
    QtCharts::QChart* m_chart = nullptr; ///< L'objet graphique qui contient les séries de données.
    QComboBox* m_monthComboBox = nullptr; ///< Le sélecteur pour le mois.
    QSpinBox* m_yearSpinBox = nullptr; ///< Le sélecteur pour l'année.
    QComboBox* m_dateRangeComboBox = nullptr; ///< Le sélecteur de plage de dates.
    QPushButton* m_addTransactionButton = nullptr; ///< Le bouton pour ajouter une transaction.

    // Membre Données
    CTransactionManager* m_transactionManager = nullptr; ///< Le gestionnaire de transactions.
    Budget::CBudgetManager* m_budgetManager = nullptr; ///< Le gestionnaire de budgets.
};

#endif // MAINWINDOW_H
