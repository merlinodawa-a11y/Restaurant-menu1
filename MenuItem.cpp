#include "MenuItem.h"

MenuItem::MenuItem() : id(0), price(0.0), available(true), popularity(0) {}
MenuItem::MenuItem(int id, const std::string &name, const std::string &cuisine, double price, bool available)
    : id(id), name(name), cuisine(cuisine), price(price), available(available), popularity(0) {}

int MenuItem::getId() const { return id; }
std::string MenuItem::getName() const { return name; }
std::string MenuItem::getCuisine() const { return cuisine; }
double MenuItem::getPrice() const { return price; }
bool MenuItem::isAvailable() const { return available; }
int MenuItem::getPopularity() const { return popularity; }

void MenuItem::setId(int v) { id = v; }
void MenuItem::setName(const std::string &n) { name = n; }
void MenuItem::setCuisine(const std::string &c) { cuisine = c; }
void MenuItem::setPrice(double p) { price = p; }
void MenuItem::setAvailable(bool a) { available = a; }
void MenuItem::incrementPopularity() { popularity++; }
