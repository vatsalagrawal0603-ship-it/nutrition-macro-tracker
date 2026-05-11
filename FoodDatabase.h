// ============================================================
// FoodDatabase.h
// Reads foods.csv and stores all food items in a vector.
// Provides search and keyword match functions.
// ============================================================

#ifndef FOODDATABASE_H
#define FOODDATABASE_H

#include <iostream>
#include <fstream>      // needed to read files (ifstream)
#include <string>
#include <vector>       // used to store all food items from the file
#include "FoodItem.h"
using namespace std;

class FoodDatabase {

private:
    // vector to store all food items loaded from the file
    vector<FoodItem> db;

    // Helper function: converts a string to all lowercase letters
    // Used so that search is not case-sensitive
    // Example: "Chicken" becomes "chicken"
    string toLower(string s) {
        for (int i = 0; i < s.length(); i++) {
            s[i] = tolower(s[i]);
        }
        return s;
    }

    // Helper function: checks if 'mainStr' contains 'subStr' inside it
    // Used for partial keyword matching
    // Example: "chicken breast" contains "chicken" -> returns true
    bool contains(string mainStr, string subStr) {
        // string::npos means "not found"
        if (mainStr.find(subStr) != string::npos) {
            return true;
        }
        return false;
    }

public:

    // Constructor -- automatically loads the food database on startup
    FoodDatabase() {
        loadFromFile("foods.csv");
    }

    // Reads the foods.csv file line by line and creates FoodItem objects
    void loadFromFile(string filename) {
        ifstream file(filename);   // open the file

        if (!file.is_open()) {
            cout << "Warning: foods.csv not found. Manual entry only." << endl;
            return;
        }

        string line;

        // Skip the first line (header: name,protein_g,carbs_g,fat_g)
        getline(file, line);

        // Read each remaining line one by one
        while (getline(file, line)) {

            // Each line looks like: Chicken Breast,31.0,0.0,3.6
            // We split it by comma using getline with ',' delimiter

            string foodName, p, c, f;

            // We need a stringstream to split by comma
            // Think of it like treating the line as its own mini input stream
            int pos1 = line.find(',');
            int pos2 = line.find(',', pos1 + 1);
            int pos3 = line.find(',', pos2 + 1);

            // Extract each part using substring
            foodName = line.substr(0, pos1);
            p        = line.substr(pos1 + 1, pos2 - pos1 - 1);
            c        = line.substr(pos2 + 1, pos3 - pos2 - 1);
            f        = line.substr(pos3 + 1);

            // Skip empty lines
            if (foodName.empty()) continue;

            // Convert string values to double
            double protein = atof(p.c_str());
            double carbs   = atof(c.c_str());
            double fat     = atof(f.c_str());

            // Create FoodItem and add to our vector
            FoodItem item(foodName, protein, carbs, fat);
            db.push_back(item);
        }

        file.close();
        cout << "Database loaded: " << db.size() << " food items." << endl;
    }

    // Searches for an exact food name (case-insensitive)
    // Returns true if found, and fills 'result' with the matching FoodItem
    bool search(string query, FoodItem &result) {
        string queryLower = toLower(query);

        for (int i = 0; i < db.size(); i++) {
            string dbNameLower = toLower(db[i].getName());
            if (dbNameLower == queryLower) {
                result = db[i];
                return true;
            }
        }
        return false;  // not found
    }

    // Shows all food items whose name contains the given keyword
    // Used for partial search (e.g. "chicken" shows all chicken items)
    void showMatches(string keyword) {
        string keyLower = toLower(keyword);
        int count = 0;

        cout << "\n--- Matching foods ---" << endl;

        for (int i = 0; i < db.size(); i++) {
            string nameLower = toLower(db[i].getName());

            if (contains(nameLower, keyLower)) {
                cout << "  " << db[i].getName()
                     << "  [P: " << db[i].getProtein() << "g"
                     << "  C: " << db[i].getCarbs()   << "g"
                     << "  F: " << db[i].getFat()     << "g]" << endl;
                count++;
            }
        }

        if (count == 0) {
            cout << "  No matches found." << endl;
        }

        cout << "----------------------" << endl;
    }

    // Returns total number of items in database
    int getSize() {
        return db.size();
    }

};

#endif
