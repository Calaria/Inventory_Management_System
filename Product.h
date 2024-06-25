#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

class Product
{
private:
    int id;
    string name;
    string category;
    double price;
    int quantity;

public:
    Product();
    Product(int id, string name, string category, double price, int quantity);

    int getId() const;
    string getName() const;
    string getCategory() const;
    double getPrice() const;
    int getQuantity() const;

    void setName(string name);
    void setCategory(string category);
    void setPrice(double price);
    void setQuantity(int quantity);

    string toString() const;
};

#endif // PRODUCT_H
