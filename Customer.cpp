#include "Customer.h"

Customer::Customer() {}
Customer::Customer(const std::string &name, const std::string &contact, const std::string &address)
    : name(name), contact(contact), address(address) {}

std::string Customer::getName() const { return name; }
std::string Customer::getContact() const { return contact; }
std::string Customer::getAddress() const { return address; }
const std::vector<int>& Customer::getOrderHistory() const { return orderHistory; }

void Customer::setName(const std::string &n) { name = n; }
void Customer::setContact(const std::string &c) { contact = c; }
void Customer::setAddress(const std::string &a) { address = a; }
void Customer::addOrderToHistory(int orderId) { orderHistory.push_back(orderId); }
