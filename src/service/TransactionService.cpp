#include "service/TransactionService.h"

#include <sqlpp11/insert.h>
#include <sqlpp11/remove.h>
#include <sqlpp11/select.h>
#include <sqlpp11/postgresql/update.h>

#include "bot/entity/TransactionsEntity.h"

TransactionService::TransactionService() {
    sqlpp::postgresql::connection_config config;

    const char *db_user = std::getenv("DB_USER");
    const char *db_password = std::getenv("DB_PASSWORD");
    const char *db_name = std::getenv("DB_NAME");
    const char *db_port = std::getenv("DB_PORT");
    const char *db_host = std::getenv("DB_HOST");

    if (db_user) config.user = db_user;
    if (db_password) config.password = db_password;
    if (db_name) config.dbname = db_name;
    if (db_port) config.port = std::stoi(db_port);
    if (db_host) config.host = db_host;

    db = sqlpp::postgresql::connection(config);
}

void TransactionService::createTransaction(const int64_t userId, const std::string &category,
                                           const double amount,
                                           const time_point date) {
    auto transactions = mydb::Transactions::TabTransaction{};
    const auto statement = insert_into(transactions).set(
        transactions.userId = userId,
        transactions.category = category,
        transactions.amount = amount,
        transactions.date = date
    );
    try {
        db(statement);
        std::cout << "Транзакція успішно створений!" << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Помилка при виконанні запиту: " << e.what() << std::endl;
    }
}

std::optional<int64_t> TransactionService::getTransactionId(int64_t id) {
    if (!isTransactionExist(id)) {
        std::cerr << "Транзакція з ID " << id << " не існує!" << std::endl;
        return std::nullopt;
    }
    auto transactions = mydb::Transactions::TabTransaction{};
    auto statement = select(transactions.id).from(transactions).where(transactions.id == id);

    auto result = db(statement);
    if (result.empty()) {
        return std::nullopt;
    }

    auto userId = result.front().id;
    return std::optional<int64_t>{userId};
}

void TransactionService::updateTransaction(const int64_t userId, const std::string &category, const double amount,
                                           const time_point date) {
    auto transactions = mydb::Transactions::TabTransaction{};
    auto statement = update(transactions).set(
        transactions.userId = userId,
        transactions.category = category,
        transactions.amount = amount,
        transactions.date = date).where(transactions.userId == userId);
    try {
        db(statement);
        std::cout << "Транзакція успішно оновлена!" << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Помилка при виконанні запиту: " << e.what() << std::endl;
    }
}

void TransactionService::deleteTransaction(const int64_t userId) {
    auto transactions = mydb::Transactions::TabTransaction{};
    auto checkStatement = select(transactions.userId)
            .from(transactions)
            .where(transactions.userId == userId);
    try {
        auto result = db(checkStatement);
        if (result.empty()) {
            throw std::invalid_argument("Транзакцій для користувача не знайдено.");
        }
        auto deleteStatement = remove_from(transactions).where(transactions.userId == userId);
        db(deleteStatement);
        std::cout << "Транзакція користувача з ID " << userId << " успішно видалена!" << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Помилка при виконанні запиту: " << e.what() << std::endl;
    }
}


std::vector<Transaction> TransactionService::getListTransactionByUserId(const int64_t userId) {
    auto transactions = mydb::Transactions::TabTransaction{};
    auto statement = select(
        transactions.userId,
        transactions.category,
        transactions.amount,
        transactions.date
    ).from(transactions).where(transactions.userId == userId);

    auto result = db(statement);

    std::vector<Transaction> transactionsList;
    for (const auto &row: result) {
        auto transactionDate = static_cast<std::chrono::system_clock::time_point>(row.date);
        transactionsList.emplace_back(
            row.userId,
            row.category,
            row.amount,
            transactionDate
        );
    }
    return transactionsList;
}

std::vector<Transaction> TransactionService::getListTransactionForWeek(int64_t userId) {
    std::vector<Transaction> weekTransactions;
    auto transactions = mydb::Transactions::TabTransaction{};
    const auto now = std::chrono::system_clock::now();
    const auto weekAgo = now - std::chrono::days(7);
    auto statement = select(transactions.userId,
                            transactions.category,
                            transactions.amount,
                            transactions.date
    ).from(transactions).where(transactions.userId == userId and transactions.date >= weekAgo);
    auto result = db(statement);
    for (const auto &row: result) {
        auto transactionDate = static_cast<std::chrono::system_clock::time_point>(row.date);
        weekTransactions.emplace_back(
            row.userId,
            row.category,
            row.amount,
            transactionDate
        );
    }
    return weekTransactions;
}

double TransactionService::getSumTransactionForWeek(int64_t userId) {
    auto transactions = mydb::Transactions::TabTransaction{};
    const auto now = std::chrono::system_clock::now();
    const auto weekAgo = now - std::chrono::days(7);
    auto statement = select(transactions.amount)
            .from(transactions)
            .where(transactions.userId == userId and transactions.date >= weekAgo);

    auto result = db(statement);
    double totalSum = 0.0;
    for (const auto &row: result) {
        totalSum += row.amount;
    }
    return totalSum;
}

std::vector<Transaction> TransactionService::getListTransactionForMonth(int64_t userId) {
    std::vector<Transaction> weekTransactions;
    auto transactions = mydb::Transactions::TabTransaction{};
    const auto now = std::chrono::system_clock::now();
    const auto monthAgo = now - std::chrono::days(31);
    auto statement = select(transactions.userId,
                            transactions.category,
                            transactions.amount,
                            transactions.date
    ).from(transactions).where(transactions.userId == userId and transactions.date >= monthAgo);
    auto result = db(statement);
    for (const auto &row: result) {
        auto transactionDate = static_cast<std::chrono::system_clock::time_point>(row.date);
        weekTransactions.emplace_back(
            row.userId,
            row.category,
            row.amount,
            transactionDate
        );
    }
    return weekTransactions;
}

double TransactionService::getSumTransactionForMonth(int64_t userId) {
    auto transactions = mydb::Transactions::TabTransaction{};
    const auto now = std::chrono::system_clock::now();
    const auto monthAgo = now - std::chrono::days(31);
    auto statement = select(transactions.amount)
            .from(transactions)
            .where(transactions.userId == userId and transactions.date >= monthAgo);
    auto result = db(statement);
    double totalSum = 0.0;
    for (const auto &row: result) {
        totalSum += row.amount;
    }
    return totalSum;
}

bool TransactionService::isTransactionExist(const int64_t id) {
    auto transactions = mydb::Transactions::TabTransaction{};
    auto statement = select(transactions.id).from(transactions).where(transactions.id == id);
    auto result = db(statement);
    return !result.empty();
}
