#include <iostream>

#include "Product.h"
#include "Inventory.h"
#include "Settings.h"
#include "cases.h"
#include "user_manager.h"

using namespace std;

int main()
{
    UserManager userManager;
    // 添加用户
    userManager.addUser(User("admin", "admin123", Role::ADMIN));
    userManager.addUser(User("user1", "password1", Role::USER));

    // 验证用户
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    if (userManager.authenticate(username, password))
    {
        Settings::line_separator(cout);
        cout << "Authentication successful!" << endl;
        Role role = userManager.getUserRole(username);
        if (role == Role::ADMIN)
        {
            cout << "Welcome, Admin!" << endl; 
            Settings::line_separator(cout);
            // 管理员的专有操作
            handleCases();
        }
        else
        {
            cout << "Welcome, User!" << endl;
            Settings::line_separator(cout);
            // 普通用户的专有操作
            handleCases();
        }
    }
    else
    {
        cout << "Authentication failed!" << endl;
        handleCases();
    }
    
    return 0;
}
