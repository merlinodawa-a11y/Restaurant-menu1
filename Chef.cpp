#include "Chef.h"

Chef::Chef() {}
Chef::Chef(const std::string &name, const std::string &address, const std::string &phone, const std::string &cuisine)
    : Staff(name,address,phone), cuisineSpecialty(cuisine) {}
std::string Chef::getCuisineSpecialty() const { return cuisineSpecialty; }
void Chef::setCuisineSpecialty(const std::string &c) { cuisineSpecialty = c; }
std::string Chef::getRole() const { return "Chef"; }
