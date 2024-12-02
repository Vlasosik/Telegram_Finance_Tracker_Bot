#ifndef USERSENTITY_H
#define USERSENTITY_H
#include <sqlpp11/char_sequence.h>
#include <sqlpp11/table.h>
#include <sqlpp11/type_traits.h>
#include <sqlpp11/data_types/integral/data_type.h>

namespace mydb::Users {
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

        using _traits = sqlpp::make_traits<sqlpp::bigint>;
    };

    struct TabUsers : sqlpp::table_t<TabUsers, Id> {
        using _value_type = sqlpp::no_value_t;

        struct _alias_t {
            static constexpr char _literal[] = "users";
            using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;

            template<typename T>
            struct _member_t {
                T tabUsers;
                T &operator()() { return tabUsers; }
                const T &operator()() const { return tabUsers; }
            };
        };
    };
}

struct UserData {
    std::int64_t id;

    UserData() : id(0) {
    }

    explicit UserData(const int64_t id) : id(id) {
    }
};

#endif //USERSENTITY_H
