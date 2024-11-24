#include "user/UserManager.h"

UserManager &UserManager::getInstance() {
    static UserManager instance;
    return instance;
}

std::shared_ptr<User> &UserManager::getUser(int64_t userId) {
    if (userManager.contains(userId)) {
        return userManager[userId];
    }
    return userManager[userId] = std::make_shared<User>(userId);
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
    userStateMap[userId] = newState;
}

UserStateType UserManager::getState(const int64_t userId) const {
    if (userStateMap.contains(userId)) {
        return userStateMap.at(userId);
    }
    return UserStateType::IDLE;
}

void UserManager::addTransactionByUser(const int64_t userId, const std::string &category, const double amount) {
    financeManager.addTransaction(userId, category, amount);
}
