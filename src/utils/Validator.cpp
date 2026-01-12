#include "utils/Validator.h"
#include <regex>
#include <algorithm>

bool Validator::isValidEmail(const std::string& email) {
    // Basic email validation regex
    const std::regex pattern(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
    return std::regex_match(email, pattern);
}

bool Validator::isValidPhone(const std::string& phone) {
    // Vietnamese phone format: starts with 0, 10-11 digits
    if (phone.length() < 10 || phone.length() > 11) {
        return false;
    }
    
    if (phone[0] != '0') {
        return false;
    }
    
    return std::all_of(phone.begin(), phone.end(), ::isdigit);
}

bool Validator::isValidPassword(const std::string& password) {
    // Password must be at least 6 characters
    return password.length() >= 6;
}

bool Validator::isValidAmount(double amount) {
    // Amount must be positive
    return amount > 0;
}

bool Validator::isValidAccountNumber(const std::string& accNum) {
    // Account number must be 10 digits
    if (accNum.length() != 10) {
        return false;
    }
    
    return std::all_of(accNum.begin(), accNum.end(), ::isdigit);
}

bool Validator::isValidUsername(const std::string& username) {
    // Username must be 3-20 characters, alphanumeric and underscore only
    if (username.length() < 3 || username.length() > 20) {
        return false;
    }
    
    return std::all_of(username.begin(), username.end(), [](char c) {
        return std::isalnum(c) || c == '_';
    });
}
