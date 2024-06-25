#ifndef USER_MANAGER_H
#define USER_MANAGER_H

#include <vector>
#include "user.h"
using namespace std;

class UserManager {
private:
    vector<User> users;

public:
    void addUser(const User &user);
    bool authenticate(const string &username, const string &password) const;
    Role getUserRole(const string &username) const;
};

#endif // USER_MANAGER_H
