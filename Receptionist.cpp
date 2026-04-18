#include "Receptionist.h"

Receptionist::Receptionist() {}
Receptionist::Receptionist(const std::string &name, const std::string &address, const std::string &phone)
    : Staff(name,address,phone) {}
std::string Receptionist::getRole() const { return "Receptionist"; }
