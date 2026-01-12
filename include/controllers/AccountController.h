#ifndef ACCOUNT_CONTROLLER_H
#define ACCOUNT_CONTROLLER_H

#include <string>
#include "services/AccountService.h"
#include "models/User.h"

class AccountController {
private:
    AccountService* accountService;
    User* currentUser;

public:
    AccountController(AccountService* service);
    
    void setCurrentUser(User* user);
    void createAccount();
    void viewBalance();
    void listAccounts();
    void closeAccount();
};

#endif // ACCOUNT_CONTROLLER_H
