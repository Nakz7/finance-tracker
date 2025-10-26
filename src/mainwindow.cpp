#include "mainwindow.h"
#include "transactionmanager.h"
#include "transaction.h"
#include "addtransactiondialog.h"
#include "budgetmanager.h"

#include <QtWidgets>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      m_transactionManager(new Transactions::CTransactionManager),
      m_budgetManager(new Budget::CBudgetManager)
{
    // --- Sample Data ---
    m_transactionManager->addTransaction(Transactions::CTransaction(Transactions::CTransaction::Type::Expense, 50.0, "Groceries", QDate::currentDate().addDays(-5), "Food"));
    m_transactionManager->addTransaction(Transactions::CTransaction(Transactions::CTransaction::Type::Expense, 25.0, "Gas", QDate::currentDate().addDays(-10), "Transport"));
    m_transactionManager->addTransaction(Transactions::CTransaction(Transactions::CTransaction::Type::Expense, 120.0, "Tickets", QDate::currentDate().addMonths(-1), "Entertainment"));
    m_transactionManager->addTransaction(Transactions::CTransaction(Transactions::CTransaction::Type::Income, 2000.0, "Salary", QDate::currentDate().addMonths(-2), "Work"));
    m_transactionManager->addTransaction(Transactions::CTransaction(Transactions::CTransaction::Type::Expense, 75.0, "Dinner", QDate::currentDate().addMonths(-3), "Food"));

    m_budgetManager->addBudget(Budget::CBudget(QDate::currentDate().year(), QDate::currentDate().month(), "Food", 150.0));

    setupUi();
    updateChart();
}

MainWindow::~MainWindow()
{
    delete m_transactionManager;
    delete m_budgetManager;
}

void MainWindow::setupUi()
{
    setWindowTitle("Finance Tracker");
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    // --- Filter Controls ---
    QHBoxLayout *filterLayout = new QHBoxLayout();

    m_dateRangeComboBox = new QComboBox();
    m_dateRangeComboBox->addItem("Current Month", static_cast<int>(UI::DateRange::CurrentMonth));
    m_dateRangeComboBox->addItem("Last 3 Months", static_cast<int>(UI::DateRange::Last3Months));
    m_dateRangeComboBox->addItem("Current Year", static_cast<int>(UI::DateRange::CurrentYear));
    m_dateRangeComboBox->addItem("Custom", static_cast<int>(UI::DateRange::Custom));

    m_monthComboBox = new QComboBox();
    for (int i = 1; i <= 12; ++i) {
        m_monthComboBox->addItem(QLocale::system().monthName(i), i);
    }
    m_yearSpinBox = new QSpinBox();
    m_yearSpinBox->setRange(2000, 2100);

    m_monthComboBox->setCurrentIndex(QDate::currentDate().month() - 1);
    m_yearSpinBox->setValue(QDate::currentDate().year());

    filterLayout->addWidget(new QLabel("Show:"));
    filterLayout->addWidget(m_dateRangeComboBox);
    filterLayout->addWidget(new QLabel("Month:"));
    filterLayout->addWidget(m_monthComboBox);
    filterLayout->addWidget(new QLabel("Year:"));
    filterLayout->addWidget(m_yearSpinBox);
    filterLayout->addStretch();

    m_addTransactionButton = new QPushButton("Add Transaction");
    filterLayout->addWidget(m_addTransactionButton);
    mainLayout->addLayout(filterLayout);

    // --- Chart View ---
    m_chart = new QtCharts::QChart();
    m_chartView = new QtCharts::QChartView(m_chart);
    m_chartView->setRenderHint(QPainter::Antialiasing);
    mainLayout->addWidget(m_chartView);

    // --- Connections ---
    connect(m_dateRangeComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::updateChart);
    connect(m_monthComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::updateChart);
    connect(m_yearSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::updateChart);
    connect(m_addTransactionButton, &QPushButton::clicked, this, &MainWindow::onAddTransactionClicked);

    // Initial state
    m_monthComboBox->setEnabled(false);
    m_yearSpinBox->setEnabled(false);

    centralWidget->setLayout(mainLayout);
    resize(800, 600);
}

void MainWindow::updateChart()
{
    auto selectedRange = static_cast<UI::DateRange>(m_dateRangeComboBox->currentData().toInt());

    bool useCustom = (selectedRange == UI::DateRange::Custom);
    m_monthComboBox->setEnabled(useCustom);
    m_yearSpinBox->setEnabled(useCustom);

    QDate fromDate, toDate;
    QDate today = QDate::currentDate();
    QString title = m_dateRangeComboBox->currentText();

    if (useCustom) {
        int year = m_yearSpinBox->value();
        int month = m_monthComboBox->currentData().toInt();
        fromDate = QDate(year, month, 1);
        toDate = fromDate.addMonths(1).addDays(-1);
        title = QString("Expenses for %1 %2").arg(m_monthComboBox->currentText()).arg(year);
    } else {
        switch (selectedRange) {
            case UI::DateRange::CurrentMonth:
                fromDate = QDate(today.year(), today.month(), 1);
                toDate = today;
                break;
            case UI::DateRange::Last3Months:
                fromDate = today.addMonths(-3);
                toDate = today;
                break;
            case UI::DateRange::CurrentYear:
                fromDate = QDate(today.year(), 1, 1);
                toDate = today;
                break;
            default: // Should not happen
                fromDate = today;
                toDate = today;
        }
    }

    m_chart->removeAllSeries();
    QtCharts::QBarSeries *series = new QtCharts::QBarSeries();
    QMap<QString, double> expensesByCategory;
    auto transactions = m_transactionManager->transactionsByDateRange(fromDate, toDate);

    for (const auto& t : transactions) {
        if (t.type() == Transactions::CTransaction::Type::Expense) {
            expensesByCategory[t.category()] += t.amount();
        }
    }

    QStringList categories;
    for (auto it = expensesByCategory.constBegin(); it != expensesByCategory.constEnd(); ++it) {
        QtCharts::QBarSet *set = new QtCharts::QBarSet(it.key());
        *set << it.value();
        series->append(set);
        categories << it.key();
    }

    m_chart->addSeries(series);
    m_chart->setTitle(title);

    // ... (rest of the chart setup is the same)
    m_chart->setAnimationOptions(QtCharts::QChart::SeriesAnimations);
    for (auto axis : m_chart->axes()) { m_chart->removeAxis(axis); }
    QtCharts::QBarCategoryAxis *axisX = new QtCharts::QBarCategoryAxis();
    axisX->append(categories);
    m_chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);
    QtCharts::QValueAxis *axisY = new QtCharts::QValueAxis();
    axisY->setLabelFormat("%.2f");
    m_chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);
    m_chart->legend()->setVisible(true);
    m_chart->legend()->setAlignment(Qt::AlignBottom);
}

void MainWindow::onAddTransactionClicked()
{
    UI::CAddTransactionDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        Transactions::CTransaction newTransaction = dialog.getTransaction();
        m_transactionManager->addTransaction(newTransaction);
        updateChart();

        if (m_budgetManager->isBudgetExceeded(m_transactionManager->transactions(), newTransaction)) {
            QMessageBox::warning(this, "Budget Alert",
                QString("You have exceeded your budget for the '%1' category this month.")
                .arg(newTransaction.category()));
        }
    }
}
