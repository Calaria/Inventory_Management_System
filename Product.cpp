#include "product.h"

Product::Product() : id(0), name(""), category(""), price(0.0), quantity(0) {}

Product::Product(int id, string name, string category, double price, int quantity)
    : id(id), name(name), category(category), price(price), quantity(quantity) {}

int Product::getId() const { return id; }
string Product::getName() const { return name; }
string Product::getCategory() const { return category; }
double Product::getPrice() const { return price; }
int Product::getQuantity() const { return quantity; }

void Product::setName(string name) { this->name = name; }
void Product::setCategory(string category) { this->category = category; }
void Product::setPrice(double price) { this->price = price; }
void Product::setQuantity(int quantity) { this->quantity = quantity; }

string Product::toString() const
{
    stringstream ss;
    ss << left << setw(10) << id
       << setw(60) << name
       << setw(20) << category
       << setw(20) << price
       << setw(10) << quantity;
    return ss.str();
}
