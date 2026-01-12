#ifndef TRANSACTION_SERVICE_H
#define TRANSACTION_SERVICE_H

#include <string>
#include <vector>
#include "models/Transaction.h"
#include "services/AccountService.h"

class TransactionService {
private:
    std::string dataFile;
    std::vector<Transaction> transactions;
    AccountService* accountService;
    
    void loadTransactions();
    void saveTransactions();
    void addTransaction(Transaction& trans);

public:
    TransactionService(AccountService* accService);
    
    bool deposit(const std::string& accountNumber, double amount, const std::string& description);
    bool withdraw(const std::string& accountNumber, double amount, const std::string& description);
    bool transfer(const std::string& fromAcc, const std::string& toAcc, 
                  double amount, const std::string& description);
    std::vector<Transaction> getTransactionHistory(const std::string& accountNumber);
    Transaction* getTransactionById(const std::string& transactionId);
};

#endif // TRANSACTION_SERVICE_H
