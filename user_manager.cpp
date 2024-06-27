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

void UserManager::deleteUser(const string &username)
{
    users.erase(std::remove_if(users.begin(), users.end(), [&](const User &user)
                               { return user.getUsername() == username; }),
                users.end());
}

void UserManager::updateUser(const string &username, const string &newPassword)
{
    for (auto &user : users)
    {
        if (user.getUsername() == username)
        {
            // 假设有 setPassword 方法，如果没有，则需要添加
            user.setPassword(newPassword);
            break;
        }
    }
}

User *UserManager::getUser(const string &username)
{
    for (auto &user : users)
    {
        if (user.getUsername() == username)
        {
            return &user;
        }
    }
    return nullptr; // 如果找不到用户，返回nullptr
}

// print all users
void UserManager::printAllUsers()
{
    for (const auto &user : users)
    {
        cout << "Username: " << user.getUsername() << ", Role: " << (user.getRole() == Role::ADMIN ? "ADMIN" : "USER") << endl;
    }
}