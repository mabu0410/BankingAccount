#include "controllers/TransactionController.h"
#include "utils/Helper.h"
#include "utils/Validator.h"
#include <iostream>
#include <iomanip>
#include <vector>

TransactionController::TransactionController(TransactionService* transService, 
                                              AccountService* accService)
    : transactionService(transService), accountService(accService), currentUser(nullptr) {}

void TransactionController::setCurrentUser(User* user) {
    currentUser = user;
}

void TransactionController::deposit() {
    if (currentUser == nullptr) {
        std::cout << "❌ Vui lòng đăng nhập trước!\n";
        return;
    }
    
    std::vector<Account> accounts = accountService->getAccountsByUserId(currentUser->getUserId());
    if (accounts.empty()) {
        std::cout << "\n⚠️ Bạn chưa có tài khoản ngân hàng nào. Vui lòng tạo tài khoản mới.\n";
        return;
    }
    
    std::cout << "\n===== GỬI TIỀN =====\n\n";
    std::cout << "Danh sách tài khoản của bạn:\n";
    for (const auto& acc : accounts) {
        std::cout << "  • " << acc.getAccountNumber() << " (" << acc.getTypeString() 
                  << ") - Số dư: " << Helper::formatCurrency(acc.getBalance()) << "\n";
    }
    
    std::cout << "\nNhập số tài khoản: ";
    std::string accNumber;
    std::getline(std::cin, accNumber);
    accNumber = Helper::trim(accNumber);
    
    Account* account = accountService->getAccountByNumber(accNumber);
    if (account == nullptr || account->getUserId() != currentUser->getUserId()) {
        std::cout << "❌ Không tìm thấy tài khoản hoặc tài khoản không thuộc về bạn!\n";
        return;
    }
    
    std::cout << "Nhập số tiền gửi (VND): ";
    double amount;
    std::cin >> amount;
    std::cin.ignore();
    
    if (!Validator::isValidAmount(amount)) {
        std::cout << "❌ Số tiền không hợp lệ!\n";
        return;
    }
    
    std::cout << "Nhập mô tả (Enter để bỏ qua): ";
    std::string description;
    std::getline(std::cin, description);
    if (description.empty()) {
        description = "Nạp tiền mặt";
    }
    
    std::cout << "\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
    std::cout << "Xác nhận giao dịch:\n";
    std::cout << "  Tài khoản: " << accNumber << "\n";
    std::cout << "  Số tiền:   " << Helper::formatCurrency(amount) << "\n";
    std::cout << "  Mô tả:     " << description << "\n";
    std::cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
    std::cout << "Xác nhận? (y/n): ";
    
    std::string confirm;
    std::getline(std::cin, confirm);
    
    if (confirm == "y" || confirm == "Y") {
        if (transactionService->deposit(accNumber, amount, description)) {
            std::cout << "\n✅ Gửi tiền thành công!\n";
            std::cout << "Số dư mới: " << Helper::formatCurrency(account->getBalance()) << "\n";
        } else {
            std::cout << "❌ Gửi tiền thất bại!\n";
        }
    } else {
        std::cout << "Đã hủy giao dịch.\n";
    }
}

void TransactionController::withdraw() {
    if (currentUser == nullptr) {
        std::cout << "❌ Vui lòng đăng nhập trước!\n";
        return;
    }
    
    std::vector<Account> accounts = accountService->getAccountsByUserId(currentUser->getUserId());
    if (accounts.empty()) {
        std::cout << "\n⚠️ Bạn chưa có tài khoản ngân hàng nào.\n";
        return;
    }
    
    std::cout << "\n===== RÚT TIỀN =====\n\n";
    std::cout << "Danh sách tài khoản của bạn:\n";
    for (const auto& acc : accounts) {
        std::cout << "  • " << acc.getAccountNumber() << " (" << acc.getTypeString() 
                  << ") - Số dư: " << Helper::formatCurrency(acc.getBalance()) << "\n";
    }
    
    std::cout << "\nNhập số tài khoản: ";
    std::string accNumber;
    std::getline(std::cin, accNumber);
    accNumber = Helper::trim(accNumber);
    
    Account* account = accountService->getAccountByNumber(accNumber);
    if (account == nullptr || account->getUserId() != currentUser->getUserId()) {
        std::cout << "❌ Không tìm thấy tài khoản hoặc tài khoản không thuộc về bạn!\n";
        return;
    }
    
    std::cout << "Số dư hiện tại: " << Helper::formatCurrency(account->getBalance()) << "\n";
    std::cout << "Nhập số tiền rút (VND): ";
    double amount;
    std::cin >> amount;
    std::cin.ignore();
    
    if (!Validator::isValidAmount(amount)) {
        std::cout << "❌ Số tiền không hợp lệ!\n";
        return;
    }
    
    if (amount > account->getBalance()) {
        std::cout << "❌ Số dư không đủ!\n";
        return;
    }
    
    std::cout << "Nhập mô tả (Enter để bỏ qua): ";
    std::string description;
    std::getline(std::cin, description);
    if (description.empty()) {
        description = "Rút tiền mặt";
    }
    
    std::cout << "\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
    std::cout << "Xác nhận giao dịch:\n";
    std::cout << "  Tài khoản: " << accNumber << "\n";
    std::cout << "  Số tiền:   " << Helper::formatCurrency(amount) << "\n";
    std::cout << "  Mô tả:     " << description << "\n";
    std::cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
    std::cout << "Xác nhận? (y/n): ";
    
    std::string confirm;
    std::getline(std::cin, confirm);
    
    if (confirm == "y" || confirm == "Y") {
        if (transactionService->withdraw(accNumber, amount, description)) {
            std::cout << "\n✅ Rút tiền thành công!\n";
            std::cout << "Số dư mới: " << Helper::formatCurrency(account->getBalance()) << "\n";
        } else {
            std::cout << "❌ Rút tiền thất bại!\n";
        }
    } else {
        std::cout << "Đã hủy giao dịch.\n";
    }
}

void TransactionController::transfer() {
    if (currentUser == nullptr) {
        std::cout << "❌ Vui lòng đăng nhập trước!\n";
        return;
    }
    
    std::vector<Account> accounts = accountService->getAccountsByUserId(currentUser->getUserId());
    if (accounts.empty()) {
        std::cout << "\n⚠️ Bạn chưa có tài khoản ngân hàng nào.\n";
        return;
    }
    
    std::cout << "\n===== CHUYỂN KHOẢN =====\n\n";
    std::cout << "Danh sách tài khoản của bạn:\n";
    for (const auto& acc : accounts) {
        std::cout << "  • " << acc.getAccountNumber() << " (" << acc.getTypeString() 
                  << ") - Số dư: " << Helper::formatCurrency(acc.getBalance()) << "\n";
    }
    
    std::cout << "\nNhập số tài khoản nguồn: ";
    std::string fromAcc;
    std::getline(std::cin, fromAcc);
    fromAcc = Helper::trim(fromAcc);
    
    Account* sourceAccount = accountService->getAccountByNumber(fromAcc);
    if (sourceAccount == nullptr || sourceAccount->getUserId() != currentUser->getUserId()) {
        std::cout << "❌ Không tìm thấy tài khoản nguồn hoặc tài khoản không thuộc về bạn!\n";
        return;
    }
    
    std::cout << "Nhập số tài khoản đích: ";
    std::string toAcc;
    std::getline(std::cin, toAcc);
    toAcc = Helper::trim(toAcc);
    
    if (fromAcc == toAcc) {
        std::cout << "❌ Không thể chuyển tiền đến cùng một tài khoản!\n";
        return;
    }
    
    Account* destAccount = accountService->getAccountByNumber(toAcc);
    if (destAccount == nullptr || !destAccount->getIsActive()) {
        std::cout << "❌ Không tìm thấy tài khoản đích hoặc tài khoản không hoạt động!\n";
        return;
    }
    
    std::cout << "Số dư hiện tại: " << Helper::formatCurrency(sourceAccount->getBalance()) << "\n";
    std::cout << "Nhập số tiền chuyển (VND): ";
    double amount;
    std::cin >> amount;
    std::cin.ignore();
    
    if (!Validator::isValidAmount(amount)) {
        std::cout << "❌ Số tiền không hợp lệ!\n";
        return;
    }
    
    if (amount > sourceAccount->getBalance()) {
        std::cout << "❌ Số dư không đủ!\n";
        return;
    }
    
    std::cout << "Nhập nội dung chuyển khoản: ";
    std::string description;
    std::getline(std::cin, description);
    if (description.empty()) {
        description = "Chuyển khoản";
    }
    
    std::cout << "\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
    std::cout << "Xác nhận giao dịch:\n";
    std::cout << "  Từ tài khoản: " << fromAcc << "\n";
    std::cout << "  Đến tài khoản: " << toAcc << "\n";
    std::cout << "  Số tiền:       " << Helper::formatCurrency(amount) << "\n";
    std::cout << "  Nội dung:      " << description << "\n";
    std::cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
    std::cout << "Xác nhận? (y/n): ";
    
    std::string confirm;
    std::getline(std::cin, confirm);
    
    if (confirm == "y" || confirm == "Y") {
        if (transactionService->transfer(fromAcc, toAcc, amount, description)) {
            std::cout << "\n✅ Chuyển khoản thành công!\n";
            std::cout << "Số dư mới: " << Helper::formatCurrency(sourceAccount->getBalance()) << "\n";
        } else {
            std::cout << "❌ Chuyển khoản thất bại!\n";
        }
    } else {
        std::cout << "Đã hủy giao dịch.\n";
    }
}

void TransactionController::viewTransactionHistory() {
    if (currentUser == nullptr) {
        std::cout << "❌ Vui lòng đăng nhập trước!\n";
        return;
    }
    
    std::vector<Account> accounts = accountService->getAccountsByUserId(currentUser->getUserId());
    if (accounts.empty()) {
        std::cout << "\n⚠️ Bạn chưa có tài khoản ngân hàng nào.\n";
        return;
    }
    
    std::cout << "\n===== LỊCH SỬ GIAO DỊCH =====\n\n";
    std::cout << "Danh sách tài khoản của bạn:\n";
    for (const auto& acc : accounts) {
        std::cout << "  • " << acc.getAccountNumber() << "\n";
    }
    
    std::cout << "\nNhập số tài khoản (hoặc 'all' để xem tất cả): ";
    std::string input;
    std::getline(std::cin, input);
    input = Helper::trim(input);
    
    std::vector<Transaction> history;
    
    if (input == "all" || input == "ALL") {
        for (const auto& acc : accounts) {
            std::vector<Transaction> accHistory = 
                transactionService->getTransactionHistory(acc.getAccountNumber());
            history.insert(history.end(), accHistory.begin(), accHistory.end());
        }
    } else {
        Account* account = accountService->getAccountByNumber(input);
        if (account == nullptr || account->getUserId() != currentUser->getUserId()) {
            std::cout << "❌ Không tìm thấy tài khoản hoặc tài khoản không thuộc về bạn!\n";
            return;
        }
        history = transactionService->getTransactionHistory(input);
    }
    
    if (history.empty()) {
        std::cout << "\n⚠️ Không có lịch sử giao dịch.\n";
        return;
    }
    
    std::cout << "\n" << std::string(100, '=') << "\n";
    std::cout << std::left << std::setw(25) << "Thời gian"
              << std::setw(12) << "Loại"
              << std::setw(15) << "Từ TK"
              << std::setw(15) << "Đến TK"
              << std::setw(18) << "Số tiền"
              << std::setw(10) << "Trạng thái" << "\n";
    std::cout << std::string(100, '-') << "\n";
    
    for (const auto& trans : history) {
        std::cout << std::left << std::setw(25) << trans.getTimestamp()
                  << std::setw(12) << trans.getTypeString()
                  << std::setw(15) << trans.getFromAccount()
                  << std::setw(15) << (trans.getToAccount().empty() ? "-" : trans.getToAccount())
                  << std::setw(18) << Helper::formatCurrency(trans.getAmount())
                  << std::setw(10) << (trans.getIsSuccess() ? "✓" : "✗") << "\n";
    }
    
    std::cout << std::string(100, '=') << "\n";
    std::cout << "Tổng số giao dịch: " << history.size() << "\n";
}
