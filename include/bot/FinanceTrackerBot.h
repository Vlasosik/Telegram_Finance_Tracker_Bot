#ifndef TELEGRAMBOT_H
#define TELEGRAMBOT_H
#include <tgbot/Bot.h>

#include "callback_command/CallbackCommand.h"
#include "finance_manager/FinanceManager.h"
#include "message_command/MessageCommand.h"

class FinanceTrackerBot {
    TgBot::Bot bot;
    FinanceManager finance_manager;
    std::unordered_map<std::string, std::shared_ptr<MessageCommand> > messageCommands;
    std::unordered_map<std::string, std::shared_ptr<CallbackCommand> > callbackCommands;

public:
    explicit FinanceTrackerBot(const std::string &token);

    void registerCommand();

    void registerCallbacks();

    void handleCommandMessage(const std::string &command, const TgBot::Message::Ptr &message);

    void handleCallbackQuery(const std::string &command, const TgBot::CallbackQuery::Ptr &query);

    void handleTextMessage(TgBot::Bot &bot, const TgBot::Message::Ptr &message);

    [[noreturn]] void Run();
};
#endif //TELEGRAMBOT_H
