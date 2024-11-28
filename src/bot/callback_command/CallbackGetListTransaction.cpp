#include "bot/callback_command/CallbackGetListTransaction.h"

#include "user/UserManager.h"

void CallbackGetListTransaction::ExecuteCallback(TgBot::Bot &bot, const TgBot::CallbackQuery::Ptr &query) {
    int64_t userId = query->message->chat->id;
    const auto &userManager = UserManager::getInstance();
    const auto transactions = userManager.getListTransaction(userId);
    std::ostringstream messageStream;

    if (transactions.empty()) {
        messageStream << "У вас поки що немає транзакцій.";
    } else {
        int index = 1;
        for (const auto &transaction: transactions) {
            messageStream << index++ << ". " << transaction.toString() << "\n";
        }
    }
    auto message = bot.getApi().sendMessage(userId, messageStream.str());
}
