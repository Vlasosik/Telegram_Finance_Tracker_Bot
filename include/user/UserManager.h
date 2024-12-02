#ifndef USERMANAGER_H
#define USERMANAGER_H
#include "User.h"
#include "finance_manager/FinanceManager.h"
#include "service/TransactionService.h"
#include "service/UserService.h"

class UserManager {
    FinanceManager financeManager;
    UserService userService;
    TransactionService transactionService;

    std::unordered_map<int64_t, std::shared_ptr<User> > userManager;

    UserManager() = default;

public:
    UserManager(const UserManager &other) = delete;

    UserManager &operator=(const UserManager &other) = delete;

    static UserManager &getInstance();

    std::shared_ptr<User> getUser(int64_t userId);

    void addCategory(int64_t userId, const std::string &category);

    std::string getUserSelectedCategory(int64_t userId);

    bool hasUserSelectedCategory(int64_t userId);

    void setState(int64_t userId, UserStateType newState);

    [[nodiscard]] UserStateType getState(int64_t userId);

    void addTransactionByUser(int64_t userId, const std::string &category, double amount);

    [[nodiscard]] std::vector<Transaction> getListTransaction(int64_t userId);

    bool transactionExists(int64_t userId, const Transaction& transaction);

    void removeTransaction(int64_t userId, const Transaction &transaction);

    void updateTransaction(int64_t userId, const Transaction &transaction);

    [[nodiscard]] std::vector<Transaction> getListTransactionForWeek(int64_t userId);

    double getListTransactionForWeekBySum(int64_t userId);

    [[nodiscard]] std::vector<Transaction> getListTransactionForMonth(int64_t userId);

    double getListTransactionForMonthBySum(int64_t userId);
};
#endif //USERMANAGER_H
