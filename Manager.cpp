#include "Manager.h"

Manager::Manager() {}
Manager::Manager(const std::string &name, const std::string &address, const std::string &phone)
    : Staff(name,address,phone) {}
std::string Manager::getRole() const { return "Manager"; }
