#include "user/UserManager.h"

UserManager &UserManager::getInstance() {
    static UserManager instance;
    return instance;
}

std::shared_ptr<User> UserManager::getUser(int64_t userId) {
    if (!userManager.contains(userId)) {
        std::cout << "Creating new user with ID: " << userId << std::endl;
        userManager[userId] = std::make_shared<User>(userId);
    } else {
        std::cout << "User with ID " << userId << " already exists. State: "
                << static_cast<int>(userManager[userId]->getUserState()) << std::endl;
    }
    return userManager[userId];
}

void UserManager::addCategory(const int64_t userId, const std::string &category) {
    userManager[userId]->setCategory(category);
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
        std::cout << "Setting state for user " << userId << " to " << static_cast<int>(newState) << std::endl;
        userManager[userId]->setUserState(newState);
    } else {
        std::cout << "User " << userId << " not found." << std::endl;
    }
}

UserStateType UserManager::getState(const int64_t userId) const {
    return userManager.at(userId)->getUserState();
}

void UserManager::addTransactionByUser(const int64_t userId, const std::string &category, const double amount) {
    financeManager.addTransaction(userId, category, amount);
}

std::vector<Transaction> UserManager::getListTransaction(const int64_t userId) const {
    return financeManager.getTransaction(userId);
}
