#include "models/User.h"
#include "utils/Helper.h"
#include <sstream>

User::User() : isActive(true) {
    userId = Helper::generateUserId();
    createdAt = Helper::getCurrentDate();
}

User::User(const std::string& username, const std::string& password,
           const std::string& fullName, const std::string& phone, const std::string& email)
    : username(username), password(password), fullName(fullName),
      phoneNumber(phone), email(email), isActive(true) {
    userId = Helper::generateUserId();
    createdAt = Helper::getCurrentDate();
}

// Getters
std::string User::getUserId() const { return userId; }
std::string User::getUsername() const { return username; }
std::string User::getPassword() const { return password; }
std::string User::getFullName() const { return fullName; }
std::string User::getPhoneNumber() const { return phoneNumber; }
std::string User::getEmail() const { return email; }
std::string User::getCreatedAt() const { return createdAt; }
bool User::getIsActive() const { return isActive; }

// Setters
void User::setUserId(const std::string& id) { userId = id; }
void User::setUsername(const std::string& uname) { username = uname; }
void User::setPassword(const std::string& pass) { password = pass; }
void User::setFullName(const std::string& name) { fullName = name; }
void User::setPhoneNumber(const std::string& phone) { phoneNumber = phone; }
void User::setEmail(const std::string& mail) { email = mail; }
void User::setCreatedAt(const std::string& date) { createdAt = date; }
void User::setIsActive(bool active) { isActive = active; }

// Serialization - Format: userId|username|password|fullName|phone|email|createdAt|isActive
std::string User::serialize() const {
    std::stringstream ss;
    ss << userId << "|" << username << "|" << password << "|" 
       << fullName << "|" << phoneNumber << "|" << email << "|" 
       << createdAt << "|" << (isActive ? "1" : "0");
    return ss.str();
}

User User::deserialize(const std::string& data) {
    User user;
    std::stringstream ss(data);
    std::string token;
    int field = 0;
    
    while (std::getline(ss, token, '|')) {
        switch (field) {
            case 0: user.userId = token; break;
            case 1: user.username = token; break;
            case 2: user.password = token; break;
            case 3: user.fullName = token; break;
            case 4: user.phoneNumber = token; break;
            case 5: user.email = token; break;
            case 6: user.createdAt = token; break;
            case 7: user.isActive = (token == "1"); break;
        }
        field++;
    }
    
    return user;
}
