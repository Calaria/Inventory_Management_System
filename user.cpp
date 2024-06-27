#include "user.h"

User::User(const string &username, const string &password, Role role)
    : username(username), password(password), role(role) {}

string User::getUsername() const
{
    return username;
}
// get password
string User::getPassword() const
{
    return password;
}

bool User::verifyPassword(const string &password) const
{
    return this->password == password;
}

Role User::getRole() const
{
    return role;
}

// 实现新添加的设置密码的方法
void User::setPassword(const string &newPassword)
{
    password = newPassword;
}
// reset role
void User::setRole(Role role)
{
    this->role = role;
}

// to string
string User::toString() const
{
    stringstream ss;
    ss << left << setw(20) << username
       << setw(20) << password
       << setw(10) << (role == Role::ADMIN ? "ADMIN" : "USER");
    return ss.str();
}