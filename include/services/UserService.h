#ifndef USER_SERVICE_H
#define USER_SERVICE_H

#include <string>
#include <vector>
#include <memory>
#include "models/User.h"

class UserService {
private:
    std::string dataFile;
    std::vector<User> users;
    
    void loadUsers();
    void saveUsers();

public:
    UserService();
    
    bool registerUser(const std::string& username, const std::string& password,
                      const std::string& fullName, const std::string& phone, 
                      const std::string& email);
    User* login(const std::string& username, const std::string& password);
    bool changePassword(const std::string& userId, const std::string& oldPass, 
                        const std::string& newPass);
    User* getUserById(const std::string& userId);
    User* getUserByUsername(const std::string& username);
    bool updateUser(const User& user);
    bool usernameExists(const std::string& username);
};

#endif // USER_SERVICE_H
