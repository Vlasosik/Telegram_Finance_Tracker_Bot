#ifndef FINANCEMANAGER_H
#define FINANCEMANAGER_H
#include "pch.h"
#include "transactions/Transaction.h"

class FinanceManager {
    std::vector<Transaction> finance_manager;

public:
    explicit FinanceManager() = default;

    explicit FinanceManager(std::vector<Transaction> financeManager);
};
#endif //FINANCEMANAGER_H
