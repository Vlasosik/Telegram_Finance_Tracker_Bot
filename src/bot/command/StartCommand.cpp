#include "bot/command/StartCommand.h"

#include "bot/ui_manager/UIManager.h"

void StartCommand::Execute(TgBot::Bot &bot, const TgBot::Message::Ptr &message) {
    bot.getApi().sendMessage(message->chat->id, "Привіт! Я ваш фінансовий бот 🤖💲");
    UIManager::sendMainBar(bot, message->chat->id);
};
