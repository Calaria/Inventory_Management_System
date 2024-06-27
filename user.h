#ifndef USER_H
#define USER_H
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

enum class Role
{
    ADMIN,
    USER
};

class User
{
private:
    string username;
    string password;
    Role role;

public:
    User(const string &username, const string &password, Role role);
    string getUsername() const;
    bool verifyPassword(const string &password) const;
    Role getRole() const;
    string toString() const;

    // 新添加的设置密码的方法
    void setPassword(const string &newPassword);
};

#endif // USER_H
