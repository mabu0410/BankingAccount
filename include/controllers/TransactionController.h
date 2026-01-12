#ifndef TRANSACTION_CONTROLLER_H
#define TRANSACTION_CONTROLLER_H

#include <string>
#include "services/TransactionService.h"
#include "services/AccountService.h"
#include "models/User.h"

class TransactionController {
private:
    TransactionService* transactionService;
    AccountService* accountService;
    User* currentUser;

public:
    TransactionController(TransactionService* transService, AccountService* accService);
    
    void setCurrentUser(User* user);
    void deposit();
    void withdraw();
    void transfer();
    void viewTransactionHistory();
};

#endif // TRANSACTION_CONTROLLER_H
