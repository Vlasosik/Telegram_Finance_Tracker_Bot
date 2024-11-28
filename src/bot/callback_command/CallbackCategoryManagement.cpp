#include "bot/callback_command/CallbackCategoryManagement.h"

#include "bot/ui_manager/UIManager.h"

void CallbackCategoryManagement::ExecuteCallback(TgBot::Bot &bot, const TgBot::CallbackQuery::Ptr &query) {
    const int64_t userId = query->message->chat->id;
    const int32_t messageId = query->message->messageId;
    UIManager::sendCategoryManagementBar(bot, userId, messageId);
    if (query->data == "Назад") {
        UIManager::sendMainBar(bot, userId, messageId);
    }
}
