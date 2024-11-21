#ifndef UIMANAGER_H
#define UIMANAGER_H
#include <tgbot/Bot.h>
#include <pch.h>

class UIManager {
public:
    static void sendMainBar(const TgBot::Bot &bot, int64_t userId);

    static void sendCategoryBar(const TgBot::Bot &bot, int64_t userId);

    static void updateCategoryBar(const TgBot::Bot &bot, int64_t userId,
                                  const std::unordered_set<std::string> &selectedCategories);
};
#endif //UIMANAGER_H
