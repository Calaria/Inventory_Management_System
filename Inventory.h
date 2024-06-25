#ifndef INVENTORY_H
#define INVENTORY_H

#include <unordered_map>
#include <string>
#include <fstream> // 用于文件读写操作。
#include <sstream> // 用于字符串流操作。
#include <iostream>
#include "product.h" // 包含自定义的 Product 类定义。

using namespace std;

class Inventory
{
private:
    unordered_map<int, Product> products;

public:
    void addProduct(Product product);
    void removeProduct(int id);
    Product* findProduct(int id);
    void updateProduct(int id, string name, string category, double price, int quantity);
    void printProduct() const;
    void saveInventoryToFile(string filename);
    void loadInventoryFromFile(string filename);
};

#endif // INVENTORY_H
