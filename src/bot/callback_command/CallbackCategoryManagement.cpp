#include "bot/callback_command/CallbackCategoryManagement.h"

#include "bot/ui_manager/UIManager.h"

void CallbackCategoryManagement::ExecuteCallback(TgBot::Bot &bot, const TgBot::CallbackQuery::Ptr &query) {
    UIManager::sendCategoryManagementBar(bot, query->message->chat->id);
}
