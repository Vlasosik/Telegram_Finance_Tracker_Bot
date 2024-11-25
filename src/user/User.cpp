#include "user/User.h"

#include <tgbot/Bot.h>

User::User(const int64_t id) : id(id), selectedCategory("None"), userState(UserStateType::IDLE) {
}

int64_t User::getUserId() const {
    return id;
}

void User::setCategory(const std::string &category) {
    this->selectedCategory = category;
}

std::string User::getSelectedCategory() {
    return selectedCategory;
}

bool User::hasSelectedCategory() const {
    const std::vector<std::string> nameCategory{
        "Їжа", "Житло", "Одяг та взуття",
        "Транспорт", "Сімʼя та діти", "Особисті витрати",
        "Накопичення", "Освіта та розвиток"
    };
    return std::ranges::any_of(nameCategory, [this](const std::string &category) {
        return category == this->selectedCategory;
    });
}

UserStateType User::getUserState() const {
    return userState;
}

void User::setUserState(const UserStateType newState) {
    this->userState = newState;
}
