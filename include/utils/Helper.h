#ifndef HELPER_H
#define HELPER_H

#include <string>

class Helper {
public:
    static std::string generateUserId();
    static std::string generateTransactionId();
    static std::string generateAccountNumber();
    static std::string hashPassword(const std::string& password);
    static std::string getCurrentTimestamp();
    static std::string getCurrentDate();
    static std::string formatCurrency(double amount);
    static std::string trim(const std::string& str);
    static std::string getDataPath();
};

#endif // HELPER_H
