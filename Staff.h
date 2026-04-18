#ifndef STAFF_H
#define STAFF_H

#include <string>

class Staff {
private:
    std::string name;
    std::string address;
    std::string phone;
public:
    Staff();
    Staff(const std::string &name, const std::string &address, const std::string &phone);
    virtual ~Staff();
    std::string getName() const;
    std::string getAddress() const;
    std::string getPhone() const;
    void setName(const std::string &n);
    void setAddress(const std::string &a);
    void setPhone(const std::string &p);
    virtual std::string getRole() const;
};

#endif // STAFF_H
