#include "finance_manager/FinanceManager.h"

#include <numeric>

bool FinanceManager::isMonthPassed(int64_t userId) {
    const auto it = std::ranges::find_if(finance_manager,
                                         [&userId](const Transaction &other) {
                                             return userId == other.getUserId();
                                         });
    if (it == finance_manager.end()) {
        throw std::invalid_argument("No transactions found for the given user ID");
    }
    const auto now = std::chrono::system_clock::now();
    const auto firstTransaction = *std::ranges::min_element(finance_manager,
                                                            [&userId](const Transaction &a, const Transaction &b) {
                                                                return a.getUserId() == userId && a.getDate() < b.
                                                                       getDate();
                                                            });
    const auto duration = std::chrono::duration_cast<std::chrono::days>(now - firstTransaction.getDate());
    return duration.count() >= 31;
}

bool FinanceManager::isWeekPassed(int64_t userId) {
    const auto it = std::ranges::find_if(finance_manager,
                                         [&userId](const Transaction &other) {
                                             return userId == other.getUserId();
                                         });
    if (it == finance_manager.end()) {
        throw std::invalid_argument("No transactions found for the given user ID");
    }
    const auto now = std::chrono::system_clock::now();
    const auto firstTransaction = *std::ranges::min_element(finance_manager,
                                                            [&userId](const Transaction &a, const Transaction &b) {
                                                                return a.getUserId() == userId && a.getDate() < b.
                                                                       getDate();
                                                            });
    const auto duration = std::chrono::duration_cast<std::chrono::days>(now - firstTransaction.getDate());
    return duration.count() >= 7;
}

FinanceManager::FinanceManager(std::vector<Transaction> finance_manager)
    : finance_manager(std::move(finance_manager)) {
}

void FinanceManager::addTransaction(int64_t userId, const std::string &category, double amount) {
    auto now = std::chrono::system_clock::now();
    finance_manager.emplace_back(userId, category, amount, now);
}

void FinanceManager::removeTransaction(const int64_t userId, const Transaction &transaction) {
    if (transaction.getUserId() != userId) {
        throw std::invalid_argument("Transaction does not belong to the user with the given ID");
    }
    if (const auto it = std::ranges::find(finance_manager, transaction);
        it != finance_manager.end()) {
        finance_manager.erase(it);
    } else {
        throw std::invalid_argument("Transaction not found in the user's list");
    }
}

void FinanceManager::updateTransactionByAmount(const int64_t userId, const std::string &category,
                                               const double newAmount) {
    for (auto &transaction: finance_manager) {
        if (transaction.getUserId() == userId && transaction.getCategory() == category) {
            transaction.setAmount(newAmount);
            return;
        }
    }
    throw std::invalid_argument("No matching transaction found for the given user ID and category");
}

void FinanceManager::updateTransactionByDate(const int64_t userId, const std::string &category,
                                             const time_point newDate) {
    for (auto &transaction: finance_manager) {
        if (transaction.getUserId() == userId && transaction.getCategory() == category) {
            transaction.setTimePoint(newDate);
            return;
        }
    }
    throw std::invalid_argument("No matching transaction found for the given user ID and category");
}

std::vector<Transaction> FinanceManager::getTransaction(const int64_t userId) const {
    std::vector<Transaction> transactions;
    transactions.reserve(finance_manager.size());
    for (auto &transaction: finance_manager) {
        if (transaction.getUserId() == userId) {
            transactions.push_back(transaction);
        }
    }
    return transactions;
}

std::unordered_map<std::string, double> FinanceManager::getSumAllTransactionsByCategory(const int64_t userId) const {
    std::unordered_map<std::string, double> statistics;
    for (const auto &transaction: finance_manager) {
        if (transaction.getUserId() == userId) {
            statistics[transaction.getCategory()] += transaction.getAmount();
        }
    }
    return statistics;
}

std::unordered_map<std::string, std::vector<double> > FinanceManager::getAllTransactionsByCategory(
    const int64_t userId) const {
    std::unordered_map<std::string, std::vector<double> > statistics;
    for (const auto &transaction: finance_manager) {
        if (transaction.getUserId() == userId) {
            statistics[transaction.getCategory()].push_back(transaction.getAmount());
        }
    }
    return statistics;
}

double FinanceManager::getTotalAmount(const int64_t userId) const {
    double totalAmount = 0.0;
    bool hasTransactions = false;
    for (auto &transaction: finance_manager) {
        if (transaction.getUserId() == userId) {
            totalAmount += transaction.getAmount();
            hasTransactions = true;
        }
    }
    if (!hasTransactions) {
        throw std::invalid_argument("Transaction does not belong to the user with the given ID");
    }
    return totalAmount;
}

std::vector<Transaction> FinanceManager::getTransactionByDateRange(const int64_t userId, const time_point &startDate,
                                                                   const time_point &endDate) const {
    if (startDate > endDate) {
        throw std::invalid_argument("Start date cannot be after end date");
    }

    std::vector<Transaction> transactionsByDateRange;
    for (auto &transaction: finance_manager) {
        if (transaction.getUserId() == userId
            && transaction.getDate() >= startDate
            && transaction.getDate() <= endDate) {
            transactionsByDateRange.push_back(transaction);
        }
    }

    if (transactionsByDateRange.empty()) {
        throw std::invalid_argument("No transactions found for the given user ID in the specified date range");
    }
    return transactionsByDateRange;
}

std::vector<Transaction> FinanceManager::getTransactionByCategory(const int64_t userId,
                                                                  const std::string &category) const {
    std::vector<Transaction> transactionsByCategory;
    for (const auto &transaction: finance_manager) {
        if (transaction.getUserId() == userId && transaction.getCategory() == category) {
            transactionsByCategory.push_back(transaction);
        }
    }
    if (transactionsByCategory.empty()) {
        throw std::invalid_argument("No transactions found for the given user ID and category");
    }
    return transactionsByCategory;
}

Transaction FinanceManager::getLargestTransaction(const int64_t userId) const {
    bool found = false;
    Transaction largestTransaction;
    constexpr double largestAmount = std::numeric_limits<double>::lowest();

    for (const auto &transaction: finance_manager) {
        if (transaction.getUserId() == userId && largestAmount < transaction.getAmount()) {
            largestTransaction = transaction;
            found = true;
        }
    }
    if (!found) {
        throw std::invalid_argument("No transactions found for the given user ID");
    }
    return largestTransaction;
}

Transaction FinanceManager::getLargestTransactionByCategory(const int64_t userId, const std::string &category) const {
    bool found = false;
    Transaction largestTransaction;
    constexpr double largestAmount = std::numeric_limits<double>::lowest();

    for (const auto &transaction: finance_manager) {
        if (transaction.getUserId() == userId
            && largestAmount < transaction.getAmount()
            && transaction.getCategory() == category) {
            largestTransaction = transaction;
            found = true;
        }
    }
    if (!found) {
        throw std::invalid_argument("No transactions found for the given user ID and category");
    }
    return largestTransaction;
}

Transaction FinanceManager::getSmallestTransaction(const int64_t userId) const {
    bool found = false;
    Transaction smallestTransaction;
    constexpr double smallestAmount = std::numeric_limits<double>::max();

    for (const auto &transaction: finance_manager) {
        if (transaction.getUserId() == userId && smallestAmount > transaction.getAmount()) {
            smallestTransaction = transaction;
            found = true;
        }
    }
    if (!found) {
        throw std::invalid_argument("No transactions found for the given user ID");
    }
    return smallestTransaction;
}

Transaction FinanceManager::getSmallestTransactionByCategory(const int64_t userId, const std::string &category) const {
    bool found = false;
    Transaction smallestTransaction;
    constexpr double smallestAmount = std::numeric_limits<double>::max();

    for (const auto &transaction: finance_manager) {
        if (transaction.getUserId() == userId
            && smallestAmount > transaction.getAmount()
            && transaction.getCategory() == category) {
            smallestTransaction = transaction;
            found = true;
        }
    }
    if (!found) {
        throw std::invalid_argument("No transactions found for the given user ID and category");
    }
    return smallestTransaction;
}

std::unordered_map<std::string, double> FinanceManager::getMonthStatistics(const int64_t userId) {
    std::unordered_map<std::string, double> monthlyStatistics;
    if (!isMonthPassed(userId)) {
        throw std::invalid_argument("A month has not passed since the first transaction");
    }
    for (const auto &transaction: finance_manager) {
        if (transaction.getUserId() == userId) {
            monthlyStatistics[transaction.getCategory()] += transaction.getAmount();
        }
    }
    return monthlyStatistics;
}

std::unordered_map<std::string, double> FinanceManager::getWeekStatistics(const int64_t userId) {
    std::unordered_map<std::string, double> weekStatistics;
    if (!isWeekPassed(userId)) {
        throw std::invalid_argument("A week has not passed since the first transaction");
    }
    for (const auto &transaction: finance_manager) {
        if (transaction.getUserId() == userId) {
            weekStatistics[transaction.getCategory()] += transaction.getAmount();
        }
    }
    return weekStatistics;
}

double FinanceManager::getMonthStatisticsByCategorySum(const int64_t userId, const std::string &category) {
    double total = 0.0;
    if (!isMonthPassed(userId)) {
        throw std::invalid_argument("A month has not passed since the first transaction");
    }
    for (const auto &transaction: finance_manager) {
        if (transaction.getUserId() == userId && transaction.getCategory() == category) {
            total += transaction.getAmount();
        }
    }
    return total;
}

double FinanceManager::getWeekStatisticsByCategorySum(const int64_t userId, const std::string &category) {
    double total = 0.0;
    if (!isWeekPassed(userId)) {
        throw std::invalid_argument("A week has not passed since the first transaction");
    }
    for (const auto &transaction: finance_manager) {
        if (transaction.getUserId() == userId && transaction.getCategory() == category) {
            total += transaction.getAmount();
        }
    }
    return total;
}

std::vector<std::string> FinanceManager::getUserCategory(const int64_t userId) const {
    std::vector<std::string> usersCategory;
    for (const auto &transaction: finance_manager) {
        if (transaction.getUserId() == userId) {
            if (std::ranges::find(usersCategory, transaction.getCategory()) == usersCategory.end()) {
                usersCategory.push_back(transaction.getCategory());
            }
        }
    }
    return usersCategory;
}
