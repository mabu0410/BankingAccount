#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <string>

class Validator {
public:
    static bool isValidEmail(const std::string& email);
    static bool isValidPhone(const std::string& phone);
    static bool isValidPassword(const std::string& password);
    static bool isValidAmount(double amount);
    static bool isValidAccountNumber(const std::string& accNum);
    static bool isValidUsername(const std::string& username);
};

#endif // VALIDATOR_H
