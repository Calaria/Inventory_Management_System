#include <iostream>
#include <string>
#include <limits>
#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

#include "Product.h"
#include "Inventory.h"
#include "Settings.h"
#include "cases.h"
#include "user_manager.h"

using namespace std;

void getPassword(string &password)
{
#ifdef _WIN32
    char ch;
    while ((ch = _getch()) != '\r')
    { // Enter key
        if (ch == '\b')
        { // Backspace key
            if (!password.empty())
            {
                cout << "\b \b";
                password.pop_back();
            }
        }
        else
        {
            cout << '*';
            password += ch;
        }
    }
    cout << endl;
#else
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt); // Get current terminal attributes
    newt = oldt;
    newt.c_lflag &= ~ECHO; // Disable echo
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    getline(cin, password);

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // Restore old terminal attributes
    cout << endl;
#endif
}
int main()
{
    UserManager userManager;
    // 添加用户
    userManager.addUser(User("admin", "1", Role::ADMIN));
    userManager.addUser(User("user1", "password1", Role::USER));

    // 验证用户
    int cnt = 0;
    while (true)
    {
        if(cnt == 3)
        {
            cout << "[info]: Too many failed attempts. Exiting..." << endl;
            break;
        }
        string username, password;
        cout << "Enter username: ";
        getline(cin, username);

        cout << "Enter password: ";
        getPassword(password);

        if (userManager.authenticate(username, password))
        {
            Settings::line_separator(cout);
            cout << "[info]: Authentication successful!" << endl;
            Role role = userManager.getUserRole(username);
            if (role == Role::ADMIN)
            {
                cout << "[info]: Welcome, Admin!" << endl;
                Settings::line_separator(cout);
                // 管理员的专有操作
                // 选择处理商品信息还是用户信息
                cout <<"Please choose the operation you want to perform: \n1. Product Management\n2. User Management\n3. Exit\n";
                int choice;
                cin >> choice;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if(choice == 1)
                    handleCases("admin"); //来自cases.cpp
                else if(choice == 2)
                {
                    handle_user_cases();//来自cases.cpp
                }
                else if (choice == 3)
                {
                    cout << "[info]: Exiting..." << endl;
                    break;
                }
                else
                {
                    cout << "[info]: Invalid choice." << endl;
                }
            }
            else
            {
                cout << "[info]: Welcome, User!" << endl;
                Settings::line_separator(cout);
                // 普通用户的专有操作
                handleCases("user");
            }
        }
        else
        {
            cnt++;
            cout << "[info]: Authentication failed!" << endl;
        }
    }

    return 0;
}
