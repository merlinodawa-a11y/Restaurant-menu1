#ifndef ORDER_H
#define ORDER_H

#include <vector>
#include <string>
#include "Customer.h"
#include "MenuItem.h"

enum class OrderType { PICKUP, DELIVERY };

class Order {
private:
    int id;
    Customer customer; // copy of customer
    std::vector<MenuItem> items;
    OrderType type;
    double totalPrice;
public:
    Order();
    Order(int id, const Customer &customer, const std::vector<MenuItem> &items, OrderType type);
    int getId() const;
    Customer getCustomer() const;
    const std::vector<MenuItem>& getItems() const;
    OrderType getType() const;
    double getTotalPrice() const;
    void calculateTotal();
};

#endif // ORDER_H
