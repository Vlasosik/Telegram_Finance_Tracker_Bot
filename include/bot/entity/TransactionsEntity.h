#ifndef TRANSACTIONSENTITY_H
#define TRANSACTIONSENTITY_H
#include <sqlpp11/char_sequence.h>
#include <sqlpp11/chrono.h>
#include <sqlpp11/table.h>
#include <sqlpp11/type_traits.h>
#include <sqlpp11/data_types/integral/data_type.h>
#include <sqlpp11/data_types/text/data_type.h>

namespace mydb::Transactions {
    struct Id {
        struct _alias_t {
            static constexpr char _literal[] = "id";
            using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;

            template<typename T>
            struct _member_t {
                T id;
                T &operator()() { return id; }
                T &operator()() const { return id; }
            };
        };

        using _traits = sqlpp::make_traits<sqlpp::bigint, sqlpp::tag::must_not_insert>;
    };

    struct UserId {
        struct _alias_t {
            static constexpr char _literal[] = "user_id";
            using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;

            template<typename T>
            struct _member_t {
                T userId;
                T &operator()() { return userId; }
                T &operator()() const { return userId; }
            };
        };

        using _traits = sqlpp::make_traits<sqlpp::bigint>;
    };

    struct Category {
        struct _alias_t {
            static constexpr char _literal[] = "category";
            using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;

            template<typename T>
            struct _member_t {
                T category;
                T &operator()() { return category; }
                T &operator()() const { return category; }
            };
        };

        using _traits = sqlpp::make_traits<sqlpp::varchar>;
    };

    struct Amount {
        struct _alias_t {
            static constexpr char _literal[] = "amount";
            using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;

            template<typename T>
            struct _member_t {
                T amount;
                T &operator()() { return amount; }
                T &operator()() const { return amount; }
            };
        };

        using _traits = sqlpp::make_traits<sqlpp::floating_point>;
    };

    struct Date {
        struct _alias_t {
            static constexpr char _literal[] = "date";
            using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;

            template<typename T>
            struct _member_t {
                T date;
                T &operator()() { return date; }
                T &operator()() const { return date; }
            };
        };

        using _traits = sqlpp::make_traits<sqlpp::time_point>;
    };

    struct TabTransaction : sqlpp::table_t<TabTransaction, Id, UserId, Category, Amount, Date> {
        struct _alias_t {
            static constexpr char _literal[] = "transactions";
            using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;

            template<typename T>
            struct _member_t {
                T tabTransactions;
                T &operator()() { return tabTransactions; }
                const T &operator()() const { return tabTransactions; }
            };
        };
    };
}

struct TabTransaction {
    int64_t id;
    int64_t userId;
    std::string category;
    double amount;
    sqlpp::chrono::microsecond_point date;

    TabTransaction() : id(0), userId(0), amount(0.0) {
    }

    explicit TabTransaction(const int64_t id, const int64_t userId, std::string category, const double amount,
                            const sqlpp::chrono::microsecond_point date)
        : id(id), userId(userId), category(std::move(category)), amount(amount), date(date) {
    }
};
#endif //TRANSACTIONSENTITY_H
