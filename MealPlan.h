// ============================================================
// MealPlan.h
// Stores a list of food items and tracks total macros.
// Also contains the friend function ComparePlans().
// ============================================================

#ifndef MEALPLAN_H
#define MEALPLAN_H

#include <iostream>
#include <vector>       // used to store the list of food items
#include <string>
#include "FoodItem.h"
using namespace std;

class MealPlan {

private:
    // private data members
    string planName;
    vector<FoodItem> items;   // STL vector -- stores all food items in this plan
    double total_protein;
    double total_carbs;
    double total_fat;

public:

    // Constructor -- sets plan name and initializes all totals to 0
    MealPlan(string name) {
        planName      = name;
        total_protein = 0;
        total_carbs   = 0;
        total_fat     = 0;
    }

    // Adds a food item to the plan
    // Also updates the running totals automatically
    void addItem(FoodItem f) {
        items.push_back(f);               // add to the vector
        total_protein += f.getProtein();  // update protein total
        total_carbs   += f.getCarbs();    // update carbs total
        total_fat     += f.getFat();      // update fat total
    }

    // Prints the full report for this meal plan
    void displayReport() {
        cout << "\n========================================" << endl;
        cout << "  Meal Plan: " << planName << endl;
        cout << "========================================" << endl;
        cout << "Food Items Logged: " << items.size() << endl;
        cout << "----------------------------------------" << endl;

        // Loop through all food items and print each one
        for (int i = 0; i < items.size(); i++) {
            cout << i + 1 << ". " << items[i].getName()
                 << "  [P: " << items[i].getProtein() << "g"
                 << "  C: " << items[i].getCarbs()   << "g"
                 << "  F: " << items[i].getFat()     << "g]" << endl;
        }

        cout << "----------------------------------------" << endl;
        cout << "Total Protein : " << total_protein << "g" << endl;
        cout << "Total Carbs   : " << total_carbs   << "g" << endl;
        cout << "Total Fat     : " << total_fat     << "g" << endl;
        cout << "========================================" << endl;
    }

    // Returns the plan name
    string getName() {
        return planName;
    }

    // ---- Friend Function Declaration ----
    // ComparePlans() is NOT a member of MealPlan.
    // But because it is declared as 'friend' here,
    // it can directly access the private members of MealPlan.
    friend void ComparePlans(const MealPlan& planA, const MealPlan& planB);

};


// ============================================================
// Friend Function -- defined outside the class
// Can access private members of MealPlan directly
// because of the 'friend' declaration above.
// ============================================================

void ComparePlans(const MealPlan& planA, const MealPlan& planB) {

    cout << "\n========================================" << endl;
    cout << "         COMPARISON REPORT" << endl;
    cout << "   " << planA.planName << "  vs  " << planB.planName << endl;
    cout << "========================================" << endl;

    // Directly accessing private members -- only possible because of friend declaration
    double diffProtein = planA.total_protein - planB.total_protein;
    double diffCarbs   = planA.total_carbs   - planB.total_carbs;
    double diffFat     = planA.total_fat     - planB.total_fat;

    cout << "\nMacro         Plan A     Plan B     Difference" << endl;
    cout << "------------------------------------------------" << endl;
    cout << "Protein(g)    " << planA.total_protein << "        "
         << planB.total_protein << "        " << diffProtein << endl;
    cout << "Carbs(g)      " << planA.total_carbs << "        "
         << planB.total_carbs << "        " << diffCarbs << endl;
    cout << "Fat(g)        " << planA.total_fat << "        "
         << planB.total_fat << "        " << diffFat << endl;

    cout << "\n--- Which plan is higher? ---" << endl;

    // Protein comparison
    if (diffProtein > 0)
        cout << "Protein : " << planA.planName << " is higher by " << diffProtein << "g" << endl;
    else if (diffProtein < 0)
        cout << "Protein : " << planB.planName << " is higher by " << -diffProtein << "g" << endl;
    else
        cout << "Protein : Both plans are equal" << endl;

    // Carbs comparison
    if (diffCarbs > 0)
        cout << "Carbs   : " << planA.planName << " is higher by " << diffCarbs << "g" << endl;
    else if (diffCarbs < 0)
        cout << "Carbs   : " << planB.planName << " is higher by " << -diffCarbs << "g" << endl;
    else
        cout << "Carbs   : Both plans are equal" << endl;

    // Fat comparison
    if (diffFat > 0)
        cout << "Fat     : " << planA.planName << " is higher by " << diffFat << "g" << endl;
    else if (diffFat < 0)
        cout << "Fat     : " << planB.planName << " is higher by " << -diffFat << "g" << endl;
    else
        cout << "Fat     : Both plans are equal" << endl;

    cout << "========================================" << endl;
}

#endif
