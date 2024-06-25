#include "user.h"

User::User(const string &username, const string &password, Role role)
    : username(username), password(password), role(role) {}

string User::getUsername() const
{
    return username;
}

bool User::verifyPassword(const string &password) const
{
    return this->password == password;
}

Role User::getRole() const
{
    return role;
}