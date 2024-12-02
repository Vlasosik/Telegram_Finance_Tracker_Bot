#include "service/UserService.h"

#include <sqlpp11/insert.h>
#include <sqlpp11/remove.h>
#include <sqlpp11/select.h>
#include <sqlpp11/update.h>

#include "bot/entity/UsersEntity.h"

UserService::UserService() {
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

void UserService::createUser(const int64_t id) {
    auto users = mydb::Users::TabUsers{};
    const auto statement = insert_into(users).set(users.id = id);
    try {
        db(statement);
        std::cout << "Користувач успішно створений!" << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Помилка при виконанні запиту: " << e.what() << std::endl;
    }
}

std::optional<int64_t> UserService::getUserId(const int64_t id) {
    if (!isUserExist(id)) {
        std::cerr << "Користувач з ID " << id << " не існує!" << std::endl;
        return std::nullopt;
    }
    const auto users = mydb::Users::TabUsers{};
    auto statement = select(users.id).from(users).where(users.id == id);

    auto result = db(statement);
    if (result.empty()) {
        return std::nullopt;
    }

    auto userId = result.front().id;
    return std::optional<int64_t>{userId};
}

void UserService::updateUser(const int64_t id) {
    if (!isUserExist(id)) {
        std::cerr << "Користувач з ID " << id << " не існує!" << std::endl;
        return;
    }
    const auto users = mydb::Users::TabUsers{};
    auto statement = update(users).set(users.id = id).where(users.id == id);
    try {
        db(statement);
        std::cout << "Користувач успішно оновлений!" << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Помилка при виконанні запиту: " << e.what() << std::endl;
    }
}

void UserService::deleteUser(const int64_t id) {
    if (!isUserExist(id)) {
        std::cerr << "Користувач з ID " << id << " не існує!" << std::endl;
        return;
    }
    const auto users = mydb::Users::TabUsers{};
    auto statement = remove_from(users).where(users.id == id);
    try {
        db(statement);
        std::cout << "Користувач за Id " << id << " успішно видалений!" << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Помилка при виконанні запиту: " << e.what() << std::endl;
    }
}

bool UserService::isUserExist(const int64_t id) {
    const auto users = mydb::Users::TabUsers{};
    auto statement = select(users.id).from(users).where(users.id == id);
    auto result = db(statement);
    return !result.empty();
}
