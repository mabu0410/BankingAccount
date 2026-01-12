#include "services/UserService.h"
#include "utils/FileHandler.h"
#include "utils/Helper.h"
#include "utils/Validator.h"
#include <algorithm>

UserService::UserService() {
    dataFile = Helper::getDataPath() + "users.txt";
    FileHandler::createFileIfNotExists(dataFile);
    loadUsers();
}

void UserService::loadUsers() {
    users.clear();
    std::vector<std::string> lines = FileHandler::readAllLines(dataFile);
    
    for (const auto& line : lines) {
        if (!line.empty()) {
            users.push_back(User::deserialize(line));
        }
    }
}

void UserService::saveUsers() {
    std::vector<std::string> lines;
    for (const auto& user : users) {
        lines.push_back(user.serialize());
    }
    FileHandler::writeAllLines(dataFile, lines);
}

bool UserService::registerUser(const std::string& username, const std::string& password,
                                const std::string& fullName, const std::string& phone,
                                const std::string& email) {
    // Validate inputs
    if (!Validator::isValidUsername(username)) {
        return false;
    }
    if (!Validator::isValidPassword(password)) {
        return false;
    }
    if (!Validator::isValidPhone(phone)) {
        return false;
    }
    if (!Validator::isValidEmail(email)) {
        return false;
    }
    
    // Check if username already exists
    if (usernameExists(username)) {
        return false;
    }
    
    // Create new user with hashed password
    User newUser(username, Helper::hashPassword(password), fullName, phone, email);
    users.push_back(newUser);
    saveUsers();
    
    return true;
}

User* UserService::login(const std::string& username, const std::string& password) {
    std::string hashedPassword = Helper::hashPassword(password);
    
    for (auto& user : users) {
        if (user.getUsername() == username && 
            user.getPassword() == hashedPassword && 
            user.getIsActive()) {
            return &user;
        }
    }
    
    return nullptr;
}

bool UserService::changePassword(const std::string& userId, const std::string& oldPass,
                                  const std::string& newPass) {
    if (!Validator::isValidPassword(newPass)) {
        return false;
    }
    
    std::string hashedOldPass = Helper::hashPassword(oldPass);
    std::string hashedNewPass = Helper::hashPassword(newPass);
    
    for (auto& user : users) {
        if (user.getUserId() == userId && user.getPassword() == hashedOldPass) {
            user.setPassword(hashedNewPass);
            saveUsers();
            return true;
        }
    }
    
    return false;
}

User* UserService::getUserById(const std::string& userId) {
    for (auto& user : users) {
        if (user.getUserId() == userId) {
            return &user;
        }
    }
    return nullptr;
}

User* UserService::getUserByUsername(const std::string& username) {
    for (auto& user : users) {
        if (user.getUsername() == username) {
            return &user;
        }
    }
    return nullptr;
}

bool UserService::updateUser(const User& user) {
    for (auto& u : users) {
        if (u.getUserId() == user.getUserId()) {
            u = user;
            saveUsers();
            return true;
        }
    }
    return false;
}

bool UserService::usernameExists(const std::string& username) {
    return std::any_of(users.begin(), users.end(), [&username](const User& u) {
        return u.getUsername() == username;
    });
}
