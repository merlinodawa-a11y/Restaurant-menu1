#include "Staff.h"

Staff::Staff() {}
Staff::Staff(const std::string &name, const std::string &address, const std::string &phone)
    : name(name), address(address), phone(phone) {}
Staff::~Staff() {}
std::string Staff::getName() const { return name; }
std::string Staff::getAddress() const { return address; }
std::string Staff::getPhone() const { return phone; }
void Staff::setName(const std::string &n) { name = n; }
void Staff::setAddress(const std::string &a) { address = a; }
void Staff::setPhone(const std::string &p) { phone = p; }
std::string Staff::getRole() const { return "Staff"; }
