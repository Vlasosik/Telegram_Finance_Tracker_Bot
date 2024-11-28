#include "bot/message_command/StartMessageCommand.h"

#include "bot/ui_manager/UIManager.h"

void StartMessageCommand::ExecuteMessage(TgBot::Bot &bot, const TgBot::Message::Ptr &message) {
    bot.getApi().sendMessage(message->chat->id, "Привіт! Я ваш фінансовий бот 🤖💲");
    const int64_t userId = message->chat->id;
    UIManager::sendMainBar(bot, userId);
};
