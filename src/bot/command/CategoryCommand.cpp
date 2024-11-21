#include "bot/command/CategoryCommand.h"

#include "bot/ui_manager/UIManager.h"

void CategoryCommand::Execute(TgBot::Bot &bot, const TgBot::Message::Ptr &message) {
    UIManager::sendCategoryBar(bot, message->chat->id);
}
