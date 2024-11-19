#ifndef TELEGRAMBOT_H
#define TELEGRAMBOT_H
#include <tgbot/Bot.h>
class FinanceTrackerBot {
    TgBot::Bot bot;

public:
    explicit FinanceTrackerBot(const std::string &token);

    [[noreturn]] void run() const;

    void setUp();

    void sendInlineKeyboard(int64_t id) const;


};
#endif //TELEGRAMBOT_H
