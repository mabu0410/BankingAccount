#include "models/Account.h"
#include "utils/Helper.h"
#include <sstream>

Account::Account() : balance(0.0), interestRate(0.0), isActive(true) {
    accountNumber = Helper::generateAccountNumber();
    createdAt = Helper::getCurrentDate();
}

Account::Account(const std::string& userId, AccountType type)
    : userId(userId), type(type), balance(0.0), isActive(true) {
    accountNumber = Helper::generateAccountNumber();
    createdAt = Helper::getCurrentDate();
    
    // Set interest rate based on account type
    switch (type) {
        case AccountType::SAVINGS:
            interestRate = 0.5;
            break;
        case AccountType::CHECKING:
            interestRate = 0.1;
            break;
        case AccountType::FIXED_DEPOSIT:
            interestRate = 1.5;
            break;
    }
}

// Getters
std::string Account::getAccountNumber() const { return accountNumber; }
std::string Account::getUserId() const { return userId; }
AccountType Account::getType() const { return type; }
double Account::getBalance() const { return balance; }
double Account::getInterestRate() const { return interestRate; }
std::string Account::getCreatedAt() const { return createdAt; }
bool Account::getIsActive() const { return isActive; }

std::string Account::getTypeString() const {
    switch (type) {
        case AccountType::SAVINGS: return "SAVINGS";
        case AccountType::CHECKING: return "CHECKING";
        case AccountType::FIXED_DEPOSIT: return "FIXED_DEPOSIT";
        default: return "UNKNOWN";
    }
}

// Setters
void Account::setAccountNumber(const std::string& accNum) { accountNumber = accNum; }
void Account::setUserId(const std::string& uid) { userId = uid; }
void Account::setType(AccountType t) { type = t; }
void Account::setBalance(double bal) { balance = bal; }
void Account::setInterestRate(double rate) { interestRate = rate; }
void Account::setCreatedAt(const std::string& date) { createdAt = date; }
void Account::setIsActive(bool active) { isActive = active; }

// Operations
bool Account::deposit(double amount) {
    if (amount > 0) {
        balance += amount;
        return true;
    }
    return false;
}

bool Account::withdraw(double amount) {
    if (amount > 0 && amount <= balance) {
        balance -= amount;
        return true;
    }
    return false;
}

// Serialization - Format: accountNumber|userId|type|balance|interestRate|createdAt|isActive
std::string Account::serialize() const {
    std::stringstream ss;
    ss << accountNumber << "|" << userId << "|" << getTypeString() << "|"
       << balance << "|" << interestRate << "|" << createdAt << "|" 
       << (isActive ? "1" : "0");
    return ss.str();
}

Account Account::deserialize(const std::string& data) {
    Account account;
    std::stringstream ss(data);
    std::string token;
    int field = 0;
    
    while (std::getline(ss, token, '|')) {
        switch (field) {
            case 0: account.accountNumber = token; break;
            case 1: account.userId = token; break;
            case 2: account.type = stringToType(token); break;
            case 3: account.balance = std::stod(token); break;
            case 4: account.interestRate = std::stod(token); break;
            case 5: account.createdAt = token; break;
            case 6: account.isActive = (token == "1"); break;
        }
        field++;
    }
    
    return account;
}

AccountType Account::stringToType(const std::string& typeStr) {
    if (typeStr == "SAVINGS") return AccountType::SAVINGS;
    if (typeStr == "CHECKING") return AccountType::CHECKING;
    if (typeStr == "FIXED_DEPOSIT") return AccountType::FIXED_DEPOSIT;
    return AccountType::SAVINGS; // Default
}
