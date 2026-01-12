#ifndef USER_H
#define USER_H

#include <string>

class User {
private:
    std::string userId;
    std::string username;
    std::string password;
    std::string fullName;
    std::string phoneNumber;
    std::string email;
    std::string createdAt;
    bool isActive;

public:
    User();
    User(const std::string& username, const std::string& password, 
         const std::string& fullName, const std::string& phone, const std::string& email);
    
    // Getters
    std::string getUserId() const;
    std::string getUsername() const;
    std::string getPassword() const;
    std::string getFullName() const;
    std::string getPhoneNumber() const;
    std::string getEmail() const;
    std::string getCreatedAt() const;
    bool getIsActive() const;
    
    // Setters
    void setUserId(const std::string& id);
    void setUsername(const std::string& uname);
    void setPassword(const std::string& pass);
    void setFullName(const std::string& name);
    void setPhoneNumber(const std::string& phone);
    void setEmail(const std::string& mail);
    void setCreatedAt(const std::string& date);
    void setIsActive(bool active);
    
    // Serialization
    std::string serialize() const;
    static User deserialize(const std::string& data);
};

#endif // USER_H
