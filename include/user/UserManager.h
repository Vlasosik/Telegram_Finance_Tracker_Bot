#ifndef USERMANAGER_H
#define USERMANAGER_H
#include "User.h"
#include "finance_manager/FinanceManager.h"
enum class UserStateType {
    ENTERING_AMOUNT,
    IDLE,
    SELECTING_CATEGORY
};

class UserManager {
    FinanceManager financeManager;

    UserStateType userState {};

    std::unordered_map<int64_t, std::shared_ptr<User> > userManager;

    std::map<int64_t, UserStateType> userStateMap;

public:
    static UserManager& getInstance();

    std::shared_ptr<User> &getUser(int64_t userId);

    void addCategory(int64_t userId, const std::string &category);

    std::string getUserSelectedCategory(int64_t userId);

    bool hasUserSelectedCategory(int64_t userId);

    void setState(int64_t userId, UserStateType newState);

    [[nodiscard]] UserStateType getState(int64_t userId) const;

    void addTransactionByUser(int64_t userId, const std::string &category, double amount);
};
#endif //USERMANAGER_H
