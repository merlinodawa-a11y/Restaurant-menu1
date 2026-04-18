#ifndef RECEPTIONIST_H
#define RECEPTIONIST_H

#include "Staff.h"

class Receptionist : public Staff {
public:
    Receptionist();
    Receptionist(const std::string &name, const std::string &address, const std::string &phone);
    std::string getRole() const override;
};

#endif // RECEPTIONIST_H
