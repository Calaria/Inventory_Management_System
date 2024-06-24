#include "Inventory.h"

void Inventory::addProduct(Product product)
{
    bool found = false;
    for (auto &p : products)
    {
        if (p.getId() == product.getId())
        {
            cout << "Id already Exist." << endl;
            found = true;
            break;
        }
    }
    if (!found)
    {
        products.push_back(product);
        cout << "Product added successfully." << endl;
        cout << "-----------------------------------------------------------" << endl;
    }
}

void Inventory::removeProduct(int id)
{
    bool found = false;
    for (auto i = products.begin(); i != products.end(); i++)
    {
        if (i->getId() == id)
        {
            products.erase(i);
            found = true;
            cout << "Product removed successfully." << endl;
            cout << "-----------------------------------------------------------" << endl;
            break;
        }
    }
    if (!found)
    {
        cout << "Id does not exist" << endl;
    }
}

Product* Inventory::findProduct(int id) //Product* 表示返回一个指向 Product 对象的指针。
{
    for (auto i = products.begin(); i != products.end(); i++)
    {
        if (i->getId() == id)
        {
            return &(*i);
        }
    }
    return nullptr;
}

void Inventory::updateProduct(int id, string name, string category, double price, int quantity)
{
    bool found = false;
    for (auto i = products.begin(); i != products.end(); i++)
    {
        if (i->getId() == id)
        {
            i->setName(name);
            i->setCategory(category);
            i->setPrice(price);
            i->setQuantity(quantity);
            found = true;
            break;
        }
    }
    if (!found)
    {
        cout << "ID does not exist." << endl;
    }
}

void Inventory::printProduct() const
{
    for (auto i = products.begin(); i != products.end(); i++)
    {
        cout << "ID : " << i->getId() << endl;
        cout << "Name : " << i->getName() << endl;
        cout << "Category : " << i->getCategory() << endl;
        cout << "Price : $" << i->getPrice() << endl;
        cout << "Quantity : " << i->getQuantity() << endl;
    }
}

void Inventory::saveInventoryToFile(string filename)
{
    ofstream file;
    file.open(filename, ios::out | ios::app);
    //ios::out：这是一个文件模式标志，表示文件将被打开以进行输出操作（写入数据）。如果文件不存在，将创建一个新文件。
    //ios::app：这是另一个文件模式标志，表示所有写入操作都将追加到文件末尾，而不是覆盖文件的现有内容。
    //这两个标志通过按位或操作符 | 组合在一起
    for (int i = 0; i < products.size(); i++)
    {
        Product p = products[i];
        file << p.getId() << "," << p.getName() << "," << p.getCategory() << "," << p.getPrice() << "," << p.getQuantity() << endl;
    }
    file.close();
}

void Inventory::loadInventoryFromFile(string filename)
{
    ifstream file; //这行代码声明了一个名为 file 的 ofstream 对象。
    file.open(filename); //这行代码调用 ofstream 对象的 open 成员函数，用于打开一个文件。open 函数的第一个参数是文件名，第二个参数是文件打开模式。

    if (file.is_open())
    {
        string line;
        while (getline(file, line))//getline 返回 false 表示已到达文件末尾或发生读取错误。
        {
            stringstream ss(line);//将读取的行内容存储到一个 stringstream 对象 ss 中，以便进一步解析。
            string idStr, name, category, priceStr, quantityStr;
            //使用 getline 函数从字符串流 ss 中读取以逗号分隔的子字符串，并分别存储到 idStr, name, category, priceStr 和 quantityStr 变量中。
            getline(ss, idStr, ',');
            getline(ss, name, ',');
            getline(ss, category, ',');
            getline(ss, priceStr, ',');
            getline(ss, quantityStr, ',');

            int id = stoi(idStr);
            double price = stod(priceStr);
            int quantity = stoi(quantityStr);

            Product p(id, name, category, price, quantity);
            products.push_back(p);
        }

        file.close();
    }
    else
    {
        cout << "Error: Could not open file " << filename << endl;
    }
}
