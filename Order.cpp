#include "Order.h"

Order::Order() : id(0), type(OrderType::PICKUP), totalPrice(0.0) {}
Order::Order(int id, const Customer &customer, const std::vector<MenuItem> &items, OrderType type)
    : id(id), customer(customer), items(items), type(type) { calculateTotal(); }

int Order::getId() const { return id; }
Customer Order::getCustomer() const { return customer; }
const std::vector<MenuItem>& Order::getItems() const { return items; }
OrderType Order::getType() const { return type; }
double Order::getTotalPrice() const { return totalPrice; }

void Order::calculateTotal() {
    double sum = 0.0;
    for (const auto &it : items) sum += it.getPrice();
    totalPrice = sum;
}
