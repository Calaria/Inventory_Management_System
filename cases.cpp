#include <iostream>
#include <unordered_set>
#include <algorithm>
#include <string>
#include <sstream>

#include "Product.h"
#include "cases.h"
#include "Inventory.h"
#include "Settings.h"
#include "Algorithm.h"

using namespace std;
vector<string> choices = {" ",
                          "Add Product",
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
    Settings::line_separator(cout);
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
    Settings::line_separator(cout);
    cout << "Enter your choice: ";
    string choice;
    getline(cin, choice);
    // if user enters a single character, return it
    if (choice.size() == 1)
        return choice[0];
    // if user enters multiple characters, find the largest common sequence
    int idx = largest_common_sequence(choice, choices);
    if (idx == 9)
        return 'q';
    return idx + '0';
}

int handleCases(const string &role)
{
    Inventory inventory;
    Settings::line_separator(cout);
    cout << "---------------Inventory Management System ----------------" << endl;
    Settings::line_separator(cout);
    cout << "------------------------- Welcome! ------------------------" << endl;
    Settings::line_separator(cout);
    do
    {
        char choice = prompt(); // display choices
        unordered_set<char> admin_rights = {'1', '2', '4', '6'};
        if (role == "user" && admin_rights.count(choice))
        {
            cout << "[info]: You do not have permission to perform this operation." << endl;
            Settings::line_separator(cout);
            continue;
        }
        switch (choice)
        {
        // invalid choice
        case '0':
            cout << "[info]: Invalid Choice. Please Try again" << endl;
            Settings::line_separator(cout);
            continue;
        // add product
        case '1':
        {
            int id;
            string name, category;
            double price;
            int quantity;
            printf("How many products do you want to add? ");
            int n;
            cin >> n;
            unordered_set<string> Inquiry_content = {"ID", "Name", "Category", "Price", "Quantity"};
            while (n--)
            {
                prompt_info(id, name, category, price, quantity, Inquiry_content);
                Product product(id, name, category, price, quantity);
                inventory.addProduct(product);
            }
            break;
        }
        // remove product
        case '2':
        {
            int id;
            cout << "Enter product id: ";
            cin >> id;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (inventory.findProduct(id) == nullptr)
            {
                cout << "[info]: Product not found." << endl;
                Settings::line_separator(cout);
                break;
            }
            else
            {
                inventory.removeProduct(id);
            }
            break;
        }
        // find product
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
                    cout << "[info]: Invalid input. Please enter a number for ID: ";
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
                cout << "[info]: Product not found." << endl;
                Settings::line_separator(cout);
            }
            break;
        }
        // update product
        case '4':
        {
            int id;
            string name, category;
            double price;
            int quantity;

            cout << "Enter the product id: ";
            cin >> id;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (inventory.findProduct(id) == nullptr)
            {
                cout << "[info]: Product not found." << endl;
                Settings::line_separator(cout);
                break;
            }

            vector<string>update_choices={" ","Name","Category","Price","Quantity","Done"};
            while(true)
            {
                cout << "What information would you like to update? (Name/Category/Price/Quantity): \n";
                cout << "If you are done updating, please enter 'Done'." << endl;
                string input;
                getline(cin, input);
                transform(input.begin(), input.end(), input.begin(), ::tolower);
                int idx = largest_common_sequence(input, update_choices);
                if (idx ==0)
                {
                    cout << "[info]: Invalid input. Please enter 'Name', 'Category', 'Price', or 'Quantity'." << endl;
                    continue;
                }
                unordered_set<string>tmp={update_choices[idx]};
                prompt_info(id, name, category, price, quantity, tmp);
                if(idx==5)
                {
                    break;
                }
            }
            inventory.updateProduct(id, name, category, price, quantity);
            cout << "[info]: Product updated successfully." << endl;
            Settings::line_separator(cout);
            break;
        }
        // print inventory
        case '5':
            inventory.printProduct();
            break;
        // save inventory
        case '6':
            inventory.saveInventoryToFile("inventory.csv");
            cout << "[info]: Inventory saved to file." << endl;
            Settings::line_separator(cout);
            break;
        // load inventory
        case '7':
            inventory.loadInventoryFromFile("inventory.csv");
            cout << "[info]: Inventory loaded from file." << endl;
            Settings::line_separator(cout);
            break;
        // sort by price
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
                cout << "[info]: Invalid input. Please enter 'A' or 'D'." << endl;
            }

            break;
        }
        // quit
        case 'q':
        case 'Q':
            cout << "[info]: Goodbye!" << endl;
            Settings::line_separator(cout);
            return 0;
        default:
            cout << "[info]: Invalid Choice. Please Try again" << endl;
            Settings::line_separator(cout);
            break;
        }
    } while (true);
}