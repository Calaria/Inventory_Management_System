#include "cases.h"
#include <iostream>
#include <algorithm>
#include <unordered_set>
#include "Product.h"
#include "Inventory.h"
#include "Settings.h"
#include <sstream>


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



int common_sequence_length(string s1, string s2)
{
    transform(s1.begin(), s1.end(), s1.begin(), [](unsigned char c) { return tolower(c); });
    transform(s2.begin(), s2.end(), s2.begin(), [](unsigned char c) { return tolower(c); });
    int n = s1.size();
    int m = s2.size();

    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (s1[i - 1] == s2[j - 1])
            {
                dp[i][j] = 1 + dp[i - 1][j - 1];
            }
            else
            {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    return dp[n][m];
}

char largest_common_sequence(string s)
{
    int len = 0;
    int idx = -1;
    for (int i = 0; i < choices.size(); i++)
    {
        int curr_len = common_sequence_length(s, choices[i]);
        if (curr_len > len)
        {
            len = curr_len;
            idx = i;
        }
    }
    // if the length of the common sequence is less than 4, return '0'
    if (len<4)
    {
        return '0';
    }
    return idx + '1'; // Convert to corresponding menu choice (1-based index)
}

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
    if (tmp == '9')return 'q';
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
        // wrong input
        {
            cout << "Invalid Choice. Please Try again" << endl;
            Settings::line_separator(cout);
            continue;
        }
        case '1':
        // add product
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
        // remove product
        {
            int id;
            cout << "Enter product id: ";
            cin >> id;
            inventory.removeProduct(id);
            break;
        }
        case '3':
        // find product
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
        // update product
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
        // print inventory
        {
            inventory.printProduct();
            break;
        }
        case '6':
        // save inventory
        {
            inventory.saveInventoryToFile("inventory.csv");
            cout << "Inventory saved to file." << endl;
            cout << "-----------------------------------------------------------" << endl;
            break;
        }
        case '7':
        // load inventory
        {
            inventory.loadInventoryFromFile("inventory.csv");
            cout << "Inventory loaded from file." << endl;
            cout << "-----------------------------------------------------------" << endl;
            break;
        }
        case '8':
        // sort by price
        {
            char choice;
            cout << "Sort by price in ascending or descending order? (A/D): ";
            cin >> choice;
            inventory.sortByPrice(choice);
            break;
        }
        case 'q':
        case 'Q':
        // quit
            cout << "Goodbye!" << endl;
            cout << "-----------------------------------------------------------" << endl;
            return 0;

        default:
        // wrong input
            cout << "Invalid Choice. Please Try again" << endl;
            cout << "-----------------------------------------------------------" << endl;
            break;
        }
    } while (true);
    return 0;
}
