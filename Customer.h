#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <vector>

class Customer {
private:
    std::string name;
    std::string contact;
    std::string address;
    std::vector<int> orderHistory; // store order IDs to avoid circular dependency
public:
    Customer();
    Customer(const std::string &name, const std::string &contact, const std::string &address);
    // getters
    std::string getName() const;
    std::string getContact() const;
    std::string getAddress() const;
    const std::vector<int>& getOrderHistory() const;
    // setters
    void setName(const std::string &n);
    void setContact(const std::string &c);
    void setAddress(const std::string &a);
    // modify
    void addOrderToHistory(int orderId);
};

#endif // CUSTOMER_H
