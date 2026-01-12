#include "controllers/AccountController.h"
#include "utils/Helper.h"
#include <iostream>
#include <iomanip>

AccountController::AccountController(AccountService* service)
    : accountService(service), currentUser(nullptr) {}

void AccountController::setCurrentUser(User* user) {
    currentUser = user;
}

void AccountController::createAccount() {
    if (currentUser == nullptr) {
        std::cout << "❌ Vui lòng đăng nhập trước!\n";
        return;
    }
    
    std::cout << "\n===== TẠO TÀI KHOẢN NGÂN HÀNG MỚI =====\n\n";
    std::cout << "Chọn loại tài khoản:\n";
    std::cout << "1. Tài khoản tiết kiệm (SAVINGS) - Lãi suất: 0.5%/năm\n";
    std::cout << "2. Tài khoản thanh toán (CHECKING) - Lãi suất: 0.1%/năm\n";
    std::cout << "3. Tài khoản tiền gửi có kỳ hạn (FIXED_DEPOSIT) - Lãi suất: 1.5%/năm\n";
    std::cout << "\nNhập lựa chọn (1-3): ";
    
    int choice;
    std::cin >> choice;
    std::cin.ignore();
    
    AccountType type;
    switch (choice) {
        case 1:
            type = AccountType::SAVINGS;
            break;
        case 2:
            type = AccountType::CHECKING;
            break;
        case 3:
            type = AccountType::FIXED_DEPOSIT;
            break;
        default:
            std::cout << "❌ Lựa chọn không hợp lệ!\n";
            return;
    }
    
    Account* newAccount = accountService->createAccount(currentUser->getUserId(), type);
    
    if (newAccount != nullptr) {
        std::cout << "\n✅ Tạo tài khoản thành công!\n";
        std::cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
        std::cout << "Số tài khoản: " << newAccount->getAccountNumber() << "\n";
        std::cout << "Loại:         " << newAccount->getTypeString() << "\n";
        std::cout << "Lãi suất:     " << newAccount->getInterestRate() << "% /năm\n";
        std::cout << "Số dư:        " << Helper::formatCurrency(newAccount->getBalance()) << "\n";
        std::cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
    } else {
        std::cout << "❌ Tạo tài khoản thất bại!\n";
    }
}

void AccountController::viewBalance() {
    if (currentUser == nullptr) {
        std::cout << "❌ Vui lòng đăng nhập trước!\n";
        return;
    }
    
    std::vector<Account> accounts = accountService->getAccountsByUserId(currentUser->getUserId());
    
    if (accounts.empty()) {
        std::cout << "\n⚠️ Bạn chưa có tài khoản ngân hàng nào. Vui lòng tạo tài khoản mới.\n";
        return;
    }
    
    std::cout << "\n===== SỐ DƯ TÀI KHOẢN =====\n\n";
    std::cout << "Nhập số tài khoản cần xem (hoặc 'all' để xem tất cả): ";
    
    std::string input;
    std::getline(std::cin, input);
    input = Helper::trim(input);
    
    if (input == "all" || input == "ALL") {
        listAccounts();
    } else {
        Account* account = accountService->getAccountByNumber(input);
        if (account != nullptr && account->getUserId() == currentUser->getUserId()) {
            std::cout << "\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
            std::cout << "Số tài khoản: " << account->getAccountNumber() << "\n";
            std::cout << "Số dư:        " << Helper::formatCurrency(account->getBalance()) << "\n";
            std::cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
        } else {
            std::cout << "❌ Không tìm thấy tài khoản hoặc tài khoản không thuộc về bạn!\n";
        }
    }
}

void AccountController::listAccounts() {
    if (currentUser == nullptr) {
        std::cout << "❌ Vui lòng đăng nhập trước!\n";
        return;
    }
    
    std::vector<Account> accounts = accountService->getAccountsByUserId(currentUser->getUserId());
    
    if (accounts.empty()) {
        std::cout << "\n⚠️ Bạn chưa có tài khoản ngân hàng nào.\n";
        return;
    }
    
    std::cout << "\n===== DANH SÁCH TÀI KHOẢN =====\n\n";
    std::cout << std::left << std::setw(15) << "Số TK" 
              << std::setw(15) << "Loại" 
              << std::setw(20) << "Số dư"
              << std::setw(10) << "Lãi suất"
              << std::setw(15) << "Ngày mở" << "\n";
    std::cout << std::string(75, '-') << "\n";
    
    double totalBalance = 0;
    for (const auto& account : accounts) {
        std::cout << std::left << std::setw(15) << account.getAccountNumber()
                  << std::setw(15) << account.getTypeString()
                  << std::setw(20) << Helper::formatCurrency(account.getBalance())
                  << std::setw(10) << std::fixed << std::setprecision(1) 
                  << account.getInterestRate() << "%"
                  << std::setw(15) << account.getCreatedAt() << "\n";
        totalBalance += account.getBalance();
    }
    
    std::cout << std::string(75, '-') << "\n";
    std::cout << "Tổng số tài khoản: " << accounts.size() << "\n";
    std::cout << "Tổng số dư:        " << Helper::formatCurrency(totalBalance) << "\n";
}

void AccountController::closeAccount() {
    if (currentUser == nullptr) {
        std::cout << "❌ Vui lòng đăng nhập trước!\n";
        return;
    }
    
    listAccounts();
    
    std::cout << "\n===== ĐÓNG TÀI KHOẢN =====\n\n";
    std::cout << "⚠️ Lưu ý: Chỉ có thể đóng tài khoản có số dư bằng 0.\n";
    std::cout << "Nhập số tài khoản cần đóng: ";
    
    std::string accNumber;
    std::getline(std::cin, accNumber);
    accNumber = Helper::trim(accNumber);
    
    Account* account = accountService->getAccountByNumber(accNumber);
    if (account == nullptr || account->getUserId() != currentUser->getUserId()) {
        std::cout << "❌ Không tìm thấy tài khoản hoặc tài khoản không thuộc về bạn!\n";
        return;
    }
    
    if (account->getBalance() > 0) {
        std::cout << "❌ Không thể đóng tài khoản có số dư " 
                  << Helper::formatCurrency(account->getBalance()) << "!\n";
        std::cout << "Vui lòng rút hết tiền trước khi đóng tài khoản.\n";
        return;
    }
    
    std::cout << "Bạn có chắc chắn muốn đóng tài khoản " << accNumber << "? (y/n): ";
    std::string confirm;
    std::getline(std::cin, confirm);
    
    if (confirm == "y" || confirm == "Y") {
        if (accountService->closeAccount(accNumber)) {
            std::cout << "\n✅ Đóng tài khoản thành công!\n";
        } else {
            std::cout << "❌ Đóng tài khoản thất bại!\n";
        }
    } else {
        std::cout << "Đã hủy thao tác.\n";
    }
}
