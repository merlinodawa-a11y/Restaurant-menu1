#include "DeliveryStaff.h"

DeliveryStaff::DeliveryStaff() {}
DeliveryStaff::DeliveryStaff(const std::string &name, const std::string &address, const std::string &phone)
    : Staff(name,address,phone) {}
std::string DeliveryStaff::getRole() const { return "DeliveryStaff"; }
