#include "services/TransactionService.h"
#include "utils/FileHandler.h"
#include "utils/Helper.h"
#include "utils/Validator.h"
#include <algorithm>

TransactionService::TransactionService(AccountService* accService)
    : accountService(accService) {
    dataFile = Helper::getDataPath() + "transactions.txt";
    FileHandler::createFileIfNotExists(dataFile);
    loadTransactions();
}

void TransactionService::loadTransactions() {
    transactions.clear();
    std::vector<std::string> lines = FileHandler::readAllLines(dataFile);
    
    for (const auto& line : lines) {
        if (!line.empty()) {
            transactions.push_back(Transaction::deserialize(line));
        }
    }
}

void TransactionService::saveTransactions() {
    std::vector<std::string> lines;
    for (const auto& trans : transactions) {
        lines.push_back(trans.serialize());
    }
    FileHandler::writeAllLines(dataFile, lines);
}

void TransactionService::addTransaction(Transaction& trans) {
    transactions.push_back(trans);
    saveTransactions();
}

bool TransactionService::deposit(const std::string& accountNumber, double amount,
                                  const std::string& description) {
    if (!Validator::isValidAmount(amount)) {
        return false;
    }
    
    Account* account = accountService->getAccountByNumber(accountNumber);
    if (account == nullptr || !account->getIsActive()) {
        return false;
    }
    
    // Create transaction record
    Transaction trans(accountNumber, "", TransactionType::DEPOSIT, amount, description);
    
    // Perform deposit
    if (account->deposit(amount)) {
        trans.setIsSuccess(true);
        accountService->updateAccount(*account);
        addTransaction(trans);
        return true;
    }
    
    trans.setIsSuccess(false);
    addTransaction(trans);
    return false;
}

bool TransactionService::withdraw(const std::string& accountNumber, double amount,
                                   const std::string& description) {
    if (!Validator::isValidAmount(amount)) {
        return false;
    }
    
    Account* account = accountService->getAccountByNumber(accountNumber);
    if (account == nullptr || !account->getIsActive()) {
        return false;
    }
    
    // Create transaction record
    Transaction trans(accountNumber, "", TransactionType::WITHDRAW, amount, description);
    
    // Check sufficient balance
    if (account->getBalance() < amount) {
        trans.setIsSuccess(false);
        addTransaction(trans);
        return false;
    }
    
    // Perform withdrawal
    if (account->withdraw(amount)) {
        trans.setIsSuccess(true);
        accountService->updateAccount(*account);
        addTransaction(trans);
        return true;
    }
    
    trans.setIsSuccess(false);
    addTransaction(trans);
    return false;
}

bool TransactionService::transfer(const std::string& fromAcc, const std::string& toAcc,
                                   double amount, const std::string& description) {
    if (!Validator::isValidAmount(amount)) {
        return false;
    }
    
    Account* sourceAccount = accountService->getAccountByNumber(fromAcc);
    Account* destAccount = accountService->getAccountByNumber(toAcc);
    
    if (sourceAccount == nullptr || !sourceAccount->getIsActive()) {
        return false;
    }
    
    if (destAccount == nullptr || !destAccount->getIsActive()) {
        return false;
    }
    
    if (fromAcc == toAcc) {
        return false; // Cannot transfer to the same account
    }
    
    // Create transaction record
    Transaction trans(fromAcc, toAcc, TransactionType::TRANSFER, amount, description);
    
    // Check sufficient balance
    if (sourceAccount->getBalance() < amount) {
        trans.setIsSuccess(false);
        addTransaction(trans);
        return false;
    }
    
    // Perform transfer
    if (sourceAccount->withdraw(amount) && destAccount->deposit(amount)) {
        trans.setIsSuccess(true);
        accountService->updateAccount(*sourceAccount);
        accountService->updateAccount(*destAccount);
        addTransaction(trans);
        return true;
    }
    
    // Rollback if partial failure (shouldn't happen with our simple implementation)
    trans.setIsSuccess(false);
    addTransaction(trans);
    return false;
}

std::vector<Transaction> TransactionService::getTransactionHistory(const std::string& accountNumber) {
    std::vector<Transaction> history;
    
    for (const auto& trans : transactions) {
        if (trans.getFromAccount() == accountNumber || 
            trans.getToAccount() == accountNumber) {
            history.push_back(trans);
        }
    }
    
    // Sort by timestamp (most recent first)
    std::sort(history.begin(), history.end(), 
        [](const Transaction& a, const Transaction& b) {
            return a.getTimestamp() > b.getTimestamp();
        });
    
    return history;
}

Transaction* TransactionService::getTransactionById(const std::string& transactionId) {
    for (auto& trans : transactions) {
        if (trans.getTransactionId() == transactionId) {
            return &trans;
        }
    }
    return nullptr;
}
