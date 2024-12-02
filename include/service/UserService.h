#ifndef USERSERVICE_H
#define USERSERVICE_H
#include <sqlpp11/postgresql/connection.h>

class UserService {
    sqlpp::postgresql::connection db;

public:
    UserService();
    void createUser(int64_t id);

    std::optional<int64_t> getUserId(int64_t id);

    void updateUser(int64_t id);

    void deleteUser(int64_t id);

    bool isUserExist(int64_t id);
};
#endif //USERSERVICE_H
