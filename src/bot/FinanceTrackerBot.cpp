#include "bot/FinanceTrackerBot.h"

#include <tgbot/net/TgLongPoll.h>

#include "bot/callback_command/CallbackAddTransaction.h"
#include "bot/callback_command/CallbackAvailableСategories.h"
#include "bot/callback_command/CallbackBack.h"
#include "bot/callback_command/CallbackCategoryManagement.h"
#include "bot/callback_command/CallbackHelp.h"
#include "bot/callback_command/CallbackSelectedCategories.h"
#include "bot/message_command/InfoMessageCommand.h"
#include "bot/message_command/StartMessageCommand.h"
#include "bot/ui_manager/UIManager.h"

FinanceTrackerBot::FinanceTrackerBot(const std::string &token) : bot(token) {
    registerCommand();
    registerCallbacks();
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

void FinanceTrackerBot::handleTextMessage(TgBot::Bot &bot, const TgBot::Message::Ptr &message) {
    const int64_t userId = message->chat->id;
    auto userManager = UserManager::getInstance();
    userManager.getUser(userId);
    if (userManager.getState(userId) == UserStateType::ENTERING_AMOUNT) {
        try {
            const auto amount = std::stod(message->text);
            userManager.addTransactionByUser(userId, userManager.getUserSelectedCategory(userId), amount);
            userManager.setState(userId, UserStateType::IDLE);
            bot.getApi().sendMessage(message->chat->id, "Суму успішно додано.");
        } catch (std::invalid_argument &ex) {
            bot.getApi().sendMessage(userId, "Будь ласка, введіть коректне число для суми.");
        }
    } else {
        bot.getApi().sendMessage(userId, "Я не очікував введення суми. Використайте команду 'Додати транзакцію'.");
    }
}


void FinanceTrackerBot::Run() {
    bot.getEvents().onCommand({"start", "info"},
                              [this](const TgBot::Message::Ptr &message) {
                                  handleCommandMessage(message->text, message);
                              });
    bot.getEvents().onAnyMessage([this](const TgBot::Message::Ptr &message) {
        handleTextMessage(bot, message);
    });
    bot.getEvents().onCallbackQuery([this](const TgBot::CallbackQuery::Ptr &query) {
        handleCallbackQuery(query->data, query);
    });
    TgBot::TgLongPoll long_poll(bot);
    std::cout << bot.getApi().getMyName()->name << ": started.\n";
    while (true) {
        long_poll.start();
    }
}
