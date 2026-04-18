#ifndef CHEF_H
#define CHEF_H

#include "Staff.h"
#include <string>

class Chef : public Staff {
private:
    std::string cuisineSpecialty;
public:
    Chef();
    Chef(const std::string &name, const std::string &address, const std::string &phone, const std::string &cuisine);
    std::string getCuisineSpecialty() const;
    void setCuisineSpecialty(const std::string &c);
    std::string getRole() const override;
};

#endif // CHEF_H
