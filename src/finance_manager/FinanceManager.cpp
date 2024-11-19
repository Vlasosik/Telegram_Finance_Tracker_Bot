#include "finance_manager/FinanceManager.h"

#include <numeric>

FinanceManager::FinanceManager(std::vector<Transaction> finance_manager)
    : finance_manager(std::move(finance_manager)) {
}

void FinanceManager::addTransaction(Transaction transaction) {
    finance_manager.push_back(std::move(transaction));
}

std::vector<Transaction> FinanceManager::getTransaction(const int64_t id) const {
    std::vector<Transaction> transactions;
    transactions.reserve(finance_manager.size());
    for (auto &transaction: finance_manager) {
        if (transaction.getUserId() == id) {
            transactions.push_back(transaction);
        }
    }
    return transactions;
}

std::unordered_map<std::string, double> FinanceManager::getSumAllTransactionsByCategory(const int64_t id) const {
    std::unordered_map<std::string, double> statistics;
    for (const auto &transaction: finance_manager) {
        if (transaction.getUserId() == id) {
            statistics[transaction.getCategory()] += transaction.getAmount();
        }
    }
    return statistics;
}

std::unordered_map<std::string, std::vector<double> > FinanceManager::getAllTransactionsByCategory(
    const int64_t id) const {
    std::unordered_map<std::string, std::vector<double> > statistics;
    for (const auto &transaction: finance_manager) {
        if (transaction.getUserId() == id) {
            statistics[transaction.getCategory()].push_back(transaction.getAmount());
        }
    }
    return statistics;
}
