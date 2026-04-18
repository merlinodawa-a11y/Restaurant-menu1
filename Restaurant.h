#ifndef RESTAURANT_H
#define RESTAURANT_H

#include <vector>
#include <string>

#include "Customer.h"
#include "MenuItem.h"
#include "Order.h"
#include "Staff.h"

class Restaurant {
private:
    std::vector<Customer> customers;
    std::vector<MenuItem> menuItems;
    std::vector<Order> orders;
    std::vector<Staff*> staff; // aggregation
    int maxOrdersPerDay;
    int nextOrderId;
    int ordersToday;

    // filenames
    const std::string customersFile = "customers.txt";
    const std::string ordersFile = "orders.txt";

    void preloadMenu();
    void loadCustomersFromFile();
    void loadOrdersFromFile();
    void appendCustomerToFile(const Customer &c);
    void appendOrderToFile(const Order &o);
    void saveAllCustomersToFile();

public:
    Restaurant(int dailyLimit=50);
    ~Restaurant();

    // Customer management
    void addCustomer();
    void viewCustomers();
    int findCustomerByContact(const std::string &contact);
    void searchCustomer();

    // Menu
    void displayMenu();
    MenuItem* getMenuItemById(int id);
    void addMenuItem();
    void viewOrders();
    void editCustomer();
    void editMenuItem();

    // Orders
    void placeOrder();
    void displayOrderHistoryForCustomer();
    void viewStaff();

    // Reports
    int getTotalOrders() const;
    double calculateTotalIncome() const;
    std::string getMostPopularCuisine() const;
    MenuItem* getMostPopularItem();
    std::vector<Customer> getLoyalCustomers();
    void generateReport();

    // Persistence
    void saveDataToFile();
};

#endif // RESTAURANT_H
