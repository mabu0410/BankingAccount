#include "Menu.h"
#include <iostream>
#include <limits>

#ifdef _WIN32
    #define CLEAR_SCREEN "cls"
#else
    #define CLEAR_SCREEN "clear"
#endif

Menu::Menu() : running(true) {
    userService = new UserService();
    accountService = new AccountService();
    transactionService = new TransactionService(accountService);
    
    authController = new AuthController(userService);
    accountController = new AccountController(accountService);
    transactionController = new TransactionController(transactionService, accountService);
}

Menu::~Menu() {
    delete transactionController;
    delete accountController;
    delete authController;
    delete transactionService;
    delete accountService;
    delete userService;
}

void Menu::clearScreen() {
    system(CLEAR_SCREEN);
}

void Menu::pauseScreen() {
    std::cout << "\nNhấn Enter để tiếp tục...";
    std::cin.get();
}

void Menu::printHeader(const std::string& title) {
    std::cout << "\n";
    printLine('=', 50);
    std::cout << "  " << title << "\n";
    printLine('=', 50);
    std::cout << "\n";
}

void Menu::printLine(char c, int length) {
    std::cout << std::string(length, c) << "\n";
}

void Menu::showLoginMenu() {
    int choice;
    
    while (!authController->isLoggedIn() && running) {
        clearScreen();
        printHeader("HỆ THỐNG QUẢN LÝ TÀI KHOẢN NGÂN HÀNG");
        
        std::cout << "  1. Đăng nhập\n";
        std::cout << "  2. Đăng ký tài khoản mới\n";
        std::cout << "  0. Thoát\n";
        std::cout << "\n  Nhập lựa chọn: ";
        
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        switch (choice) {
            case 1:
                if (authController->login()) {
                    accountController->setCurrentUser(authController->getCurrentUser());
                    transactionController->setCurrentUser(authController->getCurrentUser());
                }
                pauseScreen();
                break;
            case 2:
                authController->registerUser();
                pauseScreen();
                break;
            case 0:
                running = false;
                std::cout << "\n👋 Cảm ơn bạn đã sử dụng hệ thống. Tạm biệt!\n";
                break;
            default:
                std::cout << "❌ Lựa chọn không hợp lệ!\n";
                pauseScreen();
        }
    }
}

void Menu::showMainMenu() {
    int choice;
    
    while (authController->isLoggedIn() && running) {
        clearScreen();
        printHeader("MENU CHÍNH");
        
        std::cout << "  Xin chào, " << authController->getCurrentUser()->getFullName() << "!\n\n";
        
        std::cout << "  1. Quản lý tài khoản ngân hàng\n";
        std::cout << "  2. Giao dịch\n";
        std::cout << "  3. Xem lịch sử giao dịch\n";
        std::cout << "  4. Thông tin cá nhân\n";
        std::cout << "  5. Đổi mật khẩu\n";
        std::cout << "  0. Đăng xuất\n";
        std::cout << "\n  Nhập lựa chọn: ";
        
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        switch (choice) {
            case 1:
                showAccountMenu();
                break;
            case 2:
                showTransactionMenu();
                break;
            case 3:
                transactionController->viewTransactionHistory();
                pauseScreen();
                break;
            case 4:
                authController->viewProfile();
                pauseScreen();
                break;
            case 5:
                authController->changePassword();
                pauseScreen();
                break;
            case 0:
                authController->logout();
                accountController->setCurrentUser(nullptr);
                transactionController->setCurrentUser(nullptr);
                pauseScreen();
                break;
            default:
                std::cout << "❌ Lựa chọn không hợp lệ!\n";
                pauseScreen();
        }
    }
}

void Menu::showAccountMenu() {
    int choice;
    bool back = false;
    
    while (!back) {
        clearScreen();
        printHeader("QUẢN LÝ TÀI KHOẢN NGÂN HÀNG");
        
        std::cout << "  1. Tạo tài khoản mới\n";
        std::cout << "  2. Xem danh sách tài khoản\n";
        std::cout << "  3. Xem số dư\n";
        std::cout << "  4. Đóng tài khoản\n";
        std::cout << "  0. Quay lại\n";
        std::cout << "\n  Nhập lựa chọn: ";
        
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        switch (choice) {
            case 1:
                accountController->createAccount();
                pauseScreen();
                break;
            case 2:
                accountController->listAccounts();
                pauseScreen();
                break;
            case 3:
                accountController->viewBalance();
                pauseScreen();
                break;
            case 4:
                accountController->closeAccount();
                pauseScreen();
                break;
            case 0:
                back = true;
                break;
            default:
                std::cout << "❌ Lựa chọn không hợp lệ!\n";
                pauseScreen();
        }
    }
}

void Menu::showTransactionMenu() {
    int choice;
    bool back = false;
    
    while (!back) {
        clearScreen();
        printHeader("GIAO DỊCH");
        
        std::cout << "  1. Gửi tiền\n";
        std::cout << "  2. Rút tiền\n";
        std::cout << "  3. Chuyển khoản\n";
        std::cout << "  0. Quay lại\n";
        std::cout << "\n  Nhập lựa chọn: ";
        
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        switch (choice) {
            case 1:
                transactionController->deposit();
                pauseScreen();
                break;
            case 2:
                transactionController->withdraw();
                pauseScreen();
                break;
            case 3:
                transactionController->transfer();
                pauseScreen();
                break;
            case 0:
                back = true;
                break;
            default:
                std::cout << "❌ Lựa chọn không hợp lệ!\n";
                pauseScreen();
        }
    }
}

void Menu::run() {
    while (running) {
        if (!authController->isLoggedIn()) {
            showLoginMenu();
        } else {
            showMainMenu();
        }
    }
}
