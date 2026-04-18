#ifndef MANAGER_H
#define MANAGER_H

#include "Staff.h"

class Manager : public Staff {
public:
    Manager();
    Manager(const std::string &name, const std::string &address, const std::string &phone);
    std::string getRole() const override;
};

#endif // MANAGER_H
