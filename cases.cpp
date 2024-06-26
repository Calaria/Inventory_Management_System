#include "cases.h"
#include <iostream>
#include <algorithm>
#include <unordered_set>
#include "Product.h"
#include "Inventory.h"
#include "Settings.h"
#include <sstream>
#include "Algorithm.h"

using namespace std;

vector<string> choices = {"Add Product",
                          "Remove Product",
                          "Find Product",
                          "Update Product",
                          "Print Inventory",
                          "Save Inventory",
                          "Load Inventory",
                          "Sort by Price",
                          "Quit"};

// print user prompts
char prompt()
{
    cout << "-----------------------------------------------------------" << endl;
    cout << "Please select an option OR enter a keyword to search: " << endl;
    cout << "1. Add Product" << endl;
    cout << "2. Remove Product" << endl;
    cout << "3. Find Product" << endl;
    cout << "4. Update Product" << endl;
    cout << "5. Print Inventory" << endl;
    cout << "6. Save Inventory" << endl;
    cout << "7. Load Inventory" << endl;
    cout << "8. Sort by Price" << endl;
    cout << "Q. Quit" << endl;
    cout << "-----------------------------------------------------------" << endl;
    cout << "Enter your choice: ";
    string choice;
    getline(cin, choice);
    // if user enters a single character, return it
    if (choice.size() == 1)
        return choice[0];
    // if user enters multiple characters, find the largest common sequence
    char tmp = largest_common_sequence(choice);
    if (tmp == '9')
        return 'q';
    return tmp;
}

int handleCases(const string &role)
{
    Inventory inventory;
    cout << "-----------------------------------------------------------" << endl;
    cout << "---------------Inventory Management System ----------------" << endl;
    cout << "-----------------------------------------------------------" << endl;
    cout << "------------------------- Welcome! ------------------------" << endl;
    cout << "-----------------------------------------------------------" << endl;
    do
    {
        char choice = prompt(); // display choices
        unordered_set<char> admin_rights = {'1', '2', '4', '6'};
        if (role == "user" && admin_rights.count(choice))
        {
            cout << "You do not have permission to perform this operation." << endl;
            Settings::line_separator(cout);
            continue;
        }
        switch (choice)
        {
        case '0':
            cout << "Invalid Choice. Please Try again" << endl;
            Settings::line_separator(cout);
            continue;
        case '1':
        {
            int id;
            string name, category;
            double price;
            int quantity;
            cout << "Enter ID: ";
            while (!(cin >> id))
            {
                cout << "Invalid input. Please enter a number for ID: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cin.ignore();
            cout << "Enter product name: ";
            getline(cin, name);
            cout << "Enter product category: ";
            getline(cin, category);
            cout << "Enter product price: $ ";
            while (!(cin >> price))
            {
                cout << "Invalid input. Please enter a number for price: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cout << "Enter product quantity: ";
            while (!(cin >> quantity))
            {
                cout << "Invalid input. Please enter a number for quantity: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            Product product(id, name, category, price, quantity);
            inventory.addProduct(product);
            break;
        }
        case '2':
        {
            int id;
            cout << "Enter product id: ";
            while (!(cin >> id))
            {
                cout << "Invalid input. Please enter a number for ID: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            inventory.removeProduct(id);
            break;
        }
        case '3':
        {
            int id;
            cout << "Enter product id: ";
            string input;

            while (true)
            {
                cout << "Please enter a number for ID: ";
                getline(cin, input);
                stringstream ss(input);

                if (ss >> id)
                {
                    break;
                }
                else
                {
                    cout << "Invalid input. Please enter a number for ID: ";
                    ss.clear();
                }
            }
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
            while (!(cin >> id))
            {
                cout << "Invalid input. Please enter a number for ID: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cin.ignore();
            cout << "Enter new product name: ";
            getline(cin, name);
            cout << "Enter new product category: ";
            getline(cin, category);
            cout << "Enter new product price: $ ";
            while (!(cin >> price))
            {
                cout << "Invalid input. Please enter a number for price: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cout << "Enter new product quantity: ";
            while (!(cin >> quantity))
            {
                cout << "Invalid input. Please enter a number for quantity: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            inventory.updateProduct(id, name, category, price, quantity);
            cout << "Product updated successfully." << endl;
            cout << "-----------------------------------------------------------" << endl;
            break;
        }
        case '5':
            inventory.printProduct();
            break;
        case '6':
            inventory.saveInventoryToFile("inventory.csv");
            cout << "Inventory saved to file." << endl;
            cout << "-----------------------------------------------------------" << endl;
            break;
        case '7':
            inventory.loadInventoryFromFile("inventory.csv");
            cout << "Inventory loaded from file." << endl;
            cout << "-----------------------------------------------------------" << endl;
            break;
        case '8':
        {
            string sort_choice;
            cout << "Sort by price in ascending or descending order? (A/D): ";
            getline(cin, sort_choice);
            if (!sort_choice.empty() && (sort_choice[0] == 'A' || sort_choice[0] == 'a' || sort_choice[0] == 'D' || sort_choice[0] == 'd'))
            {
                inventory.sortByPrice(sort_choice[0]);
            }
            else
            {
                cout << "Invalid input. Please enter 'A' or 'D'." << endl;
            }

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
}