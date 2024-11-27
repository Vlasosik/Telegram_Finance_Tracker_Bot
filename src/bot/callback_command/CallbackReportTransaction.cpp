#include "bot/callback_command/CallbackReportTransaction.h"

#include "bot/ui_manager/UIManager.h"

void CallbackReportTransaction::ExecuteCallback(TgBot::Bot &bot, const TgBot::CallbackQuery::Ptr &query) {
    UIManager::sendReportTransactionBar(bot, query->message->chat->id);
}
