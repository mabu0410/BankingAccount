#include "controllers/AuthController.h"
#include "utils/Validator.h"
#include "utils/Helper.h"
#include <iostream>
#include <limits>

AuthController::AuthController(UserService* service) 
    : userService(service), currentUser(nullptr) {}

bool AuthController::registerUser() {
    std::string username, password, confirmPassword, fullName, phone, email;
    
    std::cout << "\n===== ĐĂNG KÝ TÀI KHOẢN MỚI =====\n\n";
    
    std::cout << "Nhập tên đăng nhập (3-20 ký tự, chữ và số): ";
    std::getline(std::cin, username);
    username = Helper::trim(username);
    
    if (!Validator::isValidUsername(username)) {
        std::cout << "❌ Tên đăng nhập không hợp lệ! (3-20 ký tự, chỉ chữ cái, số và _)\n";
        return false;
    }
    
    if (userService->usernameExists(username)) {
        std::cout << "❌ Tên đăng nhập đã tồn tại!\n";
        return false;
    }
    
    std::cout << "Nhập mật khẩu (ít nhất 6 ký tự): ";
    std::getline(std::cin, password);
    
    if (!Validator::isValidPassword(password)) {
        std::cout << "❌ Mật khẩu phải có ít nhất 6 ký tự!\n";
        return false;
    }
    
    std::cout << "Xác nhận mật khẩu: ";
    std::getline(std::cin, confirmPassword);
    
    if (password != confirmPassword) {
        std::cout << "❌ Mật khẩu xác nhận không khớp!\n";
        return false;
    }
    
    std::cout << "Nhập họ và tên: ";
    std::getline(std::cin, fullName);
    fullName = Helper::trim(fullName);
    
    if (fullName.empty()) {
        std::cout << "❌ Họ và tên không được để trống!\n";
        return false;
    }
    
    std::cout << "Nhập số điện thoại (10-11 số, bắt đầu bằng 0): ";
    std::getline(std::cin, phone);
    phone = Helper::trim(phone);
    
    if (!Validator::isValidPhone(phone)) {
        std::cout << "❌ Số điện thoại không hợp lệ!\n";
        return false;
    }
    
    std::cout << "Nhập email: ";
    std::getline(std::cin, email);
    email = Helper::trim(email);
    
    if (!Validator::isValidEmail(email)) {
        std::cout << "❌ Email không hợp lệ!\n";
        return false;
    }
    
    if (userService->registerUser(username, password, fullName, phone, email)) {
        std::cout << "\n✅ Đăng ký thành công! Vui lòng đăng nhập.\n";
        return true;
    }
    
    std::cout << "❌ Đăng ký thất bại! Vui lòng thử lại.\n";
    return false;
}

bool AuthController::login() {
    std::string username, password;
    
    std::cout << "\n===== ĐĂNG NHẬP =====\n\n";
    
    std::cout << "Tên đăng nhập: ";
    std::getline(std::cin, username);
    username = Helper::trim(username);
    
    std::cout << "Mật khẩu: ";
    std::getline(std::cin, password);
    
    currentUser = userService->login(username, password);
    
    if (currentUser != nullptr) {
        std::cout << "\n✅ Đăng nhập thành công! Chào mừng " << currentUser->getFullName() << "!\n";
        return true;
    }
    
    std::cout << "❌ Tên đăng nhập hoặc mật khẩu không đúng!\n";
    return false;
}

void AuthController::logout() {
    if (currentUser != nullptr) {
        std::cout << "\n✅ Đăng xuất thành công! Tạm biệt " << currentUser->getFullName() << "!\n";
        currentUser = nullptr;
    }
}

bool AuthController::changePassword() {
    if (currentUser == nullptr) {
        std::cout << "❌ Vui lòng đăng nhập trước!\n";
        return false;
    }
    
    std::string oldPass, newPass, confirmPass;
    
    std::cout << "\n===== ĐỔI MẬT KHẨU =====\n\n";
    
    std::cout << "Nhập mật khẩu hiện tại: ";
    std::getline(std::cin, oldPass);
    
    std::cout << "Nhập mật khẩu mới (ít nhất 6 ký tự): ";
    std::getline(std::cin, newPass);
    
    if (!Validator::isValidPassword(newPass)) {
        std::cout << "❌ Mật khẩu mới phải có ít nhất 6 ký tự!\n";
        return false;
    }
    
    std::cout << "Xác nhận mật khẩu mới: ";
    std::getline(std::cin, confirmPass);
    
    if (newPass != confirmPass) {
        std::cout << "❌ Mật khẩu xác nhận không khớp!\n";
        return false;
    }
    
    if (userService->changePassword(currentUser->getUserId(), oldPass, newPass)) {
        std::cout << "\n✅ Đổi mật khẩu thành công!\n";
        return true;
    }
    
    std::cout << "❌ Mật khẩu hiện tại không đúng!\n";
    return false;
}

void AuthController::viewProfile() {
    if (currentUser == nullptr) {
        std::cout << "❌ Vui lòng đăng nhập trước!\n";
        return;
    }
    
    std::cout << "\n===== THÔNG TIN CÁ NHÂN =====\n\n";
    std::cout << "ID:             " << currentUser->getUserId() << "\n";
    std::cout << "Tên đăng nhập:  " << currentUser->getUsername() << "\n";
    std::cout << "Họ và tên:      " << currentUser->getFullName() << "\n";
    std::cout << "Số điện thoại:  " << currentUser->getPhoneNumber() << "\n";
    std::cout << "Email:          " << currentUser->getEmail() << "\n";
    std::cout << "Ngày tạo:       " << currentUser->getCreatedAt() << "\n";
}

User* AuthController::getCurrentUser() {
    return currentUser;
}

bool AuthController::isLoggedIn() {
    return currentUser != nullptr;
}
