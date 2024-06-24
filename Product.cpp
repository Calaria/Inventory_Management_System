#include "product.h"

Product::Product(int id, string name, string category, double price, int quantity)
{
    this->id = id; // this是指针
    this->name = name;
    this->category = category;
    this->price = price;
    this->quantity = quantity;
}

int Product::getId() const
{
    return id;
}

void Product::setId(int id)
{
    this->id = id;
}

string Product::getName() const
{
    return name;
}

void Product::setName(string name)
{
    this->name = name;
}

string Product::getCategory() const
{
    return category;
}

void Product::setCategory(string category)
{
    this->category = category;
}

double Product::getPrice() const
{
    return price;
}

void Product::setPrice(double price)
{
    this->price = price;
}

int Product::getQuantity() const
{
    return quantity;
}

void Product::setQuantity(int quantity)
{
    this->quantity = quantity;
}
