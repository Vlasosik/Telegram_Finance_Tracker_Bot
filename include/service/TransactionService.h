#ifndef TRANSACTIONSERVICE_H
#define TRANSACTIONSERVICE_H
#include <sqlpp11/postgresql/connection.h>

#include "transactions/Transaction.h"

typedef std::chrono::system_clock::time_point time_point;

class TransactionService {
    sqlpp::postgresql::connection db;

public:
    TransactionService();
    void createTransaction(int64_t userId, const std::string &category, double amount, time_point date);

    std::optional<int64_t> getTransactionId(int64_t id);

    void updateTransaction(int64_t userId, const std::string &category, double amount, time_point date);

    void deleteTransaction(int64_t userId);

    [[nodiscard]] std::vector<Transaction> getListTransactionByUserId(int64_t userId);

    std::vector<Transaction> getListTransactionForWeek(int64_t userId);

    double getSumTransactionForWeek(int64_t userId);

    std::vector<Transaction> getListTransactionForMonth(int64_t userId);

    double getSumTransactionForMonth(int64_t userId);

    bool isTransactionExist(int64_t id);
};
#endif //TRANSACTIONSERVICE_H
