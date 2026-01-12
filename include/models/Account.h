#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>

enum class AccountType {
    SAVINGS,
    CHECKING,
    FIXED_DEPOSIT
};

class Account {
private:
    std::string accountNumber;
    std::string userId;
    AccountType type;
    double balance;
    double interestRate;
    std::string createdAt;
    bool isActive;

public:
    Account();
    Account(const std::string& userId, AccountType type);
    
    // Getters
    std::string getAccountNumber() const;
    std::string getUserId() const;
    AccountType getType() const;
    std::string getTypeString() const;
    double getBalance() const;
    double getInterestRate() const;
    std::string getCreatedAt() const;
    bool getIsActive() const;
    
    // Setters
    void setAccountNumber(const std::string& accNum);
    void setUserId(const std::string& uid);
    void setType(AccountType t);
    void setBalance(double bal);
    void setInterestRate(double rate);
    void setCreatedAt(const std::string& date);
    void setIsActive(bool active);
    
    // Operations
    bool deposit(double amount);
    bool withdraw(double amount);
    
    // Serialization
    std::string serialize() const;
    static Account deserialize(const std::string& data);
    static AccountType stringToType(const std::string& typeStr);
};

#endif // ACCOUNT_H
