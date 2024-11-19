#ifndef TRANSACTION_H
#define TRANSACTION_H
#include "pch.h"
typedef std::chrono::system_clock::time_point time_point;

class Transaction {
    int64_t userId = 0;
    std::string category;
    double amount = 0.0;
    time_point date;

public:
    Transaction() = default;

    Transaction(int64_t userId, std::string category, double amount, time_point date);

    Transaction(const Transaction &other) = default;

    Transaction(Transaction &&other) = default;

    Transaction &operator=(const Transaction &other) = default;

    Transaction &operator=(Transaction &&other) = default;

    bool operator==(const Transaction &other) const;


    [[nodiscard]] int64_t getUserId() const;

    [[nodiscard]] std::string getCategory() const;

    [[nodiscard]] double getAmount() const;

    [[nodiscard]] time_point getDate() const;

    void setUserId(int64_t userId);

    void setCategory(std::string category);

    void setAmount(double amount);

    void setTimePoint(time_point date);

    void setTimePoint(const std::string &date);

    static std::string convertTimeToString(time_point time);

    static std::chrono::system_clock::time_point convertStringToTimePoint(const std::string &timeString,
                                                                          const std::string &format = "%d.%m.%Y");
        [[nodiscard]] std::string toString() const;
    };
#endif //TRANSACTION_H
