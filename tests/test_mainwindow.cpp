#include <gtest/gtest.h>
#include <QApplication>
#include <QSpinBox>
#include <QComboBox>
#include <QDate>
#include <QLocale>
#include <QtCharts/QChart>
#include <QtCharts/QBarSeries>
#include "mainwindow.h"
#include "budgetmanager.h"
#include "transactionmanager.h" // Include full header for test logic

// Test fixture for QApplication initialization in a headless environment
class MainWindowTest : public ::testing::Test {
protected:
    static QApplication* app;

    static void SetUpTestSuite() {
        if (QApplication::instance() == nullptr) {
            int argc = 3;
            char* argv[] = { (char*)"test", (char*)"-platform", (char*)"offscreen", nullptr };
            app = new QApplication(argc, argv);
        }
    }

    static void TearDownTestSuite() {
        delete app;
        app = nullptr;
    }
};

QApplication* MainWindowTest::app = nullptr;

TEST_F(MainWindowTest, InitialWindowTitle) {
    MainWindow w;
    ASSERT_EQ(w.windowTitle().toStdString(), "Finance Tracker");
}

TEST_F(MainWindowTest, InitialFilterValues) {
    MainWindow w;
    QDate currentDate = QDate::currentDate();

    // Check year spinbox
    QSpinBox* yearSpinBox = w.yearSpinBox();
    ASSERT_NE(yearSpinBox, nullptr);
    EXPECT_EQ(yearSpinBox->value(), currentDate.year());

    // Check month combobox
    QComboBox* monthComboBox = w.monthComboBox();
    ASSERT_NE(monthComboBox, nullptr);
    EXPECT_EQ(monthComboBox->currentIndex(), currentDate.month() - 1);
}

TEST_F(MainWindowTest, UpdateChartLogic_CustomDate) {
    MainWindow w;
    QtCharts::QChart* chart = w.chart();
    ASSERT_NE(chart, nullptr);

    // --- Test Setup: Create a known state ---
    CTransactionManager* tm = w.transactionManager();
    ASSERT_NE(tm, nullptr);
    tm->clear(); // Clear default sample data
    // Add specific data for this test
    tm->addTransaction(CTransaction(CTransaction::Type::Expense, 100.0, "Test Expense 1", QDate(2024, 7, 10), "CategoryA"));
    tm->addTransaction(CTransaction(CTransaction::Type::Expense, 50.0, "Test Expense 2", QDate(2024, 7, 15), "CategoryB"));
    tm->addTransaction(CTransaction(CTransaction::Type::Income, 200.0, "Test Income", QDate(2024, 7, 12), "CategoryA"));

    // Set the range to Custom to enable month/year widgets
    w.dateRangeComboBox()->setCurrentIndex(w.dateRangeComboBox()->findData(static_cast<int>(UI::DateRange::Custom)));

    // Set filters to July 2024
    const int year = 2024;
    const int month = 7;
    w.yearSpinBox()->setValue(year);
    w.monthComboBox()->setCurrentIndex(month - 1);

    // Manually trigger the update
    w.updateChart();

    // --- Assertions ---
    // Check chart title in a locale-independent way
    QString expectedTitle = QString("Expenses for %1 %2")
                              .arg(QLocale::system().monthName(month))
                              .arg(year);
    ASSERT_EQ(chart->title().toStdString(), expectedTitle.toStdString());

    // Check series and bar sets based on the controlled data
    // We have 2 expenses in 2 unique categories, so we expect 2 bar sets.
    ASSERT_EQ(chart->series().count(), 1);
    QtCharts::QBarSeries* series = static_cast<QtCharts::QBarSeries*>(chart->series().at(0));
    ASSERT_NE(series, nullptr);
    EXPECT_EQ(series->barSets().count(), 2);
}


// Although we can't test the QMessageBox popup itself in headless mode,
// we can test the logic that would trigger it.
TEST_F(MainWindowTest, BudgetExceededLogicIsTriggered) {
    MainWindow w;

    // Get the internal budget manager to add a test budget
    Budget::CBudgetManager* bm = w.budgetManager();
    ASSERT_NE(bm, nullptr);
    bm->addBudget(Budget::CBudget(QDate::currentDate().year(), QDate::currentDate().month(), "Groceries", 100.0));

    // Get the internal transaction manager to add transactions
    Transactions::CTransactionManager* tm = w.transactionManager();
    ASSERT_NE(tm, nullptr);
    tm->addTransaction(Transactions::CTransaction(Transactions::CTransaction::Type::Expense, 80.0, "Initial shopping", QDate::currentDate(), "Groceries"));

    // This new expense should exceed the budget
    Transactions::CTransaction newExpense(Transactions::CTransaction::Type::Expense, 30.0, "More shopping", QDate::currentDate(), "Groceries");
    tm->addTransaction(newExpense);

    // Verify that the budget manager detects the exceeded budget
    EXPECT_TRUE(bm->isBudgetExceeded(tm->transactions(), newExpense));
}
