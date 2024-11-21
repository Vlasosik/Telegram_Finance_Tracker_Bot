#include "bot/FinanceTrackerBot.h"

#include <tgbot/net/TgLongPoll.h>

FinanceTrackerBot::FinanceTrackerBot(const std::string &token) : bot(token) {
}

[[noreturn]] void FinanceTrackerBot::run() const {
    TgBot::TgLongPoll long_poll(bot);
    std::cout << bot.getApi().getMyName()->name << ": started.\n";
    while (true) {
        long_poll.start();
    }
}