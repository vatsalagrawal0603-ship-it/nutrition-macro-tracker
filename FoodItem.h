// ============================================================
// FoodItem.h
// Stores the name and macro values of a single food item.
// ============================================================

#ifndef FOODITEM_H
#define FOODITEM_H

#include <string>
using namespace std;

class FoodItem {

private:
    // private data members -- cannot be accessed directly from outside
    string name;
    double protein_g;
    double carb_g;
    double fat_g;

public:

    // Default constructor -- sets everything to zero/empty
    // This is needed when we store FoodItem inside a vector
    FoodItem() {
        name      = "";
        protein_g = 0;
        carb_g    = 0;
        fat_g     = 0;
    }

    // Parameterized constructor -- used when creating a food item with values
    // Example: FoodItem f("Chicken", 31.0, 0.0, 3.6);
    FoodItem(string n, double p, double c, double f) {
        name      = n;
        protein_g = p;
        carb_g    = c;
        fat_g     = f;
    }

    // ---- Getter functions ----
    // These are the only way to read the private data from outside the class

    string getName() {
        return name;
    }

    double getProtein() {
        return protein_g;
    }

    double getCarbs() {
        return carb_g;
    }

    double getFat() {
        return fat_g;
    }

};

#endif
