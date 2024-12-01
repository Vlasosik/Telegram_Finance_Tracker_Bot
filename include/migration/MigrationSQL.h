#ifndef MIGRATIONSQL_H
#define MIGRATIONSQL_H
#include <sqlpp11/postgresql/postgresql.h>
#include <__filesystem/directory_iterator.h>
#include <fstream>
#include <string>
class MigrationSQL {
    std::string migrationPath;
    sqlpp::postgresql::connection db;

public:
    MigrationSQL();
    MigrationSQL(const std::string &user, const std::string &password, const std::string &dbname,
                 int port, const std::string &host);

    void executeMigrations(const std::string &migrationFolder);
};
#endif //MIGRATIONSQL_H
