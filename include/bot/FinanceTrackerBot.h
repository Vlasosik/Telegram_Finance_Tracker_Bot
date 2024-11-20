#ifndef TELEGRAMBOT_H
#define TELEGRAMBOT_H
#include <tgbot/Bot.h>
#include <pch.h>
#include "finance_manager/FinanceManager.h"

class FinanceTrackerBot {
    TgBot::Bot bot;
    FinanceManager finance_manager;
    std::unordered_multimap<int64_t, std::string> chosenCategories;

public:
    explicit FinanceTrackerBot(const std::string &token);

    [[noreturn]] void run() const;

    void setUp();

    void addCategory(int64_t userId, const std::string &category);

    void sendMainBar(int64_t userId) const;

    void sendCategoryBar(int64_t userId) const;
};
#endif //TELEGRAMBOT_H
