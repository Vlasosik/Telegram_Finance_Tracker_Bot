#include "bot/callback_command/CallbackAvailableСategories.h"
#include "bot/ui_manager/UIManager.h"

void CallbackAvailableCategories::ExecuteCallback(TgBot::Bot &bot, const TgBot::CallbackQuery::Ptr &query) {
    UIManager::sendCategoryBar(bot, query->message->chat->id);
}
