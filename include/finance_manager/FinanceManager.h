#ifndef FINANCEMANAGER_H
#define FINANCEMANAGER_H
#include "pch.h"
#include "transactions/Transaction.h"

class FinanceManager {
    std::vector<Transaction> finance_manager;

    bool isMonthPassed(int64_t userId);

    bool isWeekPassed(int64_t userId);

public:
    explicit FinanceManager() = default;

    explicit FinanceManager(std::vector<Transaction> financeManager);

    void addTransaction(int64_t userId, const std::string &category, double amount);

    void removeTransaction(int64_t userId, const Transaction &transaction);

    void updateTransaction(int64_t userId, const Transaction &transaction);

    void updateTransactionByAmount(int64_t userId, const std::string &category, double newAmount);

    void updateTransactionByDate(int64_t userId, const std::string &category, time_point newDate);

    [[nodiscard]] std::vector<Transaction> getTransaction(int64_t userId) const;

    [[nodiscard]] std::unordered_map<std::string, double> getSumAllTransactionsByCategory(int64_t userId) const;

    [[nodiscard]] std::unordered_map<std::string, std::vector<double> > getAllTransactionsByCategory(
        int64_t userId) const;

    [[nodiscard]] double getTotalAmount(int64_t userId) const;

    [[nodiscard]] std::vector<Transaction> getTransactionByDateRange(int64_t userId, const time_point &startDate,
                                                                     const time_point &endDate) const;

    [[nodiscard]] std::vector<Transaction> getTransactionByCategory(int64_t userId, const std::string &category) const;

    [[nodiscard]] Transaction getLargestTransaction(int64_t userId) const;

    [[nodiscard]] Transaction getLargestTransactionByCategory(int64_t userId, const std::string &category) const;

    [[nodiscard]] Transaction getSmallestTransaction(int64_t userId) const;

    [[nodiscard]] Transaction getSmallestTransactionByCategory(int64_t userId, const std::string &category) const;

    [[nodiscard]] std::unordered_map<std::string, double> getMonthStatistics(int64_t userId);

    [[nodiscard]] std::unordered_map<std::string, double> getWeekStatistics(int64_t userId);

    [[nodiscard]] double getStatisticsBySum(int64_t userId,
                                              const std::chrono::system_clock::duration &duration);

    [[nodiscard]] double getMonthStatisticsBySum(int64_t userId);

    [[nodiscard]] double getWeekStatisticsBySum(int64_t userId);

    [[nodiscard]] std::vector<std::string> getUserCategory(int64_t userId) const;
};
#endif //FINANCEMANAGER_H
