#include "Restaurant.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include "Manager.h"
#include "Chef.h"
#include "DeliveryStaff.h"
#include "Receptionist.h"
#include <map>

using namespace std;

Restaurant::Restaurant(int dailyLimit) : maxOrdersPerDay(dailyLimit), nextOrderId(1), ordersToday(0) {
    preloadMenu();
    loadCustomersFromFile();
    loadOrdersFromFile();

    // preload staff objects
    staff.push_back(new Manager("Alice Manager","Restaurant St","555-0001"));
    staff.push_back(new Chef("Marco","Kitchen Lane","555-1001","Italian"));
    staff.push_back(new Chef("Li Mei","Kitchen Lane","555-1002","Chinese"));
    staff.push_back(new DeliveryStaff("Sam Driver","Drivers Rd","555-2001"));
    staff.push_back(new Receptionist("Rita","Front St","555-3001"));
}

Restaurant::~Restaurant() {
    for (auto p : staff) delete p;
}

// ================= file I/O helpers =================
void Restaurant::loadCustomersFromFile() {
    ifstream fin(customersFile);
    if (!fin) return;
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
                try { int oid = stoi(token); c.addOrderToHistory(oid); } catch(...) {}
            }
        }
        customers.push_back(c);
    }
}

void Restaurant::loadOrdersFromFile() {
    ifstream fin(ordersFile);
    if (!fin) return;
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
            MenuItem mi(0, iname, icuisine, p, true);
            items.push_back(mi);
            for (auto &m : menuItems) if (m.getName()==iname) m.incrementPopularity();
        }
        Order ord(id, c, items, otype);
        orders.push_back(ord);
        nextOrderId = max(nextOrderId, id+1);
    }
}

void Restaurant::appendCustomerToFile(const Customer &c) {
    ofstream fout(customersFile, ios::app);
    if (!fout) { cerr << "Error opening customers file for append." << endl; return; }
    fout << c.getName() << '|' << c.getContact() << '|' << c.getAddress() << '|';
    const auto &oh = c.getOrderHistory();
    for (size_t i=0;i<oh.size();++i) { fout << oh[i]; if (i+1<oh.size()) fout << ','; }
    fout << '\n';
}

void Restaurant::appendOrderToFile(const Order &o) {
    ofstream fout(ordersFile, ios::app);
    if (!fout) { cerr << "Error opening orders file for append." << endl; return; }
    fout << o.getId() << '|' << o.getCustomer().getName() << '|' << o.getCustomer().getContact() << '|' << o.getCustomer().getAddress() << '|';
    fout << (o.getType()==OrderType::DELIVERY?"DELIVERY":"PICKUP") << '|' << fixed << setprecision(2) << o.getTotalPrice() << '|';
    const auto &items = o.getItems();
    for (size_t i=0;i<items.size();++i) {
        fout << items[i].getName() << '~' << items[i].getCuisine() << '~' << fixed << setprecision(2) << items[i].getPrice();
        if (i+1<items.size()) fout << ',';
    }
    fout << '\n';
}

void Restaurant::saveAllCustomersToFile() {
    ofstream fout(customersFile);
    if (!fout) { cerr << "Error writing customers file." << endl; return; }
    for (const auto &c : customers) {
        fout << c.getName() << '|' << c.getContact() << '|' << c.getAddress() << '|';
        const auto &oh = c.getOrderHistory();
        for (size_t i=0;i<oh.size();++i) { fout << oh[i]; if (i+1<oh.size()) fout << ','; }
        fout << '\n';
    }
}

// ================= menu & setup =================
void Restaurant::preloadMenu() {
    menuItems.clear();
    menuItems.emplace_back(1, "Margherita Pizza", "Italian", 8.99);
    menuItems.emplace_back(2, "Pasta Carbonara", "Italian", 10.99);
    menuItems.emplace_back(3, "Bruschetta", "Italian", 5.49);
    menuItems.emplace_back(4, "Kung Pao Chicken", "Chinese", 9.99);
    menuItems.emplace_back(5, "Fried Rice", "Chinese", 7.49);
    menuItems.emplace_back(6, "Spring Rolls", "Chinese", 4.99);
}

// ================= customer management =================
void Restaurant::addCustomer() {
    string name, contact, address;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Enter customer name: "; getline(cin, name);
    if (name.empty()) { cout << "Name cannot be empty." << endl; return; }
    // prevent duplicate customers by contact
    cout << "Enter contact (phone/email): "; getline(cin, contact);
    if (contact.empty()) { cout << "Contact cannot be empty." << endl; return; }
    if (findCustomerByContact(contact) != -1) { cout << "Customer with this contact already exists." << endl; return; }
    cout << "Enter address: "; getline(cin, address);
    Customer c(name, contact, address);
    customers.push_back(c);
    appendCustomerToFile(c);
    cout << "Customer added." << endl;
}

void Restaurant::viewCustomers() {
    if (customers.empty()) { cout << "No customers available." << endl; return; }
    cout << "\n--- Customers ---\n";
    for (size_t i=0;i<customers.size();++i) {
        const auto &c = customers[i];
        cout << i+1 << ". " << c.getName() << " | " << c.getContact() << " | " << c.getAddress() << " | Orders: " << c.getOrderHistory().size() << '\n';
    }
}

void Restaurant::addMenuItem() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string name, cuisine; double price; string availStr; bool avail=true;
    cout << "Enter item name: "; getline(cin, name); if (name.empty()) { cout << "Name empty." << endl; return; }
    cout << "Enter cuisine (Italian/Chinese): "; getline(cin, cuisine); if (cuisine != "Italian" && cuisine != "Chinese") { cout << "Invalid cuisine." << endl; return; }
    cout << "Enter price: "; if (!(cin >> price)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); cout << "Invalid price." << endl; return; }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Available? (y/n): "; getline(cin, availStr); if (!availStr.empty() && (availStr[0]=='n' || availStr[0]=='N')) avail=false;
    int newId = (menuItems.empty()?1:menuItems.back().getId()+1);
    menuItems.emplace_back(newId, name, cuisine, price, avail);
    cout << "Menu item added." << endl;
}

void Restaurant::viewOrders() {
    if (orders.empty()) { cout << "No orders." << endl; return; }
    cout << "\n--- Orders ---\n";
    for (const auto &o : orders) {
        cout << "Order ID " << o.getId() << " | " << o.getCustomer().getName() << " | " << (o.getType()==OrderType::DELIVERY?"Delivery":"Pickup") << " | Total: $" << fixed << setprecision(2) << o.getTotalPrice() << " | Items:";
        for (const auto &it : o.getItems()) cout << ' ' << it.getName() << ',';
        cout << '\n';
    }
}

void Restaurant::editCustomer() {
    viewCustomers();
    if (customers.empty()) return;
    cout << "Enter customer number to edit: "; int idx; if (!(cin >> idx)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); cout << "Invalid." << endl; return; }
    if (idx < 1 || idx > (int)customers.size()) { cout << "Out of range." << endl; return; }
    idx -= 1;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string name, contact, address;
    cout << "New name (leave empty to keep): "; getline(cin, name);
    cout << "New contact (leave empty to keep): "; getline(cin, contact);
    cout << "New address (leave empty to keep): "; getline(cin, address);
    if (!name.empty()) customers[idx].setName(name);
    if (!contact.empty()) {
        if (findCustomerByContact(contact) != -1 && customers[idx].getContact() != contact) { cout << "Contact already used." << endl; }
        else customers[idx].setContact(contact);
    }
    if (!address.empty()) customers[idx].setAddress(address);
    saveAllCustomersToFile();
    cout << "Customer updated." << endl;
}

void Restaurant::editMenuItem() {
    displayMenu(); if (menuItems.empty()) return;
    cout << "Enter menu item ID to edit: "; int id; if (!(cin >> id)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); cout << "Invalid." << endl; return; }
    MenuItem* mi = getMenuItemById(id);
    if (!mi) { cout << "No such ID." << endl; return; }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string priceStr, availStr;
    cout << "New price (leave empty to keep): "; getline(cin, priceStr);
    if (!priceStr.empty()) { try { double p = stod(priceStr); mi->setPrice(p); } catch(...) { cout << "Invalid price." << endl; } }
    cout << "Available? (y/n leave empty to keep): "; getline(cin, availStr);
    if (!availStr.empty()) mi->setAvailable(!(availStr[0]=='n' || availStr[0]=='N'));
    cout << "Menu item updated." << endl;
}

int Restaurant::findCustomerByContact(const string &contact) {
    for (size_t i=0;i<customers.size();++i) if (customers[i].getContact()==contact) return (int)i;
    return -1;
}

void Restaurant::searchCustomer() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Search by name or contact: "; string q; getline(cin, q);
    if (q.empty()) { cout << "Empty query." << endl; return; }
    vector<int> found;
    for (size_t i=0;i<customers.size();++i) {
        if (customers[i].getName().find(q)!=string::npos || customers[i].getContact().find(q)!=string::npos) found.push_back((int)i);
    }
    if (found.empty()) { cout << "No customers found." << endl; return; }
    for (int idx : found) {
        const auto &c = customers[idx];
        cout << "Name: " << c.getName() << " | Contact: " << c.getContact() << " | Address: " << c.getAddress() << " | Orders: " << c.getOrderHistory().size() << endl;
    }
}

// ================= menu display =================
void Restaurant::displayMenu() {
    if (menuItems.empty()) { cout << "Menu is empty." << endl; return; }
    cout << "\n--- MENU ---\n";
    cout << left << setw(5) << "ID" << setw(30) << "Item" << setw(12) << "Cuisine" << setw(8) << "Price" << setw(12) << "Available" << setw(10) << "Popular" << '\n';
    for (const auto &m : menuItems) {
        cout << left << setw(5) << m.getId() << setw(30) << m.getName() << setw(12) << m.getCuisine() << "$" << setw(7) << fixed << setprecision(2) << m.getPrice() << setw(12) << (m.isAvailable()?"Yes":"No") << setw(10) << m.getPopularity() << '\n';
    }
    cout << "------------\n";
}

MenuItem* Restaurant::getMenuItemById(int id) {
    for (auto &m : menuItems) if (m.getId()==id) return &m;
    return nullptr;
}

// ================= place order =================
void Restaurant::placeOrder() {
    if (ordersToday >= maxOrdersPerDay) { cout << "Daily limit reached." << endl; return; }
    cout << "Placing an order. Existing customer or new? 1=Existing 2=New: ";
    int ch; if (!(cin >> ch)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); cout << "Invalid" << endl; return; }
    int custIndex = -1;
    if (ch==1) {
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); cout << "Enter customer contact: "; string contact; getline(cin, contact);
        custIndex = findCustomerByContact(contact);
        if (custIndex==-1) { cout << "Customer not found." << endl; return; }
    } else if (ch==2) {
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); string name, contact, address;
        cout << "Name: "; getline(cin, name);
        cout << "Contact: "; getline(cin, contact);
        cout << "Address: "; getline(cin, address);
        customers.emplace_back(name, contact, address);
        appendCustomerToFile(customers.back());
        custIndex = (int)customers.size()-1;
    } else { cout << "Invalid choice." << endl; return; }

    vector<MenuItem> chosen;
    while (true) {
        displayMenu(); cout << "Enter item ID to add (0 finish): "; int id; if (!(cin >> id)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); cout << "Invalid" << endl; continue; }
        if (id==0) break;
        MenuItem* mi = getMenuItemById(id);
        if (!mi) { cout << "No such item." << endl; continue; }
        if (!mi->isAvailable()) { cout << "Not available." << endl; continue; }
        chosen.push_back(*mi);
    }
    if (chosen.empty()) { cout << "No items chosen." << endl; return; }
    cout << "Order type 1=Pickup 2=Delivery: "; int t; if (!(cin >> t)) { cout.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); cout << "Invalid" << endl; return; }
    OrderType otype = (t==2)?OrderType::DELIVERY:OrderType::PICKUP;
    if (otype==OrderType::DELIVERY) { cout << "Delivery distance (miles <=1.0): "; double dist; if (!(cin >> dist)) { cout.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); cout << "Invalid" << endl; return; } if (dist>1.0) { cout << "Too far." << endl; return; } }

    Order ord(nextOrderId, customers[custIndex], chosen, otype);
    for (const auto &it : chosen) for (auto &m : menuItems) if (m.getName()==it.getName()) m.incrementPopularity();
    orders.push_back(ord);
    customers[custIndex].addOrderToHistory(ord.getId());
    appendOrderToFile(ord);
    saveAllCustomersToFile();
    cout << "Order placed. ID=" << ord.getId() << " Total=$" << fixed << setprecision(2) << ord.getTotalPrice() << endl;
    nextOrderId++;
    ordersToday++;
}

void Restaurant::displayOrderHistoryForCustomer() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); cout << "Enter customer contact: "; string contact; getline(cin, contact);
    int idx = findCustomerByContact(contact);
    if (idx==-1) { cout << "Not found." << endl; return; }
    const auto &oh = customers[idx].getOrderHistory();
    if (oh.empty()) { cout << "No orders." << endl; return; }
    for (int oid : oh) {
        for (const auto &o : orders) if (o.getId()==oid) {
            cout << "Order " << o.getId() << " | " << (o.getType()==OrderType::DELIVERY?"Delivery":"Pickup") << " | $" << fixed << setprecision(2) << o.getTotalPrice() << " | Items:";
            for (const auto &it : o.getItems()) cout << ' ' << it.getName() << ',';
            cout << '\n';
        }
    }
}

// ================= reports =================
int Restaurant::getTotalOrders() const { return (int)orders.size(); }

double Restaurant::calculateTotalIncome() const { double sum=0; for (const auto &o : orders) sum += o.getTotalPrice(); return sum; }

string Restaurant::getMostPopularCuisine() const {
    map<string,int> counts;
    for (const auto &m : menuItems) counts[m.getCuisine()] += m.getPopularity();
    string best = "N/A"; int bestCnt=-1; for (auto &p : counts) if (p.second>bestCnt) { best=p.first; bestCnt=p.second; }
    return best;
}

MenuItem* Restaurant::getMostPopularItem() {
    if (menuItems.empty()) return nullptr;
    MenuItem* best = &menuItems[0];
    for (auto &m : menuItems) if (m.getPopularity() > best->getPopularity()) best=&m;
    return best;
}

vector<Customer> Restaurant::getLoyalCustomers() {
    vector<Customer> result; size_t best=0; for (const auto &c: customers) best = max(best, c.getOrderHistory().size()); if (best==0) return result; for (const auto &c: customers) if (c.getOrderHistory().size()==best) result.push_back(c); return result;
}

void Restaurant::generateReport() {
    cout << "\n--- REPORT ---\n";
    cout << "Total orders: " << getTotalOrders() << '\n';
    cout << "Total income: $" << fixed << setprecision(2) << calculateTotalIncome() << '\n';
    cout << "Most popular cuisine: " << getMostPopularCuisine() << '\n';
    MenuItem* m = getMostPopularItem(); cout << "Most popular item: " << (m?m->getName():string("N/A")) << "\n";
    auto loyal = getLoyalCustomers(); cout << "Loyal customers: "; if (loyal.empty()) cout << "N/A\n"; else { for (auto &c: loyal) cout << c.getName() << "(" << c.getOrderHistory().size() << ") "; cout << '\n'; }
    cout << "--------------\n";
}

void Restaurant::saveDataToFile() {
    saveAllCustomersToFile();
    ofstream fout(ordersFile);
    if (!fout) { cerr << "Error writing orders file." << endl; return; }
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
    cout << "Data saved." << endl;
}

void Restaurant::viewStaff() {
    if (staff.empty()) { cout << "No staff." << endl; return; }
    cout << "\n--- STAFF ---\n";
    for (size_t i=0;i<staff.size();++i) {
        Staff* s = staff[i];
        cout << i+1 << ". " << s->getRole() << " | " << s->getName() << " | " << s->getPhone() << " | " << s->getAddress();
        // if chef, print cuisine specialty
        Chef* c = dynamic_cast<Chef*>(s);
        if (c) cout << " | Specialty: " << c->getCuisineSpecialty();
        cout << '\n';
    }
}
