#ifndef ACCOUNT_SERVICE_H
#define ACCOUNT_SERVICE_H

#include <string>
#include <vector>
#include "models/Account.h"

class AccountService {
private:
    std::string dataFile;
    std::vector<Account> accounts;
    
    void loadAccounts();
    void saveAccounts();

public:
    AccountService();
    
    Account* createAccount(const std::string& userId, AccountType type);
    double getBalance(const std::string& accountNumber);
    bool closeAccount(const std::string& accountNumber);
    std::vector<Account> getAccountsByUserId(const std::string& userId);
    Account* getAccountByNumber(const std::string& accountNumber);
    bool updateAccount(const Account& account);
    bool accountExists(const std::string& accountNumber);
};

#endif // ACCOUNT_SERVICE_H
