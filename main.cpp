#include <iostream>
#include "Product.h"
#include "Inventory.h"
#include "Settings.h"


using namespace std;

int main()
{
    Inventory inventory;
    cout << "-----------------------------------------------------------" << endl;
    cout << "---------------Inventory Management System ----------------" << endl;
    cout << "-----------------------------------------------------------" << endl;
    cout << "------------------------- Welcome! ------------------------" << endl;
    cout << "-----------------------------------------------------------" << endl;
    char choice;
    do
    {
        cout << "Please choose an option:" << endl;
        cout << "1. Add a product" << endl;
        cout << "2. Remove a product" << endl;
        cout << "3. Find a product" << endl;
        cout << "4. Update a product" << endl;
        cout << "5. View all products" << endl;
        cout << "6. Save inventory to file" << endl;
        cout << "7. Load Inventory from file" << endl;
        cout << "Q. Quit" << endl;
        cin >> choice;

        switch (choice)
        {
        case '1':
        {
            int id;
            string name, category;
            double price;
            int quantity;
            cout << "Enter ID: ";
            cin >> id;
            cout << "Enter product name: ";
            cin >> name;
            cout << "Enter product category: ";
            cin >> category;
            cout << "Enter product price: $ ";
            cin >> price;
            cout << "Enter product quantity: ";
            cin >> quantity;
            Product product(id, name, category, price, quantity);
            inventory.addProduct(product);
            break;
        }

        case '2':
        {
            int id;
            cout << "Enter product id: ";
            cin >> id;
            inventory.removeProduct(id);
            break;
        }

        case '3':
        {
            int id;
            cout << "Enter product id: ";
            cin >> id;
            Product *product = inventory.findProduct(id);
            if (product != nullptr)
            {
                Settings::line_separator(cout);
                Settings::printTableHeader(cout);
                Settings::line_separator(cout);
                cout << product->toString() << endl;
                Settings::line_separator(cout);
            }
            else
            {
                cout << "Product not found." << endl;
                Settings::line_separator(cout);
            }
            break;
        }

        case '4':
        {
            int id;
            string name, category;
            double price;
            int quantity;
            cout << "Enter the product id: ";
            cin >> id;
            cout << "Enter new product name: ";
            cin >> name;
            cout << "Enter new product category: ";
            cin >> category;
            cout << "Enter new product price: $ ";
            cin >> price;
            cout << "Enter new product quantity: ";
            cin >> quantity;
            inventory.updateProduct(id, name, category, price, quantity);
            cout << "Product updated successfully." << endl;
            cout << "-----------------------------------------------------------" << endl;
            break;
        }

        case '5':
        {
            inventory.printProduct();
            break;
        }
        case '6':
        {
            inventory.saveInventoryToFile("inventory.csv");
            cout << "Inventory saved to file." << endl;
            cout << "-----------------------------------------------------------" << endl;
            break;
        }
        case '7':
        {
            inventory.loadInventoryFromFile("inventory.csv");
            cout << "Inventory loaded from file." << endl;
            cout << "-----------------------------------------------------------" << endl;
            break;
        }
        case 'q':
        case 'Q':
            cout << "Goodbye!" << endl;
            cout << "-----------------------------------------------------------" << endl;
            return 0;

        default:
            cout << "Invalid Choice. Please Try again" << endl;
            cout << "-----------------------------------------------------------" << endl;
            break;
        }
    } while (true);

    return 0;
}
