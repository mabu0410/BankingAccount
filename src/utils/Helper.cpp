#include "utils/Helper.h"
#include <chrono>
#include <random>
#include <sstream>
#include <iomanip>
#include <algorithm>

std::string Helper::generateUserId() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis(10000, 99999);
    
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    
    std::stringstream ss;
    ss << "U" << std::put_time(std::localtime(&time), "%Y%m%d") << dis(gen);
    return ss.str();
}

std::string Helper::generateTransactionId() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis(100000, 999999);
    
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    
    std::stringstream ss;
    ss << "TX" << std::put_time(std::localtime(&time), "%Y%m%d%H%M%S") << dis(gen);
    return ss.str();
}

std::string Helper::generateAccountNumber() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis(0, 9);
    
    std::stringstream ss;
    for (int i = 0; i < 10; ++i) {
        ss << dis(gen);
    }
    return ss.str();
}

std::string Helper::hashPassword(const std::string& password) {
    // Simple hash function (for demonstration purposes)
    // In production, use a proper cryptographic library
    unsigned long hash = 5381;
    for (char c : password) {
        hash = ((hash << 5) + hash) + c;
    }
    
    std::stringstream ss;
    ss << std::hex << hash;
    return ss.str();
}

std::string Helper::getCurrentTimestamp() {
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

std::string Helper::getCurrentDate() {
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time), "%Y-%m-%d");
    return ss.str();
}

std::string Helper::formatCurrency(double amount) {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(0) << amount << " VND";
    return ss.str();
}

std::string Helper::trim(const std::string& str) {
    size_t first = str.find_first_not_of(' ');
    if (std::string::npos == first) {
        return str;
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

std::string Helper::getDataPath() {
    return "data/";
}
