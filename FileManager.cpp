#include "FileManager.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>

using namespace std;

bool FileManager::saveCustomers(const string &filename, const vector<Customer> &customers) {
    ofstream fout(filename);
    if (!fout) return false;
    for (const auto &c : customers) {
        fout << c.getName() << '|' << c.getContact() << '|' << c.getAddress() << '|';
        const auto &oh = c.getOrderHistory();
        for (size_t i=0;i<oh.size();++i) { fout << oh[i]; if (i+1<oh.size()) fout << ','; }
        fout << '\n';
    }
    return true;
}

bool FileManager::loadCustomers(const string &filename, vector<Customer> &customers) {
    ifstream fin(filename);
    if (!fin) return false;
    string line;
    while (getline(fin, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string name, contact, address, ordersPart;
        if (!getline(ss, name, '|')) continue;
        if (!getline(ss, contact, '|')) continue;
        if (!getline(ss, address, '|')) continue;
        Customer c(name, contact, address);
        if (getline(ss, ordersPart)) {
            stringstream os(ordersPart);
            string token;
            while (getline(os, token, ',')) {
                if (token.empty()) continue;
                try { c.addOrderToHistory(stoi(token)); } catch(...) {}
            }
        }
        customers.push_back(c);
    }
    return true;
}

bool FileManager::saveOrders(const string &filename, const vector<Order> &orders) {
    ofstream fout(filename);
    if (!fout) return false;
    for (const auto &o : orders) {
        fout << o.getId() << '|' << o.getCustomer().getName() << '|' << o.getCustomer().getContact() << '|' << o.getCustomer().getAddress() << '|';
        fout << (o.getType()==OrderType::DELIVERY?"DELIVERY":"PICKUP") << '|' << fixed << setprecision(2) << o.getTotalPrice() << '|';
        const auto &items = o.getItems();
        for (size_t i=0;i<items.size();++i) {
            fout << items[i].getName() << '~' << items[i].getCuisine() << '~' << fixed << setprecision(2) << items[i].getPrice();
            if (i+1<items.size()) fout << ',';
        }
        fout << '\n';
    }
    return true;
}

bool FileManager::loadOrders(const string &filename, vector<Order> &orders) {
    ifstream fin(filename);
    if (!fin) return false;
    string line;
    while (getline(fin, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string idS, custName, custContact, custAddress, typeS, totalS, itemsPart;
        if (!getline(ss, idS, '|')) continue;
        if (!getline(ss, custName, '|')) continue;
        if (!getline(ss, custContact, '|')) continue;
        if (!getline(ss, custAddress, '|')) continue;
        if (!getline(ss, typeS, '|')) continue;
        if (!getline(ss, totalS, '|')) continue;
        if (!getline(ss, itemsPart)) itemsPart = "";
        int id = stoi(idS);
        OrderType otype = (typeS=="DELIVERY")?OrderType::DELIVERY:OrderType::PICKUP;
        Customer c(custName, custContact, custAddress);
        vector<MenuItem> items;
        stringstream is(itemsPart);
        string token;
        while (getline(is, token, ',')) {
            if (token.empty()) continue;
            stringstream ts(token);
            string iname, icuisine, iprice;
            if (!getline(ts, iname, '~')) continue;
            if (!getline(ts, icuisine, '~')) continue;
            if (!getline(ts, iprice, '~')) continue;
            double p = stod(iprice);
            items.emplace_back(0, iname, icuisine, p, true);
        }
        orders.emplace_back(id, c, items, otype);
    }
    return true;
}
