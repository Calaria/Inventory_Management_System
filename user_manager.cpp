#include "user_manager.h"

void UserManager::addUser(const User &user)
{
    users.push_back(user);
}

bool UserManager::authenticate(const string &username, const string &password) const
{
    for (const auto &user : users)
    {
        if (user.getUsername() == username && user.verifyPassword(password))
        {
            return true;
        }
    }
    return false;
}

Role UserManager::getUserRole(const string &username) const
{
    for (const auto &user : users)
    {
        if (user.getUsername() == username)
        {
            return user.getRole();
        }
    }
    return Role::USER; // 默认角色
}
