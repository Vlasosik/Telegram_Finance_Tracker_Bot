#include "bot/command/InfoCommand.h"

void InfoCommand::Execute(TgBot::Bot &bot, const TgBot::Message::Ptr &message) {
    bot.getApi().sendMessage(message->chat->id, "Якщо виникли несправності з ботом, прошу напишіть сюди✏️\n"
                             "@R3qp1o");
}
