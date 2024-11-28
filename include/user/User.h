#ifndef USER_H
#define USER_H

enum class UserStateType {
    IDLE = 1,
    ENTERING_AMOUNT,
    SELECTING_CATEGORY,
    REMOVED_TRANSACTION,
    UPDATED_TRANSACTION,
    SELECTING_REPORT
};

class User {
    int64_t id;
    std::string selectedCategory;
    UserStateType userState;

public:
    explicit User(int64_t id);

    [[nodiscard]] int64_t getUserId() const;

    void setCategory(const std::string &category);

    std::string getSelectedCategory();

    [[nodiscard]] bool hasSelectedCategory() const;

    [[nodiscard]] UserStateType getUserState() const;

    void setUserState(UserStateType newState);
};
#endif //USER_H
