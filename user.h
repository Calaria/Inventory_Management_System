#ifndef USER_H
#define USER_H

#include <string>
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
};

#endif // USER_H
