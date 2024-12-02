#include "finance_manager/FinanceManager.h"

#include <numeric>

FinanceManager::FinanceManager(std::vector<Transaction> financeManager)
    : finance_manager(std::move(financeManager)) {
}
