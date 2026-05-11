// ============================================================
// main.cpp
// Entry point of MacroLog -- Nutrition Macro Tracker
// Contains the menu loop and food addition logic.
// ============================================================

#include <iostream>
#include <string>
#include "FoodDatabase.h"   // for FoodDatabase class
#include "MealPlan.h"       // for MealPlan class and ComparePlans()
using namespace std;


// ============================================================
// Function: addFoodToPlan
// Handles adding a food item to a given MealPlan.
// First searches the database. If found, uses those values.
// If not found, shows partial matches or falls back to manual entry.
// ============================================================

void addFoodToPlan(MealPlan &plan, FoodDatabase &db) {

    string query;
    cout << "\nEnter food name (or keyword to search): ";
    cin.ignore();               // clears leftover newline from previous cin >>
    getline(cin, query);        // reads full line including spaces

    // Create a temporary FoodItem to hold the search result
    FoodItem found("", 0, 0, 0);

    bool inDB = db.search(query, found);   // search database for exact match

    if (inDB) {
        // Exact match found -- show the values and ask user to confirm
        cout << "\nFound in database!" << endl;
        cout << "  " << found.getName()
             << "  [Protein: " << found.getProtein() << "g"
             << "  Carbs: "   << found.getCarbs()   << "g"
             << "  Fat: "     << found.getFat()     << "g]" << endl;

        char useIt;
        cout << "Use these values? (y/n): ";
        cin >> useIt;

        if (useIt == 'y' || useIt == 'Y') {
            plan.addItem(found);
            cout << found.getName() << " added to " << plan.getName() << "!" << endl;
            return;   // done -- exit the function
        }

    } else {
        // Exact match not found -- try partial keyword search
        cout << "\nExact match not found. Searching similar items..." << endl;
        db.showMatches(query);

        char tryAgain;
        cout << "Try exact name from above? (y/n): ";
        cin >> tryAgain;

        if (tryAgain == 'y' || tryAgain == 'Y') {
            string exactName;
            cout << "Enter exact name: ";
            cin.ignore();
            getline(cin, exactName);

            if (db.search(exactName, found)) {
                plan.addItem(found);
                cout << found.getName() << " added to " << plan.getName() << "!" << endl;
                return;   // done -- exit the function
            } else {
                cout << "Still not found. Switching to manual entry." << endl;
            }
        }
    }

    // ---- Manual Entry Fallback ----
    // If food was not found in database, user enters values manually

    cout << "\n--- Manual Entry ---" << endl;

    string itemName;
    double protein, carbs, fat;

    cout << "Enter food name: ";
    cin.ignore();
    getline(cin, itemName);

    cout << "Enter Protein (g): ";
    cin >> protein;
    while (protein < 0) {
        cout << "Invalid! Enter a positive value: ";
        cin >> protein;
    }

    cout << "Enter Carbs (g): ";
    cin >> carbs;
    while (carbs < 0) {
        cout << "Invalid! Enter a positive value: ";
        cin >> carbs;
    }

    cout << "Enter Fat (g): ";
    cin >> fat;
    while (fat < 0) {
        cout << "Invalid! Enter a positive value: ";
        cin >> fat;
    }

    // Create a new FoodItem with manually entered values and add to plan
    FoodItem manual(itemName, protein, carbs, fat);
    plan.addItem(manual);
    cout << itemName << " added to " << plan.getName() << "!" << endl;
}


// ============================================================
// main() -- program starts here
// ============================================================

int main() {

    cout << "========================================" << endl;
    cout << "     NUTRITION MACRO TRACKER" << endl;
    cout << "========================================" << endl;

    // Load the food database from foods.csv
    FoodDatabase db;

    // Create two meal plans
    MealPlan planA("Bulking Plan");
    MealPlan planB("Cutting Plan");

    int choice;

    // Keep showing menu until user selects Exit (7)
    do {
        cout << "\n--- MAIN MENU ---" << endl;
        cout << "1. Add food item to Plan A (" << planA.getName() << ")" << endl;
        cout << "2. Add food item to Plan B (" << planB.getName() << ")" << endl;
        cout << "3. Search food in database" << endl;
        cout << "4. View Plan A Report" << endl;
        cout << "5. View Plan B Report" << endl;
        cout << "6. Compare Plans" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            addFoodToPlan(planA, db);

        } else if (choice == 2) {
            addFoodToPlan(planB, db);

        } else if (choice == 3) {
            string keyword;
            cout << "Enter keyword to search: ";
            cin.ignore();
            getline(cin, keyword);
            db.showMatches(keyword);

        } else if (choice == 4) {
            planA.displayReport();

        } else if (choice == 5) {
            planB.displayReport();

        } else if (choice == 6) {
            // ComparePlans is a friend function -- called like a normal function
            // NOT called as planA.ComparePlans() because it is NOT a member
            ComparePlans(planA, planB);

        } else if (choice == 7) {
            cout << "\nExiting. Goodbye!" << endl;

        } else {
            cout << "Invalid choice. Please try again." << endl;
        }

    } while (choice != 7);

    return 0;
}
