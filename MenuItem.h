#ifndef MENUITEM_H
#define MENUITEM_H

#include <string>

class MenuItem {
private:
    int id;
    std::string name;
    std::string cuisine; // Italian or Chinese
    double price;
    bool available;
    int popularity;
public:
    MenuItem();
    MenuItem(int id, const std::string &name, const std::string &cuisine, double price, bool available=true);
    // getters
    int getId() const;
    std::string getName() const;
    std::string getCuisine() const;
    double getPrice() const;
    bool isAvailable() const;
    int getPopularity() const;
    // setters
    void setId(int v);
    void setName(const std::string &n);
    void setCuisine(const std::string &c);
    void setPrice(double p);
    void setAvailable(bool a);
    void incrementPopularity();
};

#endif // MENUITEM_H
