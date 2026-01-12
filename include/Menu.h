#ifndef MENU_H
#define MENU_H

#include "controllers/AuthController.h"
#include "controllers/AccountController.h"
#include "controllers/TransactionController.h"
#include "services/UserService.h"
#include "services/AccountService.h"
#include "services/TransactionService.h"

class Menu {
private:
    UserService* userService;
    AccountService* accountService;
    TransactionService* transactionService;
    
    AuthController* authController;
    AccountController* accountController;
    TransactionController* transactionController;
    
    bool running;
    
    void clearScreen();
    void pauseScreen();
    void printHeader(const std::string& title);
    void printLine(char c = '-', int length = 50);
    
    void showLoginMenu();
    void showMainMenu();
    void showAccountMenu();
    void showTransactionMenu();

public:
    Menu();
    ~Menu();
    
    void run();
};

#endif // MENU_H
