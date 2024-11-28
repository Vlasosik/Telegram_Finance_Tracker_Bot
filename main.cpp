#include <tgbot/tgbot.h>
#include "bot/FinanceTrackerBot.h"

int main() {
    const char* token = std::getenv("TOKEN_BOT");
    if (!token) {
        throw std::runtime_error("TOKEN_BOT is not set in the environment variables");
    }
    FinanceTrackerBot telegram_bot(token);
    telegram_bot.Run();
}

