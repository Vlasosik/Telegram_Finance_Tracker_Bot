#include "migration/MigrationSQL.h"

MigrationSQL::MigrationSQL(const std::string &user, const std::string &password, const std::string &dbname, int port,
                           const std::string &host) {
    sqlpp::postgresql::connection_config config;
    config.user = user;
    config.password = password;
    config.dbname = dbname;
    config.port = port;
    config.host = host;
    db = sqlpp::postgresql::connection(config);
}

// constructor for used migrations file in environment variables
MigrationSQL::MigrationSQL() {
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

void MigrationSQL::executeMigrations(const std::string &migrationFolder) {
    try {
        std::filesystem::path exe_path = std::filesystem::current_path();
        std::filesystem::path migration_path = exe_path / migrationFolder;
        if (!exists(migration_path) || !is_directory(migration_path)) {
            std::cerr << "Папка міграцій не знайдена: " << migration_path << std::endl;
            return;
        }
        for (const auto &entry: std::filesystem::directory_iterator(migration_path)) {
            if (entry.is_regular_file() && entry.path().extension() == ".sql") {
                if (std::ifstream migration_file(entry.path()); migration_file) {
                    std::string migration_sql((std::istreambuf_iterator<char>(migration_file)),
                                              std::istreambuf_iterator<char>());
                    db.execute(migration_sql);
                    std::cout << "Міграція виконана успішно: " << entry.path() << std::endl;
                } else {
                    std::cerr << "Не вдалося відкрити файл: " << entry.path() << std::endl;
                }
            }
        }
    } catch (const std::exception &e) {
        std::cerr << "Помилка при виконанні міграцій: " << e.what() << std::endl;
    }
}
