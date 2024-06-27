#include "user_manager.h"

void UserManager::addUser(const User &user)
{
    if (findUser(user.getUsername()) == nullptr)
        users.push_back(user);
    else
        cerr << "[info]: Error: user already exists." << endl;
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

void UserManager::updateUser(const string &username, const string &newPassword, Role &role)
{
    for (auto &user : users)
    {
        if (user.getUsername() == username)
        {
            // 假设有 setPassword 方法，如果没有，则需要添加
            user.setPassword(newPassword);
            user.setRole(role);
            break;
        }
    }
}

User *UserManager::findUser(const string &username)
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
    Settings::line_separator(cout);
    Settings::printUserTableHeader(cout);
    Settings::line_separator(cout);
    for(const auto &user : users)
    {
        cout << user.toString() << endl;
    }
    Settings::line_separator(cout);
}

// load users
void UserManager::loadUsers()
{
    ifstream file("users.txt");
    if (!file)
    {
        cerr << "[info]: Error: could not open file." << endl;
        return;
    }

    string username;
    string password;
    string role;
    while (file >> username >> password >> role)
    {
        Role r = role == "ADMIN" ? Role::ADMIN : Role::USER;
        users.push_back(User(username, password, r));
    }
    file.close();
}
// save users
void UserManager::saveUsers()
{
    ofstream file("users.txt");
    if (!file)
    {
        cerr << "[info]: Error: could not open file." << endl;
        return;
    }

    for (const auto &user : users)
    {
        file << user.getUsername() << " "
             << user.getPassword() << " "
             << (user.getRole() == Role::ADMIN ? "ADMIN" : "USER") << endl;
    }
    file.close();
}