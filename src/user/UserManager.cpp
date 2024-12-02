#include "user/UserManager.h"

UserManager &UserManager::getInstance() {
    static UserManager instance;
    return instance;
}

std::shared_ptr<User> UserManager::getUser(int64_t userId) {
    if (userManager.contains(userId)) {
        return userManager[userId];
    }
    if (const auto userIdFromDb = userService.getUserId(userId); userIdFromDb.has_value()) {
        userManager[userId] = std::make_shared<User>(userId);
        return userManager[userId];
    }
    userService.createUser(userId);
    userManager[userId] = std::make_shared<User>(userId);
    return userManager[userId];
}

void UserManager::addCategory(const int64_t userId, const std::string &category) const {
    userManager.at(userId)->setCategory(category);
}

std::string UserManager::getUserSelectedCategory(const int64_t userId) {
    return userManager[userId]->getSelectedCategory();
}

bool UserManager::hasUserSelectedCategory(const int64_t userId) {
    if (const auto it = userManager.find(userId); it != userManager.end()) {
        return it->second->hasSelectedCategory();
    }
    return false;
}

void UserManager::setState(const int64_t userId, const UserStateType newState) {
    if (userManager.contains(userId)) {
        userManager[userId]->setUserState(newState);
    } else {
        std::cout << "User " << userId << " not found." << std::endl;
    }
}

UserStateType UserManager::getState(const int64_t userId) {
    return userManager[userId]->getUserState();
}

void UserManager::addTransactionByUser(const int64_t userId, const std::string &category, const double amount) {
    transactionService.createTransaction(userId, category, amount, std::chrono::system_clock::now());
}

std::vector<Transaction> UserManager::getListTransaction(const int64_t userId) {
    return transactionService.getListTransactionByUserId(userId);
}

bool UserManager::transactionExists(const int64_t userId, const Transaction &transaction) {
    auto transactions = getListTransaction(userId);
    return std::ranges::any_of(transactions.begin(), transactions.end(), [&transaction](const Transaction &t) {
        return transaction == t;
    });
}

void UserManager::removeTransaction(const int64_t userId, const Transaction &transaction) {
    transactionService.deleteTransaction(userId);
}

void UserManager::updateTransaction(const int64_t userId, const Transaction &transaction) {
    transactionService.updateTransaction(userId, transaction.getCategory(), transaction.getAmount(),
                                         transaction.getDate());
}

[[nodiscard]] std::vector<Transaction> UserManager::getListTransactionForWeek(const int64_t userId) {
    return transactionService.getListTransactionForWeek(userId);
}

double UserManager::getListTransactionForWeekBySum(const int64_t userId) {
    return transactionService.getSumTransactionForWeek(userId);
}

[[nodiscard]] std::vector<Transaction> UserManager::getListTransactionForMonth(const int64_t userId) {
    return transactionService.getListTransactionForMonth(userId);
}

double UserManager::getListTransactionForMonthBySum(const int64_t userId) {
    return transactionService.getSumTransactionForMonth(userId);
}
