#include "bot/FinanceTrackerBot.h"

#include <tgbot/net/TgLongPoll.h>

#include "bot/callback_command/CallbackAddTransaction.h"
#include "bot/callback_command/CallbackAvailableСategories.h"
#include "bot/callback_command/CallbackBack.h"
#include "bot/callback_command/CallbackCategoryManagement.h"
#include "bot/callback_command/CallbackGetListTransaction.h"
#include "bot/callback_command/CallbackHelp.h"
#include "bot/callback_command/CallbackRemoveTransaction.h"
#include "bot/callback_command/CallbackSelectedCategories.h"
#include "bot/message_command/InfoMessageCommand.h"
#include "bot/message_command/StartMessageCommand.h"
#include "bot/text_message/EnteringAmountHandler.h"
#include "bot/text_message/EnteringRemoveHandler.h"
#include "bot/ui_manager/UIManager.h"

FinanceTrackerBot::FinanceTrackerBot(const std::string &token) : bot(token) {
    registerCommand();
    registerCallbacks();
    registerTextMessages();
}

void FinanceTrackerBot::registerCommand() {
    messageCommands["/start"] = std::make_shared<StartMessageCommand>();
    messageCommands["/info"] = std::make_shared<InfoMessageCommand>();
}

void FinanceTrackerBot::registerCallbacks() {
    callbackCommands["Доступні категорії"] = std::make_shared<CallbackAvailableCategories>();
    callbackCommands["Управління категоріями"] = std::make_shared<CallbackCategoryManagement>();
    callbackCommands["Допомога"] = std::make_shared<CallbackHelp>();

    const std::vector<std::string> categories = {
        "Їжа", "Одяг та взуття", "Сімʼя та діти", "Накопичення",
        "Житло", "Транспорт", "Особисті витрати", "Освіта та розвиток"
    };
    for (const auto &category: categories) {
        callbackCommands[category] = std::make_shared<CallbackSelectedCategories>();
    }
    callbackCommands["Назад"] = std::make_shared<CallbackBack>();
    callbackCommands["Додати транзакцію"] = std::make_shared<CallbackAddTransaction>();
    callbackCommands["Список транзакцій"] = std::make_shared<CallbackGetListTransaction>();
    callbackCommands["Видалити транзакцію"] = std::make_shared<CallbackRemoveTransaction>();
}

void FinanceTrackerBot::registerTextMessages() {
    textMessages.emplace_back(std::make_unique<EnteringAmountHandler>());
    textMessages.emplace_back(std::make_unique<EnteringRemoveHandler>());
}

void FinanceTrackerBot::handleCommandMessage(const std::string &command, const TgBot::Message::Ptr &message) {
    if (messageCommands.contains(command)) {
        messageCommands[command]->ExecuteMessage(bot, message);
    } else {
        bot.getApi().sendMessage(message->chat->id, "Невідома команда: " + command);
    }
}

void FinanceTrackerBot::handleCallbackQuery(const std::string &command, const TgBot::CallbackQuery::Ptr &query) {
    if (callbackCommands.contains(command)) {
        callbackCommands[command]->ExecuteCallback(bot, query);
    } else {
        bot.getApi().sendMessage(query->message->chat->id, "Невідома команда: " + command);
    }
}

void FinanceTrackerBot::handleTextMessages(const TgBot::Message::Ptr &message) {
    const int64_t userId = message->chat.get()->id;
    for (const auto &handler: textMessages) {
        if (handler->canHandle(userId, message)) {
            handler->handleMessage(bot, message);
            return;
        }
    }
    bot.getApi().sendMessage(message->chat->id, "Виберіть операцію, яку ви хочете зробити з вашим повідомленням.");
}


void FinanceTrackerBot::Run() {
    bot.getEvents().onCommand({"start", "info"},
                              [this](const TgBot::Message::Ptr &message) {
                                  handleCommandMessage(message->text, message);
                              });
    bot.getEvents().onCallbackQuery([this](const TgBot::CallbackQuery::Ptr &query) {
        handleCallbackQuery(query->data, query);
    });

    bot.getEvents().onAnyMessage([this](const TgBot::Message::Ptr &message) {
        if (!message->text.empty() && message->text[0] != '/') {
            handleTextMessages(message);
        }
    });
    TgBot::TgLongPoll long_poll(bot);
    std::cout << bot.getApi().getMyName()->name << ": started.\n";
    while (true) {
        long_poll.start();
    }
}
