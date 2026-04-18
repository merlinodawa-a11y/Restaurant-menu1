// main.cpp
// Entry point and menu-driven interface for Restaurant Take-away System

#include <iostream>
#include <string>
#include "Restaurant.h"

using namespace std;

int main() {
    cout << "Restaurant Take-away System (multi-file) starting...\n";
    int limit = 50;
    cout << "Enter daily order limit (default 50): ";
    string line;
    getline(cin, line);
    if (!line.empty()) {
        try { limit = stoi(line); } catch(...) { limit = 50; }
    }

    Restaurant rest(limit);

    while (true) {
        cout << "\n==============================\n";
        cout << "RESTAURANT SYSTEM MENU\n";
        cout << "==============================\n";
        cout << "1. Add Customer\n";
        cout << "2. View Customers\n";
        cout << "3. Add Menu Item\n";
        cout << "4. View Menu\n";
        cout << "5. Place Order\n";
        cout << "6. View Orders\n";
        cout << "7. Edit Customer\n";
        cout << "8. Edit Menu Item\n";
        cout << "9. Generate Reports\n";
        cout << "10. Save Data\n";
        cout << "11. View Staff\n";
        cout << "12. Search Customer\n";
        cout << "13. Exit\n";
        cout << "==============================\n";
        cout << "Choose (1-11): ";
        int choice;
        if (!(cin >> choice)) { cin.clear(); cin.ignore(numeric_limits<std::streamsize>::max(), '\n'); cout << "Invalid input." << endl; continue; }

        switch (choice) {
            case 1: rest.addCustomer(); break;
            case 2: rest.viewCustomers(); break;
            case 3: rest.addMenuItem(); break;
            case 4: rest.displayMenu(); break;
            case 5: rest.placeOrder(); break;
            case 6: rest.viewOrders(); break;
            case 7: rest.editCustomer(); break;
            case 8: rest.editMenuItem(); break;
            case 9: rest.generateReport(); break;
            case 10: rest.saveDataToFile(); break;
            case 11: rest.viewStaff(); break;
            case 12: rest.searchCustomer(); break;
            case 13: cout << "Exiting and saving data...\n"; rest.saveDataToFile(); return 0;
            default: cout << "Invalid choice." << endl;
        }
    }

    return 0;
}
