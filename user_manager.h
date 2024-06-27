#ifndef USER_MANAGER_H
#define USER_MANAGER_H

#include <vector>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <fstream> // 用于文件读写操作。
#include <sstream> // 用于字符串流操作。

#include "user.h"
#include "Settings.h"

using namespace std;

class UserManager
{
private:
    vector<User> users;

public:
    void addUser(const User &user);
    bool authenticate(const string &username, const string &password) const;
    void printAllUsers();
    Role getUserRole(const string &username) const;

    // 新添加的管理用户的方法
    void deleteUser(const string &username);
    void updateUser(const string &username, const string &newPassword);
    User *findUser(const string &username);
    void loadUsers();
    void saveUsers();

};

#endif // USER_MANAGER_H
