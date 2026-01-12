#include "services/AccountService.h"
#include "utils/FileHandler.h"
#include "utils/Helper.h"
#include <algorithm>

AccountService::AccountService() {
    dataFile = Helper::getDataPath() + "accounts.txt";
    FileHandler::createFileIfNotExists(dataFile);
    loadAccounts();
}

void AccountService::loadAccounts() {
    accounts.clear();
    std::vector<std::string> lines = FileHandler::readAllLines(dataFile);
    
    for (const auto& line : lines) {
        if (!line.empty()) {
            accounts.push_back(Account::deserialize(line));
        }
    }
}

void AccountService::saveAccounts() {
    std::vector<std::string> lines;
    for (const auto& account : accounts) {
        lines.push_back(account.serialize());
    }
    FileHandler::writeAllLines(dataFile, lines);
}

Account* AccountService::createAccount(const std::string& userId, AccountType type) {
    Account newAccount(userId, type);
    accounts.push_back(newAccount);
    saveAccounts();
    
    // Return pointer to the newly added account
    return &accounts.back();
}

double AccountService::getBalance(const std::string& accountNumber) {
    Account* account = getAccountByNumber(accountNumber);
    if (account != nullptr) {
        return account->getBalance();
    }
    return -1; // Account not found
}

bool AccountService::closeAccount(const std::string& accountNumber) {
    for (auto& account : accounts) {
        if (account.getAccountNumber() == accountNumber && account.getIsActive()) {
            if (account.getBalance() > 0) {
                return false; // Cannot close account with balance
            }
            account.setIsActive(false);
            saveAccounts();
            return true;
        }
    }
    return false;
}

std::vector<Account> AccountService::getAccountsByUserId(const std::string& userId) {
    std::vector<Account> userAccounts;
    
    for (const auto& account : accounts) {
        if (account.getUserId() == userId && account.getIsActive()) {
            userAccounts.push_back(account);
        }
    }
    
    return userAccounts;
}

Account* AccountService::getAccountByNumber(const std::string& accountNumber) {
    for (auto& account : accounts) {
        if (account.getAccountNumber() == accountNumber) {
            return &account;
        }
    }
    return nullptr;
}

bool AccountService::updateAccount(const Account& account) {
    for (auto& acc : accounts) {
        if (acc.getAccountNumber() == account.getAccountNumber()) {
            acc = account;
            saveAccounts();
            return true;
        }
    }
    return false;
}

bool AccountService::accountExists(const std::string& accountNumber) {
    return std::any_of(accounts.begin(), accounts.end(), 
        [&accountNumber](const Account& acc) {
            return acc.getAccountNumber() == accountNumber && acc.getIsActive();
        });
}
