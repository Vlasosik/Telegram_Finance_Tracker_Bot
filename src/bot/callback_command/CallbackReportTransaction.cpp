#include "bot/callback_command/CallbackReportTransaction.h"

#include "bot/ui_manager/UIManager.h"

void CallbackReportTransaction::ExecuteCallback(TgBot::Bot &bot, const TgBot::CallbackQuery::Ptr &query) {
    const int64_t userId = query->message->chat->id;
    const int32_t messageId = query->message->messageId;
    UIManager::sendReportTransactionBar(bot, userId, messageId);
}
