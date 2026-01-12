#include "models/Transaction.h"
#include "utils/Helper.h"
#include <sstream>

Transaction::Transaction() : amount(0.0), isSuccess(false) {
    transactionId = Helper::generateTransactionId();
    timestamp = Helper::getCurrentTimestamp();
}

Transaction::Transaction(const std::string& fromAcc, const std::string& toAcc,
                         TransactionType type, double amount, const std::string& desc)
    : fromAccount(fromAcc), toAccount(toAcc), type(type), 
      amount(amount), description(desc), isSuccess(false) {
    transactionId = Helper::generateTransactionId();
    timestamp = Helper::getCurrentTimestamp();
}

// Getters
std::string Transaction::getTransactionId() const { return transactionId; }
std::string Transaction::getFromAccount() const { return fromAccount; }
std::string Transaction::getToAccount() const { return toAccount; }
TransactionType Transaction::getType() const { return type; }
double Transaction::getAmount() const { return amount; }
std::string Transaction::getDescription() const { return description; }
std::string Transaction::getTimestamp() const { return timestamp; }
bool Transaction::getIsSuccess() const { return isSuccess; }

std::string Transaction::getTypeString() const {
    switch (type) {
        case TransactionType::DEPOSIT: return "DEPOSIT";
        case TransactionType::WITHDRAW: return "WITHDRAW";
        case TransactionType::TRANSFER: return "TRANSFER";
        default: return "UNKNOWN";
    }
}

// Setters
void Transaction::setTransactionId(const std::string& id) { transactionId = id; }
void Transaction::setFromAccount(const std::string& acc) { fromAccount = acc; }
void Transaction::setToAccount(const std::string& acc) { toAccount = acc; }
void Transaction::setType(TransactionType t) { type = t; }
void Transaction::setAmount(double amt) { amount = amt; }
void Transaction::setDescription(const std::string& desc) { description = desc; }
void Transaction::setTimestamp(const std::string& ts) { timestamp = ts; }
void Transaction::setIsSuccess(bool success) { isSuccess = success; }

// Serialization - Format: transactionId|fromAccount|toAccount|type|amount|description|timestamp|isSuccess
std::string Transaction::serialize() const {
    std::stringstream ss;
    ss << transactionId << "|" << fromAccount << "|" << toAccount << "|"
       << getTypeString() << "|" << amount << "|" << description << "|"
       << timestamp << "|" << (isSuccess ? "1" : "0");
    return ss.str();
}

Transaction Transaction::deserialize(const std::string& data) {
    Transaction trans;
    std::stringstream ss(data);
    std::string token;
    int field = 0;
    
    while (std::getline(ss, token, '|')) {
        switch (field) {
            case 0: trans.transactionId = token; break;
            case 1: trans.fromAccount = token; break;
            case 2: trans.toAccount = token; break;
            case 3: trans.type = stringToType(token); break;
            case 4: trans.amount = std::stod(token); break;
            case 5: trans.description = token; break;
            case 6: trans.timestamp = token; break;
            case 7: trans.isSuccess = (token == "1"); break;
        }
        field++;
    }
    
    return trans;
}

TransactionType Transaction::stringToType(const std::string& typeStr) {
    if (typeStr == "DEPOSIT") return TransactionType::DEPOSIT;
    if (typeStr == "WITHDRAW") return TransactionType::WITHDRAW;
    if (typeStr == "TRANSFER") return TransactionType::TRANSFER;
    return TransactionType::DEPOSIT; // Default
}
