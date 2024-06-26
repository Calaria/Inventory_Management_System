#include "Inventory.h"
#include "Settings.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

void Inventory::addProduct(Product product)
{
    if (products.find(product.getId()) != products.end())
    {
        cout << "[info]: Id already exists." << endl;
    }
    else
    {
        products[product.getId()] = product;
        cout << "[info]: Product added successfully." << endl;
        Settings::line_separator(cout);
    }
}

void Inventory::removeProduct(int id)
{
    auto it = products.find(id);
    if (it != products.end())
    {
        cout << "Are you sure you want to remove the product? (Y/N): ";
        {
            char choice;
            cin >> choice;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (choice != 'Y' && choice != 'y')
            {
                cout << "[info]: Product not removed." << endl;
                Settings::line_separator(cout);
                return;
            }
            else
            {
                products.erase(it);
                cout << "[info]: Product removed successfully." << endl;
                Settings::line_separator(cout);
                
            }
        }
    }
    else
    {
        cout << "[info]: ID does not exist." << endl;
        Settings::line_separator(cout);
    }
}

Product *Inventory::findProduct(std::string input) // Product* 表示返回一个指向 Product 对象的指针。
{
    if(isdigit(input[0]))
    {
        int id = stoi(input);
        auto it = products.find(id);
        if (it != products.end())
        {
            return &(it->second);
        }
    }
    else
    {
        for (auto &pair : products)
        {
            if (pair.second.getName() == input)
            {
                return &(pair.second);
            }
        }
    }
    return nullptr;
}

void Inventory::updateProduct(int id, string name, string category, double price, int quantity)
{
    auto it = products.find(id);
    if (it != products.end())
    {
        it->second.setName(name);
        it->second.setCategory(category);
        it->second.setPrice(price);
        it->second.setQuantity(quantity);
    }
    else
    {
        cout << "[info]: ID does not exist." << endl;
    }
}

void Inventory::printProduct() const
{
    Settings::printTableHeader(cout); // Print the table header
    Settings::line_separator(cout);   // Print a line separator

    for (const auto &pair : products)
    {
        cout << pair.second.toString() << endl;
    }
}

void Inventory::saveInventoryToFile(string filename)
{
    ofstream file;
    file.open(filename, ios::out | ios::app);
    // ios::out：这是一个文件模式标志，表示文件将被打开以进行输出操作（写入数据）。如果文件不存在，将创建一个新文件。
    // ios::app：这是另一个文件模式标志，表示所有写入操作都将追加到文件末尾，而不是覆盖文件的现有内容。
    // 这两个标志通过按位或操作符 | 组合在一起
    for (const auto &pair : products)
    {
        const Product &p = pair.second;
        file << p.getId() << "," << p.getName() << "," << p.getCategory() << "," << p.getPrice() << "," << p.getQuantity() << endl;
    }
    file.close();
}

void Inventory::loadInventoryFromFile(string filename)
{
    ifstream file;       // 这行代码声明了一个名为 file 的 ofstream 对象。
    file.open(filename); // 这行代码调用 ofstream 对象的 open 成员函数，用于打开一个文件。open 函数的第一个参数是文件名，第二个参数是文件打开模式。

    if (file.is_open())
    {
        products.clear();
        string line;
        while (getline(file, line)) // getline 返回 false 表示已到达文件末尾或发生读取错误。
        {
            stringstream ss(line); // 将读取的行内容存储到一个 stringstream 对象 ss 中，以便进一步解析。
            string idStr, name, category, priceStr, quantityStr;
            // 使用 getline 函数从字符串流 ss 中读取以逗号分隔的子字符串，并分别存储到 idStr, name, category, priceStr 和 quantityStr 变量中。
            getline(ss, idStr, ',');
            getline(ss, name, ',');
            getline(ss, category, ',');
            getline(ss, priceStr, ',');
            getline(ss, quantityStr, ',');

            int id = stoi(idStr);
            double price = stod(priceStr);
            int quantity = stoi(quantityStr);

            products[id] = Product(id, name, category, price, quantity);
        }

        file.close();
    }
    else
    {
        cout << "[info]: Error: Could not open file " << filename << endl;
    }
}

void Inventory::sortByPrice(char choice)
{
    vector<Product> sortedProducts;
    for (const auto &pair : products)
    {
        sortedProducts.push_back(pair.second);
    }
    if (choice == 'A')
        sort(sortedProducts.begin(), sortedProducts.end(), [](const Product &a, const Product &b)
             { return a.getPrice() < b.getPrice(); });
    else if (choice == 'D')
    {
        sort(sortedProducts.begin(), sortedProducts.end(), [](const Product &a, const Product &b)
             { return a.getPrice() > b.getPrice(); });
    }
    Settings::printTableHeader(cout);
    Settings::line_separator(cout);

    for (const auto &p : sortedProducts)
    {
        cout << p.toString() << endl;
    }

    Settings::line_separator(cout);
}