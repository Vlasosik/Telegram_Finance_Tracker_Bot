#include "bot/FinanceTrackerBot.h"

#include <tgbot/net/TgLongPoll.h>

#include "bot/command/BackCommand.h"
#include "bot/command/HelpCommand.h"
#include "bot/command/InfoCommand.h"
#include "bot/command/StartCommand.h"
#include "bot/ui_manager/UIManager.h"

FinanceTrackerBot::FinanceTrackerBot(const std::string &token) : bot(token) {
    registerCommand();
    registerCallbacks();
}

void FinanceTrackerBot::registerCommand() {
    commands["/start"] = std::make_shared<StartCommand>();
    commands["/help"] = std::make_shared<HelpCommand>();
    // made command info
}

void FinanceTrackerBot::registerCallbacks() {
    callbackQueries["Доступні категорії"] = [this](const TgBot::CallbackQuery::Ptr &query) {
        UIManager::sendCategoryBar(bot, query->message->chat->id);
    };
    callbackQueries["Управління категоріями"] = [this](const TgBot::CallbackQuery::Ptr &query) {
        UIManager::sendCategoryManagementBar(bot, query->message->chat->id);
    };
    callbackQueries["Допомога"] = [this](const TgBot::CallbackQuery::Ptr &query) {
        bot.getApi().sendMessage(query->message->chat->id,
                                 "Цей бот допомагає вам вести облік витрат і категорій, створювати фінансові звіти та"
                                 " аналізувати свої фінанси для кращого планування бюджету🤓📝\n"
                                 "Використовуйте цього бота для відстеження витрат, автоматичного підрахунку звітів та "
                                 "управління своїми фінансами, щоб досягти фінансової стабільності💪🏻✨");
    };
    callbackQueries["Їжа"] = [this](const TgBot::CallbackQuery::Ptr &query) {
        userSelectedCategories[query->message->chat->id].emplace(query->data);
        bot.getApi().sendMessage(query->message->chat->id, "Категорію \"" + query->data + "\" успішно додано.");
    };
    callbackQueries["Одяг та взуття"] = [this](const TgBot::CallbackQuery::Ptr &query) {
        userSelectedCategories[query->message->chat->id].emplace(query->data);
        bot.getApi().sendMessage(query->message->chat->id, "Категорію \"" + query->data + "\" успішно додано.");
    };
    callbackQueries["Сімʼя та діти"] = [this](const TgBot::CallbackQuery::Ptr &query) {
        userSelectedCategories[query->message->chat->id].emplace(query->data);
        bot.getApi().sendMessage(query->message->chat->id, "Категорію \"" + query->data + "\" успішно додано.");
    };
    callbackQueries["Накопичення"] = [this](const TgBot::CallbackQuery::Ptr &query) {
        userSelectedCategories[query->message->chat->id].emplace(query->data);
        bot.getApi().sendMessage(query->message->chat->id, "Категорію \"" + query->data + "\" успішно додано.");
    };
    callbackQueries["Житло"] = [this](const TgBot::CallbackQuery::Ptr &query) {
        userSelectedCategories[query->message->chat->id].emplace(query->data);
        bot.getApi().sendMessage(query->message->chat->id, "Категорію \"" + query->data + "\" успішно додано.");
    };
    callbackQueries["Транспорт"] = [this](const TgBot::CallbackQuery::Ptr &query) {
        userSelectedCategories[query->message->chat->id].emplace(query->data);
        bot.getApi().sendMessage(query->message->chat->id, "Категорію \"" + query->data + "\" успішно додано.");
    };
    callbackQueries["Особисті витрати"] = [this](const TgBot::CallbackQuery::Ptr &query) {
        userSelectedCategories[query->message->chat->id].emplace(query->data);
        bot.getApi().sendMessage(query->message->chat->id, "Категорію \"" + query->data + "\" успішно додано.");
    };
    callbackQueries["Освіта та розвиток"] = [this](const TgBot::CallbackQuery::Ptr &query) {
        userSelectedCategories[query->message->chat->id].emplace(query->data);
        bot.getApi().sendMessage(query->message->chat->id, "Категорію \"" + query->data + "\" успішно додано.");
    };
    callbackQueries["Назад"] = [this](const TgBot::CallbackQuery::Ptr &query) {
        UIManager::sendMainBar(bot, query->message->chat->id);
    };
}

void FinanceTrackerBot::handleCommandMessage(const std::string &command, const TgBot::Message::Ptr &message) {
    if (commands.contains(command)) {
        commands[command]->Execute(bot, message);
    } else {
        bot.getApi().sendMessage(message->chat->id, "Невідома команда: " + command);
    }
}

void FinanceTrackerBot::handleCallbackMessages(const std::string &command, const TgBot::Message::Ptr &message) {
    if (callbackMessages.contains(command)) {
        callbackMessages[command](message);
    } else {
        bot.getApi().sendMessage(message->chat->id, "Невідома команда: " + command);
    }
}

void FinanceTrackerBot::handleCallbackQuery(const std::string &command, const TgBot::CallbackQuery::Ptr &query) {
    if (callbackQueries.contains(command)) {
        callbackQueries[command](query);
    } else {
        bot.getApi().sendMessage(query->message->chat->id, "Невідома команда: " + command);
    }
}

void FinanceTrackerBot::Run() {
    bot.getEvents().onCommand({"start", "help", "info"},
                              [this](const TgBot::Message::Ptr &message) {
                                  handleCommandMessage(message->text, message);
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
