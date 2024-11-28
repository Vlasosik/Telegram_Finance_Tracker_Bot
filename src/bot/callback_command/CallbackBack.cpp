#include "bot/callback_command/CallbackBack.h"

#include "bot/ui_manager/UIManager.h"

void CallbackBack::ExecuteCallback(TgBot::Bot &bot, const TgBot::CallbackQuery::Ptr &query) {
    const int64_t userId = query->message->chat->id;
    const int32_t messageId = query->message->messageId;
    UIManager::sendMainBar(bot, userId, messageId);
}
