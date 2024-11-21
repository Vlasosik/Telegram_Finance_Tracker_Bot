#ifndef TELEGRAMBOT_H
#define TELEGRAMBOT_H
#include <tgbot/Bot.h>
#include <pch.h>

#include "command/Command.h"
#include "finance_manager/FinanceManager.h"

class FinanceTrackerBot {
    TgBot::Bot bot;
    FinanceManager finance_manager;
    std::unordered_map<std::string, std::shared_ptr<Command> > commands;
    std::unordered_map<std::string, std::function<void(const TgBot::Message::Ptr &)> > callbackMessages;
    std::unordered_map<std::string, std::function<void(const TgBot::CallbackQuery::Ptr &)> > callbackQueries;
    std::unordered_map<int64_t, std::unordered_set<std::string> > userSelectedCategories;

public:
    explicit FinanceTrackerBot(const std::string &token);

    void registerCommand();

    void registerCallbacks();

    void handleCommandMessage(const std::string &command, const TgBot::Message::Ptr &message);

    void handleCallbackMessages(const std::string &command, const TgBot::Message::Ptr &message);

    void handleCallbackQuery(const std::string &command, const TgBot::CallbackQuery::Ptr &query);

    [[noreturn]] void Run();
};
#endif //TELEGRAMBOT_H
