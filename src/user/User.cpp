#include "user/User.h"

#include <tgbot/Bot.h>

User::User(const int64_t id) : id(id), selectedCategory(" ") {
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
    return !selectedCategory.empty();
}