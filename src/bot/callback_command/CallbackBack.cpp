#include "bot/callback_command/CallbackBack.h"

#include "bot/ui_manager/UIManager.h"

void CallbackBack::ExecuteCallback(TgBot::Bot &bot, const TgBot::CallbackQuery::Ptr &query) {
    UIManager::sendMainBar(bot, query->message->chat->id);
}
