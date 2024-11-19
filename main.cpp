#include <cstdio>
#include <tgbot/tgbot.h>
#include "pch.h"
#include "bot/FinanceTrackerBot.h"
#include "finance_manager/FinanceManager.h"
#include "transactions/Transaction.h"

int main() {
    const char* token = std::getenv("TOKEN_BOT");
    if (!token) {
        throw std::runtime_error("TOKEN_BOT is not set in the environment variables");
    }
    const FinanceTrackerBot telegram_bot(token);
    telegram_bot.run();
}

