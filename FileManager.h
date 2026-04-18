#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>
#include <vector>
#include "Order.h"
#include "Customer.h"

namespace FileManager {
    bool saveCustomers(const std::string &filename, const std::vector<Customer> &customers);
    bool loadCustomers(const std::string &filename, std::vector<Customer> &customers);
    bool saveOrders(const std::string &filename, const std::vector<Order> &orders);
    bool loadOrders(const std::string &filename, std::vector<Order> &orders);
}

#endif // FILEMANAGER_H
