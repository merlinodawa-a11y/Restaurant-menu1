#ifndef DELIVERYSTAFF_H
#define DELIVERYSTAFF_H

#include "Staff.h"

class DeliveryStaff : public Staff {
public:
    DeliveryStaff();
    DeliveryStaff(const std::string &name, const std::string &address, const std::string &phone);
    std::string getRole() const override;
};

#endif // DELIVERYSTAFF_H
