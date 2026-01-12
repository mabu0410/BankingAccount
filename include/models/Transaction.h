#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>

enum class TransactionType {
    DEPOSIT,
    WITHDRAW,
    TRANSFER
};

class Transaction {
private:
    std::string transactionId;
    std::string fromAccount;
    std::string toAccount;
    TransactionType type;
    double amount;
    std::string description;
    std::string timestamp;
    bool isSuccess;

public:
    Transaction();
    Transaction(const std::string& fromAcc, const std::string& toAcc,
                TransactionType type, double amount, const std::string& desc);
    
    // Getters
    std::string getTransactionId() const;
    std::string getFromAccount() const;
    std::string getToAccount() const;
    TransactionType getType() const;
    std::string getTypeString() const;
    double getAmount() const;
    std::string getDescription() const;
    std::string getTimestamp() const;
    bool getIsSuccess() const;
    
    // Setters
    void setTransactionId(const std::string& id);
    void setFromAccount(const std::string& acc);
    void setToAccount(const std::string& acc);
    void setType(TransactionType t);
    void setAmount(double amt);
    void setDescription(const std::string& desc);
    void setTimestamp(const std::string& ts);
    void setIsSuccess(bool success);
    
    // Serialization
    std::string serialize() const;
    static Transaction deserialize(const std::string& data);
    static TransactionType stringToType(const std::string& typeStr);
};

#endif // TRANSACTION_H
