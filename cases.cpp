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
#include "user.h"
#include "user_manager.h"

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

char prompt_user()
{
    Settings::line_separator(cout);
    cout << "Please select an option OR enter a keyword to search: " << endl;
    cout << "1. Find Product" << endl;    // map to 3
    cout << "2. Print Inventory" << endl; // map to 5
    cout << "3. Load Inventory" << endl;  // map to 7
    cout << "4. Sort by Price" << endl;   // map to 8
    cout << "5. Quit" << endl;            // map to 9
    Settings::line_separator(cout);
    cout << "Enter your choice: ";
    string choice;
    getline(cin, choice);
    // if user enters a single character, return it
    unordered_map<string, string> map = {{"1", "3"}, {"2", "5"}, {"3", "7"}, {"4", "8"}, {"5", "q"}};
    if (choice.size() == 1)
        return map[choice][0];
    // if user enters multiple characters, find the largest common sequence
    int idx = largest_common_sequence(choice, choices);
    if (idx == 9)
        return 'q';
    return idx + '0';
}
char prompt_admin()
{
    Settings::line_separator(cout);
    cout << "Please select an option OR enter a keyword to search: " << endl;
    cout << "1. Add Product" << endl;     // admin
    cout << "2. Remove Product" << endl;  // admin
    cout << "3. Find Product" << endl;    // user1
    cout << "4. Update Product" << endl;  // admin
    cout << "5. Print Inventory" << endl; // user2
    cout << "6. Save Inventory" << endl;  // admin
    cout << "7. Load Inventory" << endl;  // user3
    cout << "8. Sort by Price" << endl;   // user4
    cout << "Q. Quit" << endl;            // user5
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
// print user prompts

char prompt(string role)
{
    if (role == "user")
        return prompt_user();
    else if (role == "admin")
        return prompt_admin();
    else
        return '0';
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
        char choice = prompt(role); // display choices
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
            if (inventory.findProduct(to_string(id)) == nullptr)
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

            while (true)
            {
                cout << "Enter the product id or product name to search\n";
                cout << "If you want to exit, please enter Done\n";

                string input;
                getline(cin, input);
                Product *product = inventory.findProduct(input);
                if (input == "Done" || input == "done")
                {
                    break;
                }
                if (product != nullptr)
                {
                    cout << "[info]: Product found.\n";
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

            if (inventory.findProduct(to_string(id)) == nullptr)
            {
                cout << "[info]: Product not found." << endl;
                Settings::line_separator(cout);
                break;
            }

            vector<string> update_choices = {" ", "Name", "Category", "Price", "Quantity", "Done"};
            while (true)
            {
                cout << "What information would you like to update? (Name/Category/Price/Quantity): \n";
                cout << "If you are done updating, please enter 'Done'." << endl;
                string input;
                getline(cin, input);
                transform(input.begin(), input.end(), input.begin(), ::tolower);
                int idx = largest_common_sequence(input, update_choices);
                if (idx == 0)
                {
                    cout << "[info]: Invalid input. Please enter 'Name', 'Category', 'Price', or 'Quantity'." << endl;
                    continue;
                }
                unordered_set<string> tmp = {update_choices[idx]};
                prompt_info(id, name, category, price, quantity, tmp);
                if (idx == 5)
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
//---------------------------------------------------------------------------
char prompt_user_cases()
{
    
    cout << "1. Add User\n";
    cout << "2. Delete User\n";
    cout << "3. Update User\n";
    cout << "4. find User\n";
    cout << "5. Print Users\n";
    cout << "6. Quit\n";
    cout << "Enter your choice:\n";
    Settings::line_separator(cout);
    string choice;
    getline(cin, choice);
    return choice[0];
}
int handle_user_cases()
{
    UserManager manager;
    // load users from file
    manager.loadUsers();
    Settings::line_separator(cout);
    cout << "---------------Inventory Management System ----------------" << endl;
    Settings::line_separator(cout);
    cout << "--------------------Welcome Admin! ------------------------" << endl;
    do
    {
        // display admin choices: add user, delete user, update user, get user, print users, quit
        char choice = prompt_user_cases();

        switch (choice)
        {
        // add user
        case '1':
        {
            string username, password;
            cout << "Enter username: ";
            getline(cin, username);
            cout << "Enter password: ";
            getline(cin, password);
            
            cout << "Enter role (admin/user): ";
            // get role
            Role role;
            string role_input;
            getline(cin, role_input);
            if (role_input == "admin")
            {
                role = Role::ADMIN;
            }
            else if (role_input == "user")
            {
                role = Role::USER;
            }
            else
            {
                cout << "[info]: Invalid role. Please enter 'admin' or 'user'." << endl;
                Settings::line_separator(cout);
                break;
            }
            manager.addUser(User(username, password, role));
            break;
        }
        // delete user
        case '2':
        {
            string username;
            cout << "Enter username: ";
            getline(cin, username);
            manager.deleteUser(username);
            break;
        }
        // update user
        case '3':
        {
            string username, password;
            cout << "Enter username: ";
            getline(cin, username);
            cout << "Enter new password: ";
            getline(cin, password);
            Role role;
            string role_input;
            cout<<"Enter role (admin/user): ";
            getline(cin, role_input);
            if (role_input == "admin")
            {
                role = Role::ADMIN;
            }
            else if (role_input == "user")
            {
                role = Role::USER;
            }
            else
            {
                cout << "[info]: Invalid role. Please enter 'admin' or 'user'." << endl;
                Settings::line_separator(cout);
                break;
            }
            getline(cin, password);
            manager.updateUser(username, password,role);
            break;
        }
        // get user
        case '4':
        {
            string username;
            cout << "Enter username: ";
            getline(cin, username);
            User *user = manager.findUser(username);
            if (user != nullptr)
            {
                cout << "[info]: User found.\n";
                Settings::line_separator(cout);
                Settings::printUserTableHeader(cout);
                cout << user->toString() << endl;
                Settings::line_separator(cout);
            }
            else
            {
                cout << "[info]: User not found." << endl;
                Settings::line_separator(cout);
            }
            break;
        }
        // print users
        case '5':
        {
            manager.printAllUsers();
            break;
        }
        // quit
        case '6':
        {
            cout << "[info]: Goodbye!" << endl;
            Settings::line_separator(cout);
            manager.saveUsers();
            return 0;
        }
        // invalid choice
        default:
        {
            cout << "[info]: Invalid Choice. Please Try again" << endl;
            Settings::line_separator(cout);
            break;
        }
        }
    } while (true);
    // save users to file
    manager.saveUsers();
    return 0;
}

// 如何返回false，则break
bool prompt_admin_UI() //
{
    do
    {
        cout << "[info]: Welcome, Admin!" << endl;
        Settings::line_separator(cout);
        // 管理员的专有操作
        // 选择处理商品信息还是用户信息
        cout << "Please choose the operation you want to perform: \n1. Product Management\n2. User Management\n3. Exit\n";
        int choice;
        cin >> choice;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (choice == 1)
            handleCases("admin"); // 来自cases.cpp
        else if (choice == 2)
        {
            handle_user_cases(); // 来自cases.cpp
        }
        else if (choice == 3)
        {
            cout << "[info]: Exiting..." << endl;
            return false;
        }
        else
        {
            cout << "[info]: Invalid choice." << endl;
        }
    } while (true);
}