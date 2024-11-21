#ifndef TELEGRAMBOT_H
#define TELEGRAMBOT_H
#include <tgbot/Bot.h>
#include <pch.h>
#include "finance_manager/FinanceManager.h"

class FinanceTrackerBot {
    TgBot::Bot bot;
    FinanceManager finance_manager;

public:
    explicit FinanceTrackerBot(const std::string &token);

    [[noreturn]] void run() const;
};
#endif //TELEGRAMBOT_H
