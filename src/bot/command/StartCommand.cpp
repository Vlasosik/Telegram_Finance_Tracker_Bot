#include "bot/command/StartCommand.h"

void StartCommand::Execute(TgBot::Bot &bot, const TgBot::Message::Ptr &message) {
    bot.getApi().sendMessage(message->chat->id, "Привіт! Я ваш фінансовий бот 🤖💲");
}
