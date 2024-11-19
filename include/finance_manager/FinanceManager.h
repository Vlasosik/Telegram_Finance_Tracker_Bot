#ifndef FINANCEMANAGER_H
#define FINANCEMANAGER_H
#include "pch.h"
#include "transactions/Transaction.h"

class FinanceManager {
    std::vector<Transaction> finance_manager;

public:
    explicit FinanceManager() = default;

    explicit FinanceManager(std::vector<Transaction> finance_manager);

    void addTransaction(Transaction transaction);

    [[nodiscard]] std::vector<Transaction> getTransaction(int64_t id) const;

    [[nodiscard]] std::unordered_map<std::string, double> getSumAllTransactionsByCategory(int64_t id) const;

    [[nodiscard]] std::unordered_map<std::string, std::vector<double> > getAllTransactionsByCategory(int64_t id) const;

};
#endif //FINANCEMANAGER_H
// TODO: WRITE CONNECTION TO POSTGRESQL
