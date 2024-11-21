#include "bot/command/BackCommand.h"

#include "bot/ui_manager/UIManager.h"

void BackCommand::Execute(TgBot::Bot &bot, const TgBot::Message::Ptr &message) {
    bot.getApi().sendMessage(message->chat->id, "Ви повернулися до головного меню.");
    UIManager::sendMainBar(bot, message->chat->id);
}
