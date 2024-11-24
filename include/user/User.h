#ifndef USER_H
#define USER_H

class User {
    int64_t id;
    std::string selectedCategory;

public:
    explicit User(int64_t id);

    [[nodiscard]] int64_t getUserId() const;

    void setCategory(const std::string &category);

    std::string getSelectedCategory();

    [[nodiscard]] bool hasSelectedCategory() const;

};
#endif //USER_H
