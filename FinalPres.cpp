#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <limits>
#include <cmath>
#include <algorithm>

using namespace std;

/*
========================================================
            PERSONAL FINANCE PLANNER
   Savings Tracker + Expense Manager + Car Loan Tool
========================================================
*/

// ===============================
// DATA STRUCTURES
// ===============================

struct Expense {
    string name;
    string category;
    double amount;
};

struct UserData {
    double monthlyIncome;
    double savings;
    double goalAmount;
    vector<Expense> expenses;
};

// ===============================
// INPUT UTILITIES
// ===============================

void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void waitForUser() {
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}

double getDoubleInput(string prompt) {
    double val;

    while (true) {
        cout << prompt;
        cin >> val;

        if (!cin.fail() && val >= 0)
            return val;

        cout << "Invalid input. Try again.\n";
        clearInput();
    }
}

int getIntInput(string prompt) {
    int val;

    while (true) {
        cout << prompt;
        cin >> val;

        if (!cin.fail())
            return val;

        cout << "Invalid input. Try again.\n";
        clearInput();
    }
}

// ===============================
// FUNCTION DECLARATIONS
// ===============================

void mainMenu(UserData& user);
void expenseMenu(UserData& user);

void addExpense(UserData& user);
void viewExpenses(const UserData& user);
void deleteExpense(UserData& user);
void editExpense(UserData& user);

void searchExpense(const UserData& user);
void sortExpenses(UserData& user);

void showCategoryBreakdown(const UserData& user);

void setIncome(UserData& user);
void setSavings(UserData& user);
void setGoal(UserData& user);

double totalExpenses(const UserData& user);

void showSummary(const UserData& user);
void simulateSavings(const UserData& user);
void simulateInterestGrowth(const UserData& user);
void yearlyForecast(const UserData& user);

void carLoanCalculator();

void saveData(const UserData& user);
void loadData(UserData& user);

// ===============================
// MAIN FUNCTION
// ===============================

int main() {
    UserData user;

    user.monthlyIncome = 0;
    user.savings = 0;
    user.goalAmount = 0;

    loadData(user);
    mainMenu(user);

    return 0;
}

// ===============================
// MAIN MENU
// ===============================

void mainMenu(UserData& user) {

    int choice;

    do {
        cout << "\n=================================\n";
        cout << "      FINANCIAL DASHBOARD\n";
        cout << "=================================\n";
        cout << "1. Set Monthly Income\n";
        cout << "2. Set Current Savings\n";
        cout << "3. Set Savings Goal\n";
        cout << "4. Manage Expenses\n";
        cout << "5. View Summary\n";
        cout << "6. Savings Simulation\n";
        cout << "7. Interest Growth Simulation\n";
        cout << "8. 5-Year Forecast\n";
        cout << "9. Car Loan Calculator\n";
        cout << "10. Save & Exit\n";
        cout << "=================================\n";

        choice = getIntInput("Select option: ");

        switch (choice) {
        case 1: setIncome(user); break;
        case 2: setSavings(user); break;
        case 3: setGoal(user); break;
        case 4: expenseMenu(user); break;
        case 5: showSummary(user); break;
        case 6: simulateSavings(user); break;
        case 7: simulateInterestGrowth(user); break;
        case 8: yearlyForecast(user); break;
        case 9: carLoanCalculator(); break;
        case 10: saveData(user); cout << "Saved.\n"; break;
        default: cout << "Invalid choice.\n";
        }

    } while (choice != 10);
}

// ===============================
// EXPENSE MENU
// ===============================

void expenseMenu(UserData& user) {

    int choice;

    do {
        cout << "\n----------- EXPENSE MENU -----------\n";
        cout << "1. Add Expense\n";
        cout << "2. View Expenses\n";
        cout << "3. Edit Expense\n";
        cout << "4. Delete Expense\n";
        cout << "5. Search Expense\n";
        cout << "6. Sort Expenses\n";
        cout << "7. Category Breakdown\n";
        cout << "8. Back\n";

        choice = getIntInput("Choose: ");

        switch (choice) {
        case 1: addExpense(user); break;
        case 2: viewExpenses(user); break;
        case 3: editExpense(user); break;
        case 4: deleteExpense(user); break;
        case 5: searchExpense(user); break;
        case 6: sortExpenses(user); break;
        case 7: showCategoryBreakdown(user); break;
        }

    } while (choice != 8);
}

// ===============================
// EXPENSE FUNCTIONS
// ===============================

void addExpense(UserData& user) {

    Expense e;

    cout << "Expense name: ";
    cin >> e.name;

    cout << "Category: ";
    cin >> e.category;

    e.amount = getDoubleInput("Amount: ");

    user.expenses.push_back(e);

    cout << "Expense added.\n";
}

void viewExpenses(const UserData& user) {

    cout << "\n----- EXPENSE LIST -----\n";

    for (size_t i = 0; i < user.expenses.size(); i++) {

        cout << i + 1 << ". "
            << user.expenses[i].name << " | "
            << user.expenses[i].category << " | $"
            << fixed << setprecision(2)
            << user.expenses[i].amount << endl;
    }
}

void editExpense(UserData& user) {

    viewExpenses(user);

    int index = getIntInput("Select expense #: ");

    if (index < 1 || index > user.expenses.size()) {
        cout << "Invalid selection.\n";
        return;
    }

    Expense& e = user.expenses[index - 1];

    cout << "New name: ";
    cin >> e.name;

    cout << "New category: ";
    cin >> e.category;

    e.amount = getDoubleInput("New amount: ");
}

void deleteExpense(UserData& user) {

    viewExpenses(user);

    int index = getIntInput("Delete #: ");

    if (index >= 1 && index <= user.expenses.size()) {
        user.expenses.erase(user.expenses.begin() + index - 1);
        cout << "Deleted.\n";
    }
}

// ===============================
// SEARCH + SORT
// ===============================

void searchExpense(const UserData& user) {

    string key;

    cout << "Search name: ";
    cin >> key;

    cout << "\nResults:\n";

    for (const auto& e : user.expenses) {
        if (e.name == key) {
            cout << e.name << " $" << e.amount << endl;
        }
    }
}

void sortExpenses(UserData& user) {

    sort(user.expenses.begin(), user.expenses.end(),
        [](Expense a, Expense b) {
            return a.amount > b.amount;
        });

    cout << "Expenses sorted by amount.\n";
}

// ===============================
// CATEGORY BREAKDOWN
// ===============================

void showCategoryBreakdown(const UserData& user) {

    vector<string> categories;
    vector<double> totals;

    for (const auto& e : user.expenses) {

        bool found = false;

        for (size_t i = 0; i < categories.size(); i++) {

            if (categories[i] == e.category) {
                totals[i] += e.amount;
                found = true;
                break;
            }
        }

        if (!found) {
            categories.push_back(e.category);
            totals.push_back(e.amount);
        }
    }

    cout << "\n--- CATEGORY TOTALS ---\n";

    for (size_t i = 0; i < categories.size(); i++) {
        cout << categories[i] << ": $" << totals[i] << endl;
    }
}

// ===============================
// USER SETTINGS
// ===============================

void setIncome(UserData& user) {
    user.monthlyIncome = getDoubleInput("Monthly income: ");
}

void setSavings(UserData& user) {
    user.savings = getDoubleInput("Current savings: ");
}

void setGoal(UserData& user) {
    user.goalAmount = getDoubleInput("Savings goal: ");
}

// ===============================
// CORE CALCULATIONS
// ===============================

double totalExpenses(const UserData& user) {

    double sum = 0;

    for (const auto& e : user.expenses) {
        sum += e.amount;
    }

    return sum;
}

// ===============================
// SUMMARY
// ===============================

void showSummary(const UserData& user) {

    double exp = totalExpenses(user);
    double left = user.monthlyIncome - exp;

    cout << "\n===== SUMMARY =====\n";
    cout << "Income: $" << user.monthlyIncome << endl;
    cout << "Expenses: $" << exp << endl;
    cout << "Leftover: $" << left << endl;
    cout << "Savings: $" << user.savings << endl;
    cout << "Goal: $" << user.goalAmount << endl;
}

// ===============================
// SIMULATIONS
// ===============================

void simulateSavings(const UserData& user) {

    double monthly = user.monthlyIncome - totalExpenses(user);

    if (monthly <= 0) {
        cout << "No savings possible.\n";
        return;
    }

    double current = user.savings;
    int months = 0;

    while (current < user.goalAmount) {
        current += monthly;
        months++;
    }

    cout << "Months to goal: " << months << endl;
}

void simulateInterestGrowth(const UserData& user) {

    double rate = getDoubleInput("Annual interest %: ") / 100 / 12;

    double current = user.savings;
    double monthly = user.monthlyIncome - totalExpenses(user);

    int months = 0;

    while (current < user.goalAmount) {
        current += monthly;
        current += current * rate;
        months++;
    }

    cout << "Months with interest: " << months << endl;
}

void yearlyForecast(const UserData& user) {

    double current = user.savings;
    double monthly = user.monthlyIncome - totalExpenses(user);

    cout << "\n--- 5 YEAR FORECAST ---\n";

    for (int year = 1; year <= 5; year++) {

        for (int m = 0; m < 12; m++) {
            current += monthly;
        }

        cout << "Year " << year << ": $" << current << endl;
    }
}

// ===============================
// CAR LOAN CALCULATOR
// ===============================

void carLoanCalculator() {

    double price = getDoubleInput("Car price: ");
    double down = getDoubleInput("Down payment: ");
    double rate = getDoubleInput("Interest rate: ");
    int months = getIntInput("Loan months: ");

    double loan = price - down;
    double r = rate / 100 / 12;

    double payment = (loan * r) /
        (1 - pow(1 + r, -months));

    cout << fixed << setprecision(2);
    cout << "Monthly payment: $" << payment << endl;
}

// ===============================
// FILE SAVE/LOAD
// ===============================

void saveData(const UserData& user) {

    ofstream file("finance.txt");

    file << user.monthlyIncome << endl;
    file << user.savings << endl;
    file << user.goalAmount << endl;

    file << user.expenses.size() << endl;

    for (const auto& e : user.expenses) {
        file << e.name << " "
            << e.category << " "
            << e.amount << endl;
    }
}

void loadData(UserData& user) {

    ifstream file("finance.txt");

    if (!file) return;

    int size;

    file >> user.monthlyIncome;
    file >> user.savings;
    file >> user.goalAmount;
    file >> size;

    for (int i = 0; i < size; i++) {

        Expense e;

        file >> e.name >> e.category >> e.amount;

        user.expenses.push_back(e);
    }
}