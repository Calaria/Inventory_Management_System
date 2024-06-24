#ifndef PRODUCT_H
#define PRODUCT_H//“头文件保护”，防止这个头文件被多次包含

#include <string>
using namespace std;

class Product
{
// 类的私有成员变量，它们只能通过类的方法（函数）来访问和修改
private:
    int id;
    string name;
    string category;
    double price;
    int quantity;

public:
    // 这是一个构造函数，它在创建 Product 对象时被调用，用于初始化对象的属性。
    Product(int id, string name, string category, double price, int quantity);
    // 这些是公共成员函数，用于获取和设置私有成员变量的值。
    int getId() const; // const 关键字，这表示这个函数不会修改对象的状态。
    void setId(int id);

    string getName() const;
    void setName(string name);

    string getCategory() const;
    void setCategory(string category);

    double getPrice() const;
    void setPrice(double price);

    int getQuantity() const;
    void setQuantity(int quantity);
};

#endif // PRODUCT_H
