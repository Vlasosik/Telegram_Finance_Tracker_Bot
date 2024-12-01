#ifndef TELEGRAMBOT_H
#define TELEGRAMBOT_H
#include <tgbot/Bot.h>

#include "callback_command/CallbackCommand.h"
#include "message_command/MessageCommand.h"
#include "migration/MigrationSQL.h"
#include "text_message/TextMessage.h"

class FinanceTrackerBot {
    TgBot::Bot bot;
    MigrationSQL migrationSQL;
    std::unordered_map<std::string, std::shared_ptr<MessageCommand> > messageCommands;
    std::unordered_map<std::string, std::shared_ptr<CallbackCommand> > callbackCommands;
    std::vector<std::unique_ptr<TextMessage> > textMessages;

public:
    explicit FinanceTrackerBot(const std::string &token);

    void registerCommand();

    void registerCallbacks();

    void registerTextMessages();

    void handleCommandMessage(const std::string &command, const TgBot::Message::Ptr &message);

    void handleCallbackQuery(const std::string &command, const TgBot::CallbackQuery::Ptr &query);

    void handleTextMessages(const TgBot::Message::Ptr &message);

    [[noreturn]] void Run();
};
#endif //TELEGRAMBOT_H
